/**********************************************************************************************
 * File         : walker.h
 * Author       : ska124
 * Date         : 07/05/2013
 * SVN          :
 * Description  : data structure walker
 *********************************************************************************************/

#ifndef WALKER_H_INCLUDED
#define WALKER_H_INCLUDED

#include "global_types.h"
#include "global_defs.h"
#include <unordered_set>
#include <cstdlib>

class walker_c
{
  private:
    macsim_c* m_simBase;
    int m_max_count;
    Counter m_cycle;
    Walker_Status m_status;
    uint32_t m_walker_store_latency;
    uint32_t m_walker_load_latency;
    unsigned m_core_id;
    uint32_t *m_cursor;
    bool m_search_done;
    md5_value *m_buf;
    uint32_t m_nuca_latency[8];


    // AT Walkers
    std::map<uint32_t, at_walker_c*> m_walkers;

    // Queues
    pqueue_c<Acc_Msg_Type> *m_in_queue;     // Enqueue IMB - Dequeue Walker
    pqueue_c<Acc_Msg_Type> *m_out_queue;     // Enqueue Walker - Dequeue IMB

    // Shared Data
    std::map<uint32_t, std::unordered_set<uint32_t> > *m_pe_walker_load_keys;
    std::map<uint32_t, std::unordered_set<uint32_t> > *m_pe_walker_store_keys;

    // O3SimInterface
    O3sim_ruby *m_ruby;

  public:
    walker_c(int max_walkers,
              pqueue_c<Acc_Msg_Type> *in_queue,
              pqueue_c<Acc_Msg_Type> *out_queue,
              macsim_c *simBase,
              std::map<uint32_t, std::unordered_set<uint32_t> > *m_pe_walker_load_keys,
              std::map<uint32_t, std::unordered_set<uint32_t> > *m_pe_walker_store_keys,
              uint32_t *m_cursor );
    ~walker_c();
    bool add_walker(void);
    void run_a_cycle(void);
    void process_load_keys(void);
    void process_store_keys(void);
    bool check_load_keys(void);
    bool check_store_keys(void);
    void clear_ruby_queue(void);
    void run_all_walkers(void);
    bool add_vector_walker(uint32_t base_addr, trace_info_s *t);
    void print_load_keys(void);
    void print_store_keys(void);
    void cleanup(void);
    void init_hash_walker(void);
    void init_btree_walker(void);
    uint32_t get_load_cycle_count(void);
    uint32_t get_store_cycle_count(void);
    uint32_t get_bank_latency(uint32_t);
    uint32_t nuca_bank_num(uint32_t);
    uint32_t nuca_bank_latency(uint32_t);
};

class at_walker_c
{
  protected:
    Walker_Type m_type;
  public:
    Walker_Type get_type(void){ return m_type; }
    virtual void run_a_cycle(void) = 0;
    virtual std::unordered_set<uint32_t> map_key_to_block_addrs(uint32_t key) = 0;
    virtual uint32_t get_node_size(void) = 0;
};

class vector_walker_c : public at_walker_c
{
  private:
    uint32_t m_base_addr;
    uint32_t m_node_size;
    uint32_t m_vec_len;
    uint32_t m_vec_fetch;
    uint32_t m_vec_cursor;
    const uint32_t *m_cursor;
    uint32_t m_stride;
    uint32_t m_last_cursor;
    uint32_t m_negative_offset;
    Counter m_cycle;
    bool m_running;
    macsim_c *m_simBase;
    walker_mshr_c * m_mshr;
    O3sim_ruby *m_ruby;

    bool m_print_once;

  public:
    vector_walker_c(uint32_t base_addr,
                    uint32_t node_size,
                    uint32_t len,
                    macsim_c *simBase,
                    uint32_t *cursor,
                    uint32_t negative_offset);
    ~vector_walker_c();
    virtual void run_a_cycle(void);
    bool is_in_llc(uint32_t key);
    virtual std::unordered_set<uint32_t> map_key_to_block_addrs(uint32_t key);
    uint32_t map_key_to_addr(uint32_t key);
    uint32_t block_addr(uint32_t addr);
    uint32_t key_count_for_block(uint32_t addr);
    uint32_t map_addr_to_key(uint32_t addr);
    void check_cursor_and_release(void);
    bool remove_mshr_entry(uint32_t key);
    uint32_t get_last_byte_addr(void);
    bool mshr_is_empty();
    void inc_vec_fetch();
    virtual uint32_t get_node_size(void) { return m_node_size; }
    uint32_t get_bank_latency(uint32_t);
    uint32_t nuca_bank_num(uint32_t);
    uint32_t nuca_bank_latency(uint32_t);
};

class hash_walker_c : public at_walker_c
{
    private:
        struct md5_value *p_buf;
        uint32_t m_base_addr;
        uint32_t m_num_keys;
        uint32_t m_node_size;
        macsim_c *m_simBase;
        walker_mshr_c * m_mshr;
        O3sim_ruby *m_ruby;
        std::vector<uint32_t> index_locs;
        int64_t m_last_index;
        bool *m_search_done;
        uint32_t m_hash_cursor;
        Counter m_cycle;

    public:
        hash_walker_c(  md5_value* buf,
                        uint32_t num_keys,
                        macsim_c *simBase,
                        bool *search_done);
        ~hash_walker_c();
        virtual void run_a_cycle(void);
        virtual std::unordered_set<uint32_t> map_key_to_block_addrs(uint32_t key);
        virtual uint32_t get_node_size();
        uint32_t map_key_to_addr(uint32_t key);
        bool keycmp(uint32_t* k1, uint32_t* k2);
        uint32_t block_addr(uint32_t addr);
        bool remove_mshr_entry(uint32_t key);
};


class btree_walker_c : public at_walker_c
{
    private:
        macsim_c *m_simBase;
        Counter m_cycle;
        BTree *p_BTree;
        bool * m_search_done;
        std::unordered_set<unsigned long long> m_address_set;
        walker_mshr_c *m_mshr;

    public:
        btree_walker_c(macsim_c* simBase, bool * search_done);
        ~btree_walker_c();
        virtual void run_a_cycle(void);
        virtual std::unordered_set<uint32_t> map_key_to_block_addrs(uint32_t key);
        virtual uint32_t get_node_size();
        uint32_t block_addr_32bit(uint64_t addr);
        bool remove_mshr_entry(uint32_t block_addr);
};

class walker_mshr_c
{
  private:
    macsim_c *m_simBase;
    uint32_t m_max_count;
    std::map < uint32_t , std::pair<Walker_MSHR_Entry_Status , std::unordered_set<uint32_t> > > m_entries;
    O3sim_ruby *m_ruby;
    at_walker_c* m_parent_walker;

  public:
    walker_mshr_c(int num_entries, macsim_c *simBase, at_walker_c* parent_walker);
    bool add_entry( uint32_t key);
    bool add_block( uint32_t block_addr);
    bool remove_entry(uint32_t block_addr);
    void issue_all(void);
    void issue_all_unlocked(void);
    uint32_t free_entries();
    bool is_empty(){ return free_entries() == m_max_count; }
};



#endif



