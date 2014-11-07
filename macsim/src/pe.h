/**********************************************************************************************
 * File         : pe.h
 * Author       : ska124
 * Date         : 07/05/2013
 * SVN          :
 * Description  : processing element for data structure acc
 *********************************************************************************************/

#ifndef PE_H_INCLUDED
#define PE_H_INCLUDED

#include "global_types.h"
#include "global_defs.h"
#include <unordered_set>

class pe_c
{
  private:
    // Queues
    pqueue_c<Acc_Msg_Type> *m_in_queue;     // Enqueue IMB - Dequeue PE
    pqueue_c<Acc_Msg_Type> *m_out_queue;     // Enqueue PE - Dequeue IMB

    uint32_t m_count;
    uint32_t m_compute_countdown;
    Counter m_cycle;

    macsim_c *m_simBase;
    uint32_t *m_cursor;
    uint32_t  m_max_cursor;
    uint32_t m_cursor_stride; // same as unroll factor
    uint32_t m_compute_init;
    int m_imb_capacity;
    uint32_t m_int_count;
    uint32_t m_fp_count;
    uint32_t m_static_ins_count;
    uint32_t m_compute_k;
    uint32_t m_stack_count;
    //nav
    long int start_index_recomm;    
    bool *read_recommender_bits_buffer;   
    bool adjust_marker;
    uint32_t  reco_compute_slice_latency;     
    long int file_size;
    // Shared Data
    std::map<uint32_t, std::unordered_set<uint32_t> > *m_pe_walker_load_keys;
    std::map<uint32_t, std::unordered_set<uint32_t> > *m_pe_walker_store_keys;


  public:
    PE_Status m_status;
    pe_c(int c,
         pqueue_c<Acc_Msg_Type> *in_queue,
         pqueue_c<Acc_Msg_Type> *out_queue,
         macsim_c* simBase,
         uint32_t *cursor,
         std::map<uint32_t, std::unordered_set<uint32_t> > *m_pe_walker_load_keys,
         std::map<uint32_t, std::unordered_set<uint32_t> > *m_pe_walker_store_keys);

    void run_a_cycle(void);
    void iter_schedule(const trace_info_s *t);
    void sort_schedule(trace_info_s *t);
    void add_load_keys();
    void add_store_keys();
    uint32_t get_bitonic_sort_bound(uint32_t num);
    void reset(void);
    uint32_t get_cursor_stride();
    //nav
    uint32_t recomm_num_of_zero_iter(uint32_t num_pes,uint32_t unroll_iters,long int  start_index_recomm);
   
};


#endif

