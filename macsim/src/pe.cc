/**********************************************************************************************
 * File         : pe.cc
 * Author       : ska124
 * Date         : 07/05/2013
 * CVS          :
 * Description  : pe methods
 *********************************************************************************************/

#include "pe.h"
#include "trace_read.h"
#include "macsim.h"
#include "acc_core.h"
#include "assert_macros.h"
#include "debug_macros.h"
#include "pqueue.h"
#include "all_knobs.h"
#include <cmath>
#include <sys/stat.h>
#include <iostream>

/**********************************************************************************************
 * 1. run_a_cycle :
 *********************************************************************************************/

void pe_c::run_a_cycle(void)
{
    // Running a pe cycle

    trace_info_s *t=NULL;
    if(m_status == PE_INACTIVE)
    {
        t = m_simBase->m_acc_core_pointer->get_front_marker();
        ASSERTM(t, "PE_INACTIVE -- No Marker -- Acc_Core called pes->run_a_cycle()");
    }

    switch(m_status)
    {
        case PE_INACTIVE:
            switch(t->ds_op_type)
            {

                case VEC_SORT:
                    sort_schedule(t);
                    m_out_queue->enqueue(WORK_PRIO_NORMAL, PE_IMB_LOAD_REQ);
                    m_status = PE_LOAD;
                    break;

                case VEC_ITER:
                    // schedule and enqueue request to imb
                    iter_schedule(t);
                    m_out_queue->enqueue(WORK_PRIO_NORMAL, PE_IMB_LOAD_REQ);
                    m_status = PE_LOAD;
                    break;

                case HASH_SEARCH:
                  // report("PE received Hash Search Marker");
                    m_out_queue->enqueue(WORK_PRIO_NORMAL, HASH_SEARCH_REQ);
                    m_status = PE_STALL;
                    break;

                case BTREE_TRAVERSE:
                  // report("PE received BTREE marker");
                    m_out_queue->enqueue(WORK_PRIO_NORMAL, BTREE_TRAVERSE_REQ);
                    m_status = PE_STALL;
                    break;

                default:
                    break;
            }
            break;

        case PE_STALL:
            if(m_in_queue->ready())
            {
                switch(m_in_queue->dequeue())
                {
                    case HASH_SEARCH_DONE:
                        m_status = PE_INACTIVE;
                        break;

                    case BTREE_TRAVERSE_DONE:
                        m_status = PE_INACTIVE;
                        break;

                    default:
                        ASSERTM(false, "Incorrect msg at PE_STALL");
                        break;
                }
            }
            break;

        case PE_LOAD:
            // Waiting for load -- check if return from imb
            if(m_in_queue->ready())
            {
                switch(m_in_queue->dequeue())
                {
                    case IMB_PE_LOAD_DONE:
                        
                        if(*KNOB(KNOB_ACC_RECO) && adjust_marker)
                        {
                            report("RECOMM: SUBTRACTING from compute_init");
                            uint32_t temp = recomm_num_of_zero_iter(m_count,m_imb_capacity /2,start_index_recomm);
                            start_index_recomm += m_imb_capacity /2;
                            m_compute_countdown = m_compute_init - (reco_compute_slice_latency *temp) ;
                            if(m_compute_init < (reco_compute_slice_latency *temp) )
                                report("RECOMM: ALERT ERORR :compute_init is negative");
                        }
                        else
                        {
                            //report("RECOMM: # ELSE");
                            m_compute_countdown = m_compute_init;

                        }
                        m_status = PE_COMPUTE;
                        break;
                    default:
                        ASSERTM(false, "Incorrect msg when waiting for load");
                        break;
                }
            }
            break;

        case PE_COMPUTE:
            switch(m_compute_countdown)
            {
              case 0:
                 //report("Compute Done - Cursor: " << (*m_cursor));
                if( m_compute_k == 0)
                {
                    ACC_STAT(PE_INT, m_int_count * m_cursor_stride);
                    ACC_STAT(PE_FP, m_fp_count * m_cursor_stride);
                    ACC_STAT(STACK_COUNT, m_stack_count * m_cursor_stride);
                    ACC_STAT(IBUF_ACCESS,m_static_ins_count); // 32 bits per instruction
                    m_out_queue->enqueue(WORK_PRIO_NORMAL, PE_IMB_STORE_REQ);
                    m_status = PE_STORE;
                }
                else
                {
                    //report("ComputeK: " << m_compute_k);
                    m_compute_countdown = m_compute_k;
                    m_compute_k = 0;
                }
                break;
              default:
                // report("Computing");
                --m_compute_countdown;
                break;
            }
            break;

        case PE_STORE:
            if(m_in_queue->ready())
            {
                switch(m_in_queue->dequeue())
                {
                    case IMB_PE_STORE_DONE:
                        // One LOAD->COMPUTE->STORE complete, increment loop counter

                        (*m_cursor) += m_cursor_stride;

                        if(*m_cursor < m_max_cursor)
                        {
                            add_load_keys();
                            add_store_keys();
                            m_out_queue->enqueue(WORK_PRIO_NORMAL, PE_IMB_LOAD_REQ);
                            m_status = PE_LOAD;
                        }
                        else
                        {
                            reset();
                            m_status = PE_INACTIVE;
                            //report("RECOMMENDER: # STORE");
                        }
                        break;
                    default:
                        ASSERTM(false, "Incorrect msg when waiting for store");
                        break;
                }
            }
            break;
    }

    m_cycle++;
    ACC_STAT(PE_CYCLE_COUNT,1);
}

void pe_c::reset()
{
    m_compute_init = 0;
    m_int_count = 0;
    m_fp_count = 0;
    m_stack_count = 0;

    m_pe_walker_store_keys->clear();
    m_pe_walker_load_keys->clear();
}

void pe_c::sort_schedule(trace_info_s *t)
{
    *m_cursor = 0;

    uint32_t base_addr = t->ds_load_base_addrs[0];
    uint32_t start_index = t->ds_load_index_offsets[0];
    uint32_t end_index = t->ds_load_index_offsets[1];
    uint32_t node_size = t->ds_node_size[0];

    int vec_data =  node_size * end_index;
    // Keys to sort per iter
    if(vec_data > m_imb_capacity)
        m_cursor_stride = m_imb_capacity / node_size;
    else
        m_cursor_stride = end_index;

    m_max_cursor = end_index;

    uint32_t max_num = get_bitonic_sort_bound(m_max_cursor);
    m_compute_init = (max_num % m_count == 0) ? max_num / m_count : max_num / m_count + 1;

    m_int_count = 1;
    m_stack_count = 0;

    // Add stores to same vector
    t->ds_store_base_addrs[0] = t->ds_load_base_addrs[0];
    t->ds_load_index_offsets[0] = 0;
    t->ds_load_index_offsets[1] = 0;
    t->ds_vec_len[0] = end_index - start_index;

    // Since we don't support iterations over different length vectors
    t->ds_num_iter = t->ds_vec_len[0];

    add_load_keys();
    add_store_keys();
}

uint32_t pe_c::get_bitonic_sort_bound(uint32_t num)
{
    // Get 2^n number which is greater than given num
    return (uint32_t)(1 << ((uint32_t) log2(num) + 1));
}

void pe_c::iter_schedule(const trace_info_s *t)
{
    *m_cursor = 0;
    adjust_marker = false;
        report("Adjust Marker False\n");
    reco_compute_slice_latency=0;
    int trace_max_ds = 8; // Replace with KNOB, check common-trace-fields for value [].

    // This filtering needs to be done to ensure that a[i] = fn(a[i]) does not
    // use 2 different imb entries

    std::unordered_set<uint32_t> ds_set;

    // IMB storage required in single iter in bytes
    int single_iter_req = 0;

    for (int i = 0; i < trace_max_ds; ++i)
    {
        uint32_t ld_addr =  t->ds_load_base_addrs[i] +
                            t->ds_node_size[i] * t->ds_load_index_offsets[i];

        if(ld_addr != 0)
        {
            if( ds_set.count(ld_addr) == 0)
            {
                single_iter_req += t->ds_node_size[i];
                ds_set.insert(ld_addr);
            }
        }

        uint32_t st_addr =  t->ds_store_base_addrs[i] +
                            t->ds_node_size[i] * t->ds_store_index_offsets[i];

        if(st_addr != 0)
        {
            if( ds_set.count(st_addr) == 0)
            {
                single_iter_req += t->ds_node_size[i];
                ds_set.insert(st_addr);
            }
        }

    }

    // Calculate the number of iterations we can store data for in the imb
    //report("RECOMMENDER: single_iter_req = "<<single_iter_req);
    //report("RECOMMENDER: node_size_i = "<<t->ds_node_size[0] << "\t"<<t->ds_node_size[1]<<endl);
    if(*KNOB(KNOB_ACC_RECO) &&  single_iter_req  == 2) 
    { 
        report("Adjust Marker True\n");
        adjust_marker = true;
        reco_compute_slice_latency = t->ds_compute_slice_latency;
    }
    else
    {
        //report("Single iter not 2");
        }
    uint32_t unroll_iters_recomm = m_imb_capacity / single_iter_req;

    ASSERTM(unroll_iters_recomm, "Single Iter Requires more than IMB size");

    if (unroll_iters_recomm >= t->ds_num_iter)
    {
        unroll_iters_recomm = t->ds_num_iter;
    }

    // Set loop break condition
    m_max_cursor = t->ds_num_iter;

    // Set loop stride
    m_cursor_stride = unroll_iters_recomm;
    


    float    X = t->ds_compute_slice_latency,
             Y = single_iter_req,
             Z = unroll_iters_recomm * single_iter_req,
             N = m_count; //No of PEs

    // 1 PE can crunch Y data in X cycles
    // 1 PE can crunch 1 data in X/Y cycles
    // 1 PE can crunch Z data in X/Y * Z cycles
    // N PE can crunch Z data in (X*Z)/(Y*N) cycles
    // + adjust for fractional

    m_compute_init = (uint32_t) ceil((Z*X) / (Y*N));
    m_compute_k = t->ds_compute_k;

    m_int_count = t->ds_compute_int_count;
    m_fp_count = t->ds_compute_fp_count;
    m_static_ins_count = t->ds_static_ins_count;
    m_stack_count = t->ds_stack_accesses;

    if( m_static_ins_count * 4 > *KNOB(KNOB_ACC_IBUF_CAPACITY) )
    {
        int refill_count = m_static_ins_count * 4 / *KNOB(KNOB_ACC_IBUF_CAPACITY);
        m_compute_k += *KNOB(KNOB_ACC_IBUF_REFILL_CYCLES) * refill_count;
    }

    add_load_keys();
    add_store_keys();
}

uint32_t pe_c::get_cursor_stride()
{
    return m_cursor_stride;
}

void pe_c::add_load_keys()
{
    trace_info_s *t = m_simBase->m_acc_core_pointer->get_front_marker();

    int trace_max_ds = 8; // Replace with KNOB, check common-trace-fields for value [].

    for (int i = 0; i < trace_max_ds; ++i)
    {
        uint32_t addr = t->ds_load_base_addrs[i];
        if( addr != 0)
        {
            int iter_max = (m_cursor_stride + *m_cursor > m_max_cursor) ?
                            m_max_cursor - *m_cursor : m_cursor_stride;

            for (int j = 0; j < iter_max; ++j )
            {
                uint32_t key = *m_cursor + j + t->ds_load_index_offsets[i];
                (*m_pe_walker_load_keys)[addr].insert(key);
            }
        }
    }
}

void pe_c::add_store_keys()
{
    trace_info_s *t = m_simBase->m_acc_core_pointer->get_front_marker();

    int trace_max_ds = 8; // Replace with KNOB, check common-trace-fields for value [].

    for (int i = 0; i < trace_max_ds; ++i)
    {
        uint32_t addr = t->ds_store_base_addrs[i];
        if( addr != 0)
        {
            int iter_max = (m_cursor_stride + *m_cursor > m_max_cursor) ?
                            m_max_cursor - *m_cursor : m_cursor_stride;

            for (int j = 0; j < iter_max; ++j )
            {
                uint32_t key = *m_cursor + j + t->ds_store_index_offsets[i];
                (*m_pe_walker_store_keys)[addr].insert(key);
            }
        }
    }
}


uint32_t pe_c::recomm_num_of_zero_iter(uint32_t num_pes,uint32_t unroll_iters_recomm,long int  start_index_recomm)
{

    report( "RECOMM: start_index_recomm = " <<start_index_recomm<<endl);
    int temp_start_index= start_index_recomm;


    int max=temp_start_index+unroll_iters_recomm;
    if(max > file_size)
        max=file_size;
    int count=0; 
    int num_zero_iters=0;
    int j =0;
    
    while (temp_start_index < max)
    {

        if(read_recommender_bits_buffer[temp_start_index]==0) {
                count++;
        }
        
        //cout<<"read_recommender_bits_buffer["<<temp_start_index<<"] ="<<read_recommender_bits_buffer[temp_start_index]<<" count = "<<count<<"  j ="<<j<<"  num_zero_iters = "<<num_zero_iters<<endl;

        if ( (j+1)%num_pes == 0 )
        {
            if(count==num_pes)
            {
                num_zero_iters++;
            }
            count=0;
            j=0;
        }
        else j++;

        temp_start_index++;
    }
    report("RECOMM: num_zero_iters ="<<num_zero_iters);
    return num_zero_iters;


}



   




pe_c::pe_c(int count,
         pqueue_c<Acc_Msg_Type> *in_queue,
         pqueue_c<Acc_Msg_Type> *out_queue,
         macsim_c* simBase,
         uint32_t *cursor,
         std::map<uint32_t, std::unordered_set<uint32_t> > *pe_walker_load_keys,
         std::map<uint32_t, std::unordered_set<uint32_t> > *pe_walker_store_keys)
{
    m_count = count;
    m_compute_countdown = 0;
    m_cycle = 0;
    m_in_queue = in_queue;
    m_out_queue = out_queue;
    m_simBase = simBase;
    m_status = PE_INACTIVE;
    m_cursor = cursor;
    m_max_cursor = 0;
    m_pe_walker_load_keys = pe_walker_load_keys;
    m_pe_walker_store_keys = pe_walker_store_keys;
    m_imb_capacity = *KNOB(KNOB_ACC_IMB_CAP);
    m_int_count = 0;
    m_fp_count = 0;
    m_static_ins_count = 0;

    //---nav
        //report("Adjust Marker False\n");
    adjust_marker = false;
    reco_compute_slice_latency=0;
    struct stat results;  
    start_index_recomm=0;
    ifstream myFile ("bits.bin", std::ifstream::binary);

    assert(myFile.is_open() && "Could not open bits.bin");
    file_size=0;
    
    if (stat("bits.bin", &results) == 0)    
    {
        file_size= results.st_size; 
    }
    report("FILE SIZE = "<<file_size<<endl<<"start_index_recomm"<<start_index_recomm);
 
    read_recommender_bits_buffer = new bool[sizeof(bool)*file_size];
    myFile.read ((char *)read_recommender_bits_buffer, file_size);
    myFile.close();

}
