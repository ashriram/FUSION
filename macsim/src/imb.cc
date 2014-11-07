/**********************************************************************************************
 * File         : imb.cc
 * Author       : ska124
 * Date         : 07/05/2013
 * CVS          :
 * Description  : imb methods
 *********************************************************************************************/

#include "imb.h"
#include "pqueue.h"
#include "assert_macros.h"
#include "debug_macros.h"
#include "macsim.h"
#include "acc_core.h"

#include <iostream>

/**********************************************************************************************
  Note: Stats for the IMB assume the entire IMB is filled and cleaned
  put in each iteration. This may not be the case for the last
  iteration of the cursor.

 *********************************************************************************************/

void imb_c::run_a_cycle(void)
{
    // Running a imb cycle

    if(m_pe_in_queue->ready())
    {
        switch(m_pe_in_queue->dequeue())
        {
            case PE_IMB_LOAD_REQ:
                m_walker_out_queue->enqueue(WORK_PRIO_NORMAL, IMB_WALKER_LOAD_REQ);
                break;
            
            case PE_IMB_STORE_REQ:
                m_walker_out_queue->enqueue(WORK_PRIO_NORMAL, IMB_WALKER_STORE_REQ);
                break;

            case HASH_SEARCH_REQ:
                m_walker_out_queue->enqueue(WORK_PRIO_NORMAL, HASH_SEARCH_REQ);
                break;

            case BTREE_TRAVERSE_REQ:
                m_walker_out_queue->enqueue(WORK_PRIO_NORMAL, BTREE_TRAVERSE_REQ);
                break;

          default:
            break;
        }
    }

    if(m_walker_in_queue->ready())
    {
        switch(m_walker_in_queue->dequeue())
        {
            case WALKER_IMB_LOAD_DONE:
                m_pe_out_queue->enqueue(WORK_PRIO_NORMAL, IMB_PE_LOAD_DONE);
                break;

            case WALKER_IMB_STORE_DONE:
                ACC_STAT(IMB_REFILL,1);
                m_pe_out_queue->enqueue(WORK_PRIO_NORMAL, IMB_PE_STORE_DONE);
                break;

            case HASH_SEARCH_DONE:
                m_pe_out_queue->enqueue(WORK_PRIO_NORMAL, HASH_SEARCH_DONE);
                break;

            case BTREE_TRAVERSE_DONE:
                m_pe_out_queue->enqueue(WORK_PRIO_NORMAL, BTREE_TRAVERSE_DONE);
                break;
                 
          default:
            break;
        }
    }

    m_cycle++;
}

imb_c::imb_c(int cap,
        pqueue_c<Acc_Msg_Type> *pe_in_queue,
        pqueue_c<Acc_Msg_Type> *pe_out_queue,
        pqueue_c<Acc_Msg_Type> *walker_in_queue,
        pqueue_c<Acc_Msg_Type> *walker_out_queue,
        macsim_c* simBase)
{
    m_pe_in_queue = pe_in_queue;
    m_pe_out_queue = pe_out_queue;
    m_walker_in_queue = walker_in_queue;
    m_walker_out_queue = walker_out_queue;

    m_capacity = cap;
    m_cycle = 0;

    m_simBase = simBase;
}
