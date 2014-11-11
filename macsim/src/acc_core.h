/*
Copyright (c) <2012>, <Georgia Institute of Technology> All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted
provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions
and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or other materials provided
with the distribution.

Neither the name of the <Georgia Institue of Technology> nor the names of its contributors
may be used to endorse or promote products derived from this software without specific prior
written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/


/**********************************************************************************************
 * File         : acc_core.h
 * Author       : ska124
 * Date         : 07/05/2013
 * SVN          :
 * Description  : accelerator core structure
 *********************************************************************************************/

#ifndef ACC_CORE_H_INCLUDED
#define ACC_CORE_H_INCLUDED


#include <string>
#include <queue>
#include <map>
#include <unordered_set>

#include "macsim.h"
#include "global_defs.h"
#include "global_types.h"
#include "trace_read.h"

#define ACC_STAT(x,y) m_simBase->m_acc_core_pointer->add_stat(string(#x),y)

///////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Core (Accelerator) class
///
/// Accelerator core has walker, pe and imb
///////////////////////////////////////////////////////////////////////////////////////////////
class acc_core_c
{
  public:
    /**
     *  \brief Constructor to class acc_core_c
     *  \param c_id - core id
     *  \param type - Type of unit
     *  \param simBase - Pointer to base simulation class for perf/stat counters
     *  \return void
     */
    acc_core_c(macsim_c* simBase, Unit_Type type = UNIT_ACC, uint32_t Id = 0);

    /**
     *  \brief Destructor to class acc_core_c
     *  \return void
     */
    ~acc_core_c(void);

    string get_core_type(void) { return m_core_type; }

    /*! \fn void run_a_cycle()
     *  \brief Function to run a cycle of acc_core_c
     *  \return void
     */
    void run_a_cycle();

    /*! \fn Counter get_cycle_count(void)
     *  \brief Function to return cycle count for the core
     *  \return Counter - Cycle count of the core
     */
    Counter get_cycle_count(void) {return m_acc_core_cycle_count;}

    /*! \fn void inc_acc_core_cycle_count(void)
     *  \brief Function to increment core cycle count
     *  \return void
     */
    void inc_acc_core_cycle_count(void) { m_acc_core_cycle_count++; }

    /*! \fn void advance_queues(void)
     *  \brief Function to advance queues
     *  \return void
     */
    void advance_queues(void);

    /*! \fn Counter check_heartbeat(bool final)
     *  \brief Function to check if final heartbeat for cores
     *  \param final - TRUE or FALSE
     *  \return Counter - Count of cores with final heartbeat
     */
    void check_heartbeat(bool final);

    /*! \fn Counter final_heartbeat(int thread_id)
     *  \brief Function to return final heartbeat count for a specified thread
     *  \param thread_id - thread_id
     *  \return Counter - Heart beat count
     *  @see process_manager_c::terminate_thread
     *
     *  deallocate data immediately follows
     */
    void final_heartbeat(int thread_id);

    /*! \fn Counter core_heartbeat(bool final)
     *  \brief Function to return the core heartbeat
     *  \param final - TRUE or FALSE
     *  \return Counter - Core heartbeat count
     */
    void core_heartbeat(bool);

    /*! \fn Counter check_forward_progress()
     *  \brief Function to check forward progress
     */
    void check_forward_progress();

    /*! \fn void start(void)
     *  \brief Functio to start core simulation
     *  \return void
     */
    void start(void);


    /*! \fn void stop(void)
     *  \brief Function to stop core simulation
     *  \return void
     */
    void stop(void);

    /**
     * Initialize core
     */
    void init(void);

    void add_stat(string name, uint64_t inc_val);
    void print_stats();

    bool m_active;
    
  private:
    int                      m_core_id; /**< core id */
    string                   m_core_type; /**< simulation core type (x86 or ptx) */
    Unit_Type                m_unit_type; /**< core type */
    int                      m_last_terminated_tid; /**< last terminated thread id */
    unordered_map<int, bool> m_terminated_tid; /**< ids of terminated threads */
    Counter                  m_unique_uop_num; /**< unique uop number */
    time_t                   m_sim_start_time; /**< simulation start time */
    Counter                  m_acc_core_cycle_count; /**< current core cycle */
    Counter                  m_inst_count; /**< current instruction count */

    // Stats
    std::map < std::string, uint64_t > m_stats;

    // Forward progress check
    Counter m_last_forward_progress; /**< last checked cycle */
    Counter m_last_inst_count;       /**< last checked instruction count */

    // heartbeat
    heartbeat_s* m_heartbeat; /**< heartbeat per thread*/
    time_t  m_heartbeat_last_time_core; /**< last heartbeat time */
    Counter m_heartbeat_last_cycle_count_core; /**< last heartbeat cycle */
    Counter m_heartbeat_last_inst_count_core; /**< last heartbeat inst. count */
    Counter m_heartbeat_printed_inst_count_core; /**< last printed heartbeat inst. count */
    bool    m_heartbeat_check_done_core; /**< check heartbeat done */

    // configuration
    macsim_c* m_simBase;         /**< macsim_c base class for simulation globals */

    // clock cycle
    Counter m_cycle; /**< clock cycle */
};
#endif   // ACC_CORE_H_INCLUDED
