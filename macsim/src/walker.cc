/**********************************************************************************************
 * File         : walker.cc
 * Author       : ska124
 * Date         : 07/05/2013
 * CVS          :
 * Description  : walker methods
 *********************************************************************************************/

#include "walker.h"
#include "pqueue.h"
#include "assert_macros.h"
#include "debug_macros.h"
#include "../../gems-lib-acc/ruby_clean/O3sim_ruby/O3sim_ruby.h"
#include <iostream>
#include "memory.h"
#include "trace_read.h"
#include "acc_core.h"
#include "knob.h"
#include "all_knobs.h"
#include "acc_btree.h"

#include <sys/stat.h>
#include <algorithm>
#include <cmath>
/**********************************************************************************************
 * 1. run_a_cycle :
 *********************************************************************************************/

// Vector Walker class

vector_walker_c::vector_walker_c(   uint32_t base_addr,
                                    uint32_t node_size,
                                    uint32_t len,
                                    macsim_c* simBase,
                                    uint32_t *cursor,
                                    uint32_t negative_offset)
{
    m_type = WALK_VEC;
    m_base_addr = base_addr;
    m_node_size = node_size;

    m_cycle = 0;
    m_running = false;
    m_simBase = simBase;
    m_vec_cursor = 0;
    m_vec_fetch = 0;
    m_stride = m_simBase->m_acc_core_pointer->get_pe_cursor_stride();
    m_ruby = simBase->m_memory->m_ruby;

    m_mshr = new walker_mshr_c(*KNOB(KNOB_ACC_WALKER_MSHR_SIZE), simBase, this);

    m_cursor = cursor;
    m_last_cursor = 0;
    m_negative_offset = negative_offset;

    m_print_once = true;

    // We need to separate out the vec_len and num_iters and treat
    // them separately and also figure out all the corner cases for
    // each, for now we always do vec_len = num_iters

    trace_info_s *t = m_simBase->m_acc_core_pointer->get_front_marker();
    m_vec_len = t->ds_num_iter;

    inc_vec_fetch();
}

void vector_walker_c::inc_vec_fetch()
{
    m_vec_fetch += m_stride;
}

void vector_walker_c::run_a_cycle(void)
{
    // Check if MSHR is ready and push in requests as many as possible for the cursor
    for( ; m_vec_cursor < m_vec_fetch &&
           m_vec_cursor < m_vec_len;
           m_vec_cursor++)
    {
        if( !m_mshr->add_entry(m_vec_cursor) )
            break;
    }

    // if ( m_vec_cursor == m_vec_len &&
    //      m_mshr->is_empty() &&
    //      m_print_once)
    // {
    //     report( hex << m_base_addr << dec << " Walker Finish: " << m_simBase->m_simulation_cycle);
    //     m_print_once = false;
    //     report("m_cursor: " << *m_cursor);
    // }



    m_mshr->issue_all();
    check_cursor_and_release();
    m_cycle++;
}

vector_walker_c::~vector_walker_c()
{
    delete m_mshr;
}

std::unordered_set<uint32_t> vector_walker_c::map_key_to_block_addrs(uint32_t key)
{
    std::unordered_set<uint32_t> blocks;

    uint32_t start_addr = map_key_to_addr(key); // First Byte Addr

    for (int i = 0; i < m_node_size; ++i)
    {
        uint32_t addr = start_addr + i;
        blocks.insert(block_addr(addr));
    }

    return blocks;
}

uint32_t vector_walker_c::block_addr(uint32_t addr)
{
    // Replace with KNOB -- Hard coded cache line size bits
    return (addr >> 6) << 6;
}

uint32_t vector_walker_c::map_key_to_addr(uint32_t key)
{
    return m_base_addr + m_node_size * key;
}

bool vector_walker_c::is_in_llc(uint32_t key)
{
    uint32_t addr = map_key_to_addr(key);
    return m_ruby->acc_try_cache_access(addr);
}

bool vector_walker_c::remove_mshr_entry(uint32_t addr)
{
#if 0
    uint32_t temp_bank = (addr>>15)%8;
    switch ( temp_bank ) {
        case 0:
            ACC_STAT(BANK0,1);
            break;

        case 1:
            ACC_STAT(BANK1,1);
            break;
            
        case 2:
            ACC_STAT(BANK2,1);
            break;
        case 3:
            ACC_STAT(BANK3,1);
            break;
        case 4:
            ACC_STAT(BANK4,1);
            break;
        case 5:
            ACC_STAT(BANK5,1);
            break;

        case 6:
            ACC_STAT(BANK6,1);
            break;
        case 7:
            ACC_STAT(BANK7,1);
            break;
    
    }

#endif
    
    uint32_t count = key_count_for_block(addr);
    m_ruby->set_key_count_for_block(addr, count);

    // report("Setting Key Count: " << hex << addr << dec << " " << count);

    return m_mshr->remove_entry(addr);
}

uint32_t vector_walker_c::key_count_for_block(uint32_t addr)
{
    std::unordered_set<uint32_t> keys;

    for (int i = 0; i < 64; ++i)
    {
        uint32_t byte_addr = addr + i;

        if(byte_addr >= m_base_addr)
        {
            uint32_t k = map_addr_to_key(byte_addr);
            keys.insert(k);

            if(byte_addr == get_last_byte_addr())
                break;
        }
    }
    return keys.size();
}

bool vector_walker_c::mshr_is_empty()
{
    return m_mshr->is_empty();
}

uint32_t vector_walker_c::get_last_byte_addr()
{
    return m_base_addr + m_node_size * m_vec_len - 1;
}

uint32_t vector_walker_c::map_addr_to_key(uint32_t addr)
{
    ASSERTM(addr >= m_base_addr , "Cant call map addr to key with addr < base_addr");
    return (addr - m_base_addr) / m_node_size;
}

void vector_walker_c::check_cursor_and_release()
{
    if(m_last_cursor < *m_cursor - m_negative_offset)
    {


        std::vector<uint32_t> blocks_to_release;

        for (int i = m_last_cursor;
            i < *m_cursor - m_negative_offset &&
            i < m_vec_len ; ++i)
        {
            std::unordered_set<uint32_t> blocks_for_key = map_key_to_block_addrs(i);

            for(auto I = blocks_for_key.begin(); I != blocks_for_key.end(); ++I)
            {
                blocks_to_release.push_back(*I);
                // report("Decrement Block: " << hex << *I << dec << " Key: " << i << dec);
            }
        }

        for (int j = 0; j < blocks_to_release.size(); ++j)
        {
            m_ruby->decrement_key_count_for_block(blocks_to_release[j]);
        }

        m_last_cursor = *m_cursor - m_negative_offset;
    }
}

// Vector Walker End

// Walker MSHR Class

void walker_mshr_c::issue_all()
{
    for(auto I = m_entries.begin(); I != m_entries.end(); ++I)
    {
        if( (*I).second.first == MSHR_ENTRY_READY)
        {
            uint32_t addr = (*I).first;
            uint32_t core_id = *KNOB(KNOB_NUM_SIM_CORES);

            if ( m_ruby->isReady( addr, 8, core_id, 0, false, false, NULL) )
            {
                m_ruby->send_acc_locked_request(addr, 8, core_id, 0, false, false, NULL);
                (*I).second.first = MSHR_ENTRY_ISSUED;
                ACC_STAT(WALKER_MSHR_ISSUE,1);
            }
        }
    }
}

void walker_mshr_c::issue_all_unlocked()
{
    for(auto I = m_entries.begin(); I != m_entries.end(); ++I)
    {
        if( (*I).second.first == MSHR_ENTRY_READY)
        {
            uint32_t addr = (*I).first;
            uint32_t core_id = *KNOB(KNOB_NUM_SIM_CORES);

            if ( m_ruby->isReady( addr, 8, core_id, 0, false, false, NULL) )
            {
                m_ruby->send_acc_unlocked_request(addr, 8, core_id, 0, false, false, NULL);
                (*I).second.first = MSHR_ENTRY_ISSUED;
                ACC_STAT(WALKER_MSHR_ISSUE,1);
                // report("MSHR Issued: " << addr );
            }
        }
    }
}

walker_mshr_c::walker_mshr_c(int max_entries,
                             macsim_c* simBase,
                             at_walker_c* parent_walker)
{
    m_simBase = simBase;
    m_max_count = max_entries;
    m_ruby = simBase->m_memory->m_ruby;
    m_parent_walker = parent_walker;
}

bool walker_mshr_c::add_entry(uint32_t key)
{
    // To add entry based on the max entries

    std::unordered_set<uint32_t> blocks = m_parent_walker->map_key_to_block_addrs(key);

    if(blocks.size() > free_entries())
        return false;

    // report("Walker: Add Entry: " << key);

    for (auto I = blocks.begin(); I != blocks.end(); ++I)
    {
        uint32_t addr = *I;
        if( m_entries.count(addr) ==  0 )
            m_entries[addr] = std::make_pair(MSHR_ENTRY_READY, std::unordered_set<uint32_t>());
        m_entries[addr].second.insert(key);
    }

    return true;
}

bool walker_mshr_c::add_block(uint32_t block_addr)
{

    if( m_entries.count(block_addr) ==  0 )
    {
        if(free_entries() > 0)
            m_entries[block_addr] = std::make_pair(MSHR_ENTRY_READY, std::unordered_set<uint32_t>());
        else
            return false;
    }

    return true;
}

bool walker_mshr_c::remove_entry(uint32_t addr)
{
    if(m_entries.count(addr) > 0)
    {
        m_entries.erase(addr);
        // Discard all the associated keys, did we need them anywhere?
        return true;
    }
    return false;
}

uint32_t walker_mshr_c::free_entries()
{
    return m_max_count - m_entries.size();
}

// Walker MSHR End


// Hash Walker Class

hash_walker_c::hash_walker_c(struct md5_value* buf, uint32_t num_keys, macsim_c* simBase, bool *search_done)
{


    m_simBase = simBase;
    p_buf = buf;
    trace_info_s *t = m_simBase->m_acc_core_pointer->get_front_marker();
    m_base_addr = t->ds_load_base_addrs[0];
    m_num_keys = num_keys;
    m_node_size = 16;
    m_hash_cursor = 0;
    m_cycle = 0;
    m_search_done = search_done;
    m_type = WALK_HASH;
    m_last_index = -1;


    m_ruby = simBase->m_memory->m_ruby;
    m_mshr = new walker_mshr_c(*KNOB(KNOB_ACC_BTREE_MSHR_SIZE), simBase, this);

    // Perform the search and find the indices where the keys match

    uint32_t* search_keys = new uint32_t[32];

    memcpy((void*)search_keys , (const void *)t->ds_node_size , 32);
    memcpy((void*)(search_keys + 8) , (const void *)t->ds_load_index_offsets , 32);
    memcpy((void*)(search_keys + 16) , (const void *)t->ds_store_base_addrs , 32);
    memcpy((void*)(search_keys + 24) , (const void *)t->ds_store_index_offsets , 32);

    // Debug Code

    // memcpy((void*)(p_buf + 4), (const void *)t->ds_node_size , 32);

    for (int i = 0; i < num_keys ; i++)
    {
        for (int j = 0; j < 32; j += 4) // Keys 0-7
        {
            if(keycmp( p_buf[i]._32, search_keys+j ))
            {
                index_locs.push_back(i);
                report("Key found at: " << i);
            }
        }
    }



    if(index_locs.size() == 8)
        m_last_index = *std::max_element(index_locs.begin(),index_locs.end()); // All keys were found somewhere
    else
        m_last_index = num_keys; // We have to look at everything as some were not found

    report("List Index: " << m_last_index);
}

bool hash_walker_c::keycmp(uint32_t* k1, uint32_t* k2)
{
    for(int i=0; i<4; i++)
        if(k1[i]!=k2[i])
            return false;
    return true;
}

hash_walker_c::~hash_walker_c()
{
    delete m_mshr;
}

void hash_walker_c::run_a_cycle()
{
    if( m_hash_cursor == m_last_index &&
        m_mshr->free_entries() == *KNOB(KNOB_ACC_BTREE_MSHR_SIZE) )
    {
        // Search is done if all blocks issued
        // and all blocks brought in by memory system
        *m_search_done = true;
    }
    else
    {
        for( ; m_hash_cursor < m_last_index ; m_hash_cursor++)
        {
            if( !m_mshr->add_entry(m_hash_cursor) )
                break;
        }
        m_mshr->issue_all_unlocked();
    }
    m_cycle++;
}

std::unordered_set<uint32_t> hash_walker_c::map_key_to_block_addrs(uint32_t key)
{
    std::unordered_set<uint32_t> blocks;

    uint32_t start_addr = map_key_to_addr(key); // First Byte Addr

    for (int i = 0; i < m_node_size; ++i)
    {
        uint32_t addr = start_addr + i;
        blocks.insert(block_addr(addr));
    }

    return blocks;
}

uint32_t hash_walker_c::block_addr(uint32_t addr)
{
    return (addr >> 6) << 6;
}

uint32_t hash_walker_c::get_node_size()
{
    return m_node_size; // Size of key
}

uint32_t hash_walker_c::map_key_to_addr(uint32_t key)
{
    // As actual array in the program has a 4 byte pointer in the same buffer
    return m_base_addr + (m_node_size + 4) * key ;
}

bool hash_walker_c::remove_mshr_entry(uint32_t addr)
{
    uint32_t latency = m_simBase->m_acc_core_pointer->get_bank_latency(addr);
    ACC_STAT(HASHT_ADD_ACCESS_LATENCY,latency);
#if 0
    uint32_t temp_bank = (addr>>15)%8;
    switch ( temp_bank ) {
        case 0:
            ACC_STAT(BANK0,1);
            break;

        case 1:
            ACC_STAT(BANK1,1);
            break;
            
        case 2:
            ACC_STAT(BANK2,1);
            break;
        case 3:
            ACC_STAT(BANK3,1);
            break;
        case 4:
            ACC_STAT(BANK4,1);
            break;
        case 5:
            ACC_STAT(BANK5,1);
            break;

        case 6:
            ACC_STAT(BANK6,1);
            break;
        case 7:
            ACC_STAT(BANK7,1);
            break;
    
    }
#endif

    return m_mshr->remove_entry(addr);
}

// Hash Walker Ends


// Walker Group class

walker_c::walker_c(int max_walkers,
                   pqueue_c<Acc_Msg_Type> *in_queue,
                   pqueue_c<Acc_Msg_Type> *out_queue,
                   macsim_c *simBase,
                   std::map<uint32_t, std::unordered_set<uint32_t> > *pe_walker_load_keys,
                   std::map<uint32_t, std::unordered_set<uint32_t> > *pe_walker_store_keys,
                   uint32_t *cursor)
{
    m_max_count = max_walkers;
    m_in_queue = in_queue;
    m_out_queue = out_queue;
    m_simBase = simBase;

    m_pe_walker_load_keys = pe_walker_load_keys;
    m_pe_walker_store_keys = pe_walker_store_keys;

    // This works because memory is initialized in macsim.cc before cores
    m_ruby = simBase->m_memory->m_ruby;

    m_status = WALKER_READY;

    m_walker_store_latency = 0;

    // As all actual cores have ids 0 ... NUM_SIM_CORES - 1
    m_core_id = *KNOB(KNOB_NUM_SIM_CORES);

    m_cursor = cursor;

    // NUCA Bank Latencies as specified in the config file
    m_nuca_latency[0] = *KNOB(KNOB_ACC_BANK_0_LATENCY);
    m_nuca_latency[1] = *KNOB(KNOB_ACC_BANK_1_LATENCY);
    m_nuca_latency[2] = *KNOB(KNOB_ACC_BANK_2_LATENCY);
    m_nuca_latency[3] = *KNOB(KNOB_ACC_BANK_3_LATENCY);
    m_nuca_latency[4] = *KNOB(KNOB_ACC_BANK_4_LATENCY);
    m_nuca_latency[5] = *KNOB(KNOB_ACC_BANK_5_LATENCY);
    m_nuca_latency[6] = *KNOB(KNOB_ACC_BANK_6_LATENCY);
    m_nuca_latency[7] = *KNOB(KNOB_ACC_BANK_7_LATENCY);
}

void walker_c::run_a_cycle(void)
{
    switch(m_status)
    {
        case WALKER_READY:
            if(m_in_queue->ready())
            {
                switch(m_in_queue->dequeue())
                {
                    case IMB_WALKER_LOAD_REQ:
                      // print_load_keys();
                      // print_store_keys();
                        process_load_keys();
                        process_store_keys();
                        m_status = WALKER_LOADING;
                        break;

                    case IMB_WALKER_STORE_REQ:

                        m_status = WALKER_STORING;
                        break;

                    case HASH_SEARCH_REQ:
                      // report("Walker Received Search Request");
                        init_hash_walker();
                        m_search_done = false;
                        m_status = WALKER_HASH_SEARCH;
                    break;

                    case BTREE_TRAVERSE_REQ:
                      // report("Walker Received BTREE_TRAVERSE_REQ");
                        init_btree_walker();
                        m_search_done = false;
                        m_status = WALKER_BTREE_TRAVERSE;
                        break;

                    default:
                        break;
                }
            }
            break;

        case WALKER_HASH_SEARCH:
            if(m_search_done)
            {
                m_search_done = false;
                m_status = WALKER_READY;
                m_out_queue->enqueue(WORK_PRIO_NORMAL, HASH_SEARCH_DONE);
                delete m_buf;
                // report("Walker Search complete");
            }
            break;

        case WALKER_BTREE_TRAVERSE:
            if(m_search_done)
            {
                m_search_done = false;
                m_status = WALKER_READY;
                m_out_queue->enqueue(WORK_PRIO_NORMAL, BTREE_TRAVERSE_DONE);
                // report("Walker BTREE traverse complete");
            }
            break;

        case WALKER_LOADING:
            if( check_load_keys() & check_store_keys() )
            {
                // m_pe_walker_load_keys->clear(); // Not needed due to swap
                //m_out_queue->enqueue(WORK_PRIO_NORMAL, WALKER_IMB_LOAD_DONE);
                //m_status = WALKER_READY;
                m_status = WALKER_LOAD_WAIT;
            }
            break;

        case WALKER_LOAD_WAIT:
            switch(m_walker_load_latency)
            {
                case 0:
                    m_out_queue->enqueue(WORK_PRIO_NORMAL, WALKER_IMB_LOAD_DONE);
                    m_status = WALKER_READY;
                    break;
                default:
                    --m_walker_load_latency;
                    break;
            }
            break;

        case WALKER_STORING:
            switch(m_walker_store_latency)
            {
              case 0:
                m_out_queue->enqueue(WORK_PRIO_NORMAL, WALKER_IMB_STORE_DONE);
                m_status = WALKER_READY;
                break;
              default:
                --m_walker_store_latency;
                break;
            }
        break;
    }

    // Run each walker for a cycle
    run_all_walkers();

    // Check Ruby Queue for completed requests
    clear_ruby_queue();

    m_cycle++;
    ACC_STAT(WALKER_CYCLE_COUNT, 1);
}

void walker_c::init_btree_walker()
{
    ASSERTM(m_walkers.size()==0, "Exclusive BTree walker");

    uint32_t base_addr = 0xF00D;
    m_walkers[base_addr] = new btree_walker_c(m_simBase, &m_search_done);
}

void walker_c::init_hash_walker()
{
    ASSERTM(m_walkers.size() == 0, "Exclusive Hash Walker");

    trace_info_s *t = m_simBase->m_acc_core_pointer->get_front_marker();

    struct stat results;
    uint32_t file_size;

    if (stat("keys.bin", &results) == 0)
        file_size = results.st_size;
    else
        ASSERTM(false, "Could not get file size");

    m_buf = new md5_value[file_size / 16];

    std::ifstream data("keys.bin", ios::in | ios::binary);
    ASSERTM(data.is_open(), "Hash Key file not found");
    data.read((char*)m_buf, file_size);
    data.close();

    uint32_t base_addr = t->ds_load_base_addrs[0];

    m_walkers[base_addr] = new hash_walker_c(m_buf, file_size / 16, m_simBase, &m_search_done);
}

void walker_c::clear_ruby_queue()
{
    while(! m_ruby->RubyQueueEmpty(m_core_id) )
    {
        Addr addr = m_ruby->RubyQueueTop(m_core_id);
        bool found = false;

        for( auto I = m_walkers.begin(); I != m_walkers.end(); I++ )
        {
            // Check here for WALK_VEC and WALK_HASH
            if(m_walkers[(*I).first]->get_type() == WALK_VEC)
            {
                vector_walker_c *w = dynamic_cast<vector_walker_c*>(m_walkers[(*I).first]);

                found = w->remove_mshr_entry(addr);

                if(found)
                {
                    m_ruby->RubyQueuePop(m_core_id);
                    break;
                }

            }
            else if(m_walkers[(*I).first]->get_type() == WALK_HASH)
            {
                hash_walker_c *w = dynamic_cast<hash_walker_c*>(m_walkers[(*I).first]);

                found = w->remove_mshr_entry(addr);

                ASSERTM(found, "Could not remove MSHR entry for HASH");
                m_ruby->RubyQueuePop(m_core_id);
            }
            else if(m_walkers[(*I).first]->get_type() == WALK_BTREE)
            {
                btree_walker_c *w = dynamic_cast<btree_walker_c*>(m_walkers[(*I).first]);

                found = w->remove_mshr_entry(addr);

                ASSERTM(found, "Could not remove MSHR entry for BTREE");
                // report("Removed BTree Block: " << addr );
                m_ruby->RubyQueuePop(m_core_id);
                break;

            }
        }
        ASSERTM(found, "Could not remove MSHR entry for VEC");

        // Could be infinite loop if no walker has addr

        // if(!found)
        // {
        //     m_ruby->RubyQueuePop(m_core_id);
        //     report("Stray Block: " << hex << addr << dec);
        //     ACC_STAT(STRAY_BLOCK,1);
        // }
    }
}


void walker_c::run_all_walkers()
{
    for(auto I = m_walkers.begin(); I != m_walkers.end(); I++)
            (I->second)->run_a_cycle();

    trace_info_s *t = m_simBase->m_acc_core_pointer->get_front_marker();

    if(t->ds_op_type == VEC_ITER || t->ds_op_type == VEC_SORT)
    {
        bool no_pending_mem_req = true;

        for(auto I = m_walkers.begin(); I != m_walkers.end(); I++)
        {
            vector_walker_c *w = dynamic_cast<vector_walker_c*>(m_walkers[(*I).first]);
            no_pending_mem_req &= w->mshr_is_empty();
        }

        if(no_pending_mem_req)
        {
            for(auto I = m_walkers.begin(); I != m_walkers.end(); I++)
            {
                vector_walker_c *w = dynamic_cast<vector_walker_c*>(m_walkers[(*I).first]);
                w->inc_vec_fetch();
            }
        }
    }
}

bool walker_c::check_load_keys()
{
    bool all_done = true;

    for(auto I = m_pe_walker_load_keys->begin(); I != m_pe_walker_load_keys->end(); I++)
    {
        ASSERTM(m_walkers.count((*I).first) > 0, "Walker not initialized");
        std::unordered_set<uint32_t> retain_keys;
        for(auto J = (*I).second.begin(); J != (*I).second.end(); J++)
        {
            vector_walker_c *w = dynamic_cast<vector_walker_c*>(m_walkers[(*I).first]);
            if( ! w->is_in_llc(*J) )
            {
                retain_keys.insert(*J);
            }

        }

        if(retain_keys.size() > 0)
            all_done = false;

        (*m_pe_walker_load_keys)[(*I).first].swap(retain_keys);
    }

    // if(!all_done)
    // {
    //     report("Retain Keys:");
    //     print_load_keys();
    // }

    return all_done;
}

bool walker_c::check_store_keys()
{
    bool all_done = true;

    for(auto I = m_pe_walker_store_keys->begin(); I != m_pe_walker_store_keys->end(); I++)
    {
        ASSERTM(m_walkers.count((*I).first) > 0, "Walker not initialized");
        std::unordered_set<uint32_t> retain_keys;
        for(auto J = (*I).second.begin(); J != (*I).second.end(); J++)
        {
            // Check here for WALK_VEC and WALK_HASH
            vector_walker_c *w = dynamic_cast<vector_walker_c*>(m_walkers[(*I).first]);
            if( ! w->is_in_llc(*J) )
            {
                retain_keys.insert(*J);
            }

        }

        if(retain_keys.size() > 0)
            all_done = false;

        (*m_pe_walker_store_keys)[(*I).first].swap(retain_keys);


    }

    // if(!all_done)
    // {
    //     report("Retain Keys:");
    //     print_store_keys();
    // }

    return all_done;
}

void walker_c::process_load_keys()
{
    trace_info_s *t = m_simBase->m_acc_core_pointer->get_front_marker();

    for(auto I = m_pe_walker_load_keys->begin(); I != m_pe_walker_load_keys->end(); I++ )
    {
        if(m_walkers.count(I->first) == 0)
        {
            // Add a walker for new vector being fetched
            switch(t->ds_op_type)
            {
                case VEC_SORT:
                case VEC_ITER:
                    ASSERTM(add_vector_walker(I->first, t), "Too Many Walkers!");
                    break;
                default:
                    break;
            }
        }
    }
    
    m_walker_load_latency = get_load_cycle_count();
     //report("Walker Load Latency: " << m_walker_load_latency);

    // Print out the cache blocks required for iter
    // print_load_keys();
}

void walker_c::process_store_keys()
{
    trace_info_s *t = m_simBase->m_acc_core_pointer->get_front_marker();

    for(auto I = m_pe_walker_store_keys->begin(); I != m_pe_walker_store_keys->end(); I++ )
    {
        if(m_walkers.count(I->first) == 0)
        {
            // Add a walker for new vector being fetched
            switch(t->ds_op_type)
            {
                case VEC_SORT:
                case VEC_ITER:
                    ASSERTM(add_vector_walker(I->first, t), "Too Many Walkers!");
                    break;
                default:
                    break;
            }
        }

    }

    // Add load latency as well since you need to access those lines to
    // decrement the reference counter.
    m_walker_store_latency = get_load_cycle_count() + get_store_cycle_count();
    //report("Walker Store Latency: " << m_walker_store_latency);
    // print_store_keys();
}

walker_c::~walker_c()
{
    cleanup();
}

inline
uint32_t walker_c::get_bank_latency(uint32_t addr)
{
    return m_nuca_latency[nuca_bank_num(addr)];
}

inline
uint32_t walker_c::nuca_bank_num(uint32_t addr)
{
    return (uint32_t)((addr >> 15) & 7);
}

inline
uint32_t walker_c::nuca_bank_latency(uint32_t id)
{
    ASSERTM(id < 8, "Invalid Bank Num");
    return m_nuca_latency[id];
}

void walker_c::cleanup(void)
{
    for(auto I = m_walkers.begin(); I != m_walkers.end(); ++I)
    {
        if ( (*I).second->get_type() == WALK_VEC )
            delete dynamic_cast<vector_walker_c*>((*I).second);
        else if ( (*I).second->get_type() == WALK_HASH )
            delete dynamic_cast<hash_walker_c*>((*I).second);
        else if ( (*I).second->get_type() == WALK_BTREE )
            delete dynamic_cast<btree_walker_c*>((*I).second);
    }


    m_walkers.clear();
    ASSERTM(m_walkers.size() == 0, "Walkers not cleared");
}

bool walker_c::add_vector_walker(uint32_t base_addr, trace_info_s *t)
{
    uint32_t node_size = 0, len = 0;

    for(int i = 0; i < m_max_count; ++i)
    {
        if(t->ds_load_base_addrs[i] == base_addr || t->ds_store_base_addrs[i] == base_addr)
        {
            node_size = t->ds_node_size[i];
            len = t->ds_vec_len[i];
            break;
        }
    }

    ASSERTM(len, "Len size is zero");
    ASSERTM(node_size, "Node size is zero");


    if (m_walkers.size() < m_max_count)
    {

        int negative_offset = 0;
        for (int i = 0; i < m_max_count; ++i)
        {
            if(t->ds_load_base_addrs[i] == base_addr || t->ds_store_base_addrs[i] == base_addr)
            {
                if( t->ds_load_index_offsets[i] < negative_offset )
                {
                    negative_offset = t->ds_load_index_offsets[i];
                }

                if( t->ds_store_index_offsets[i] < negative_offset )
                {
                    negative_offset = t->ds_store_index_offsets[i];
                }
            }
        }

        m_walkers[base_addr] = new vector_walker_c( base_addr,
                                                    node_size,
                                                    len,
                                                    m_simBase,
                                                    m_cursor,
                                                    -(negative_offset));
        // report("New Vector Walker: "
        //        << hex << base_addr << dec
        //        << " Node: " << node_size
        //        << " Len: " << len);

        return true;
    }
    else
    {
        return false;
    }
}

uint32_t walker_c::get_store_cycle_count()
{
    std::unordered_set<uint32_t> cache_blocks;
    for(auto I = m_pe_walker_store_keys->begin(); I != m_pe_walker_store_keys->end(); I++)
    {
        for(auto J = (*I).second.begin(); J != (*I).second.end(); J++)
        {
            vector_walker_c *w = dynamic_cast<vector_walker_c*>(m_walkers[(*I).first]);
            cache_blocks.insert( w->block_addr(w->map_key_to_addr(*J)) );
        }
    }

    uint32_t cache_cycles = 0;

    for (auto L = cache_blocks.begin(); L != cache_blocks.end(); ++L)
    {
       cache_cycles += get_bank_latency(*L);
    }
    
    float ratio = *KNOB(KNOB_CLOCK_L3) / *KNOB(KNOB_CLOCK_ACC);
    float acc_cycles = (float) cache_cycles / ratio;

    return (uint32_t) ceil(acc_cycles);
}

uint32_t walker_c::get_load_cycle_count()
{
    std::unordered_set<uint32_t> cache_blocks;
    for(auto I = m_pe_walker_load_keys->begin(); I != m_pe_walker_load_keys->end(); I++)
    {
        for(auto J = (*I).second.begin(); J != (*I).second.end(); J++)
        {
            vector_walker_c *w = dynamic_cast<vector_walker_c*>(m_walkers[(*I).first]);
            cache_blocks.insert( w->block_addr(w->map_key_to_addr(*J)) );
        }
    }

    uint32_t cache_cycles = 0;

    for (auto L = cache_blocks.begin(); L != cache_blocks.end(); ++L)
    {
       cache_cycles += get_bank_latency(*L);
    }
    
    float ratio = *KNOB(KNOB_CLOCK_L3) / *KNOB(KNOB_CLOCK_ACC);
    float acc_cycles = (float) cache_cycles / ratio;

    return (uint32_t) ceil(acc_cycles);
}

void walker_c::print_load_keys()
{
    for(auto I = m_pe_walker_load_keys->begin(); I != m_pe_walker_load_keys->end(); I++)
    {
        std::unordered_set<uint32_t> cache_blocks;
        std::cout << hex << (*I).first << dec << " Load Set [ ";
        for(auto J = (*I).second.begin(); J != (*I).second.end(); J++)
        {
            std::cout << *J << ",";

            vector_walker_c *w = dynamic_cast<vector_walker_c*>(m_walkers[(*I).first]);
            cache_blocks.insert( w->block_addr(w->map_key_to_addr(*J)) );
        }
        std::cout << "] Blocks: [";
        for(auto K = cache_blocks.begin(); K != cache_blocks.end(); K++)
        {
            std::cout << hex << *K << ",";
        }
        std::cout << "]" << dec << endl;
    }
}


void walker_c::print_store_keys()
{
    for(auto I = m_pe_walker_store_keys->begin(); I != m_pe_walker_store_keys->end(); I++)
    {
        std::unordered_set<uint32_t> cache_blocks;
        std::cout << hex << (*I).first << dec << " Store Set [ ";
        for(auto J = (*I).second.begin(); J != (*I).second.end(); J++)
        {
            std::cout << *J << ",";
            vector_walker_c *w = dynamic_cast<vector_walker_c*>(m_walkers[(*I).first]);
            cache_blocks.insert( w->block_addr(w->map_key_to_addr(*J)));
        }
        std::cout << "] Blocks: [";
        for(auto K = cache_blocks.begin(); K != cache_blocks.end(); K++)
        {
            std::cout << hex << *K << ",";
        }
        std::cout << "]" << dec << endl;
    }
}


/******* BTree Walker **************/

btree_walker_c::btree_walker_c(macsim_c * simBase, bool * search_done)
{
    m_simBase = simBase;
    m_search_done = search_done;
    m_type = WALK_BTREE;

    p_BTree = new BTree(const_cast<char *>("dump.bin"),4*1000*1000);
    p_BTree->init();
    p_BTree->doWork();

    m_mshr = new walker_mshr_c( *KNOB(KNOB_ACC_BTREE_MSHR_SIZE) , simBase, this );
}

btree_walker_c::~btree_walker_c()
{
    delete p_BTree;
}

void btree_walker_c::run_a_cycle()
{
    if(m_address_set.size() == 0)
        m_address_set.swap(p_BTree->pop());

    if( m_address_set.size() == 0 &&
        m_mshr->free_entries() == *KNOB(KNOB_ACC_BTREE_MSHR_SIZE))
    {
        // If address set size is 0 even after pop then we are done
        *m_search_done = true;
    }
    else
    {

        // for(auto I = m_address_set.begin(); I != m_address_set.end(); I++ )
        //     report("Set Contains: " << *I);

        std::unordered_set<unsigned long long> retain_set;
        for(auto I = m_address_set.begin(); I != m_address_set.end(); I++ )
        {
            uint32_t addr = block_addr_32bit(*I);
            if( ! m_mshr->add_block(addr) )
                retain_set.insert(*I);
        }

        m_address_set.swap(retain_set);

        m_mshr->issue_all_unlocked();
    }

    m_cycle++;
}

uint32_t btree_walker_c::block_addr_32bit(uint64_t addr)
{
    // Replace with KNOB -- Hard coded cache line size bits
    // report("BTree addr: " << hex << addr << dec << endl);
    addr &= 0x00000000FFFFFFFF;
    uint32_t block_addr = (addr >> 6) << 6;
    // report("BTree block addr: " << hex << block_addr << dec << endl);
    return block_addr;
}

std::unordered_set<uint32_t> btree_walker_c::map_key_to_block_addrs(uint32_t key)
{
    ASSERTM(false, "This function should not be called");
}

uint32_t btree_walker_c::get_node_size(void)
{
    ASSERTM(false, "This function should not be called");
    return 0;
}

bool btree_walker_c::remove_mshr_entry(uint32_t addr)
{
    uint32_t latency = m_simBase->m_acc_core_pointer->get_bank_latency(addr);
    ACC_STAT(BTREE_ADD_ACCESS_LATENCY,latency);

#if 0
     uint32_t temp_bank = (addr>>15)%8;
    switch ( temp_bank ) {
        case 0:
            ACC_STAT(BANK0,1);
            break;

        case 1:
            ACC_STAT(BANK1,1);
            break;
            
        case 2:
            ACC_STAT(BANK2,1);
            break;
        case 3:
            ACC_STAT(BANK3,1);
            break;
        case 4:
            ACC_STAT(BANK4,1);
            break;
        case 5:
            ACC_STAT(BANK5,1);
            break;

        case 6:
            ACC_STAT(BANK6,1);
            break;
        case 7:
            ACC_STAT(BANK7,1);
            break;
    
    }
#endif
      
    return m_mshr->remove_entry(addr);
}

/******* BTree Walker End **********/
