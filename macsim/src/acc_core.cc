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
 * File         : acc_core.cc
 * Author       : ska124
 * Date         : 07/05/2013
 * CVS          :
 * Description  : main function
 *********************************************************************************************/


/**********************************************************************************************
 * 1. run_a_cycle :
 *
 * 2. heartbeat : for every N cycle, print out current/accumulative performance information.
 *
 *********************************************************************************************/


#include <stdio.h>
#include <cmath>
#include <map>
#include <sstream>
#include <fstream>

#include "assert.h"
#include "acc_core.h"
#include "knob.h"
#include "pqueue.h"
#include "utils.h"
#include "bug_detector.h"
#include "dma_core.h"

#include "config.h"

#include "debug_macros.h"

#include "all_knobs.h"

///////////////////////////////////////////////////////////////////////////////////////////////


#define DEBUG(args...)   _DEBUG(*m_simBase->m_knobs->KNOB_DEBUG_TRACE_READ, ## args)


///////////////////////////////////////////////////////////////////////////////////////////////


void acc_core_c::init(void)
{

}


// acc_core_c constructor
acc_core_c::acc_core_c (macsim_c* simBase, Unit_Type type, uint32_t Id)
{
    m_core_id = Id; /**< core id */
    m_core_type = string("acc"); 
    m_unit_type = type; /**< core type */
    m_active = false;
}

// acc_core_c destructor
acc_core_c::~acc_core_c()
{

}


// start core simulation
void acc_core_c::start(void)
{

}


// stop core simulation
void acc_core_c::stop(void)
{

}


// main execution routine
// In every cycle, run all pipeline stages
void acc_core_c::run_a_cycle(void)
{
    std::cerr << "In ACC: " << m_core_id << "\n";
    m_simBase->m_dma_core_pointer->m_active = true;
    m_simBase->m_dma_core_pointer->m_next = -1;
}


// age entries in various queues
void acc_core_c::advance_queues(void)
{}


// last heartbeat call when a thread is terminated
void acc_core_c::final_heartbeat(int thread_id)
{

}


// In every HEARTBEAT_INTERVAL cycles, print performance information
void acc_core_c::check_heartbeat(bool final)
{
  core_heartbeat(final);
}

// core heartbeat
void acc_core_c::core_heartbeat(bool final)
{
    if (!*m_simBase->m_knobs->KNOB_PRINT_HEARTBEAT)
        return ;
}


// check forward progress of the simulation
void acc_core_c::check_forward_progress()
{
}

void acc_core_c::add_stat(string name, uint64_t inc_val)
{
    ASSERTM(m_stats.count(name) > 0, "Unknown ACC Stat");
    m_stats[name] += inc_val;
}

void acc_core_c::print_stats()
{
    std::ofstream stats_file("acc.stat.out", std::ofstream::out);

    for(auto I = m_stats.begin(); I != m_stats.end(); I++)
        stats_file << I->first << "\t" << I->second << endl;

    stats_file.close();
}
