/** \file L1Cache.C
  * 
  * Auto generated C++ code started by symbols/StateMachine.C:327
  * Created by slicc definition of Module "Cache Leasing v2 L1 Cache CMP"
  */

#include "Global.h"
#include "RubySlicc_includes.h"
#include "L1Cache_Controller.h"
#include "L1Cache_State.h"
#include "L1Cache_Event.h"
#include "Types.h"
#include "System.h"
#include "Chip.h"

stringstream L1Cache_transitionComment;
#define APPEND_TRANSITION_COMMENT(str) (L1Cache_transitionComment << str)
/** \brief static profiler defn */
L1Cache_Profiler L1Cache_Controller::s_profiler;

/** \brief constructor */
L1Cache_Controller::L1Cache_Controller(Chip* chip_ptr, int version)
{
  m_chip_ptr = chip_ptr;
  m_id = m_chip_ptr->getID();
  m_version = version;
  m_machineID.type = MachineType_L1Cache;
  m_machineID.num = m_id*RubyConfig::numberOfL1CachePerChip()+m_version;
  (*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version])).setConsumer(this);


  s_profiler.possibleTransition(L1Cache_State_I, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_I, L1Cache_Event_L1_WThru);
  s_profiler.possibleTransition(L1Cache_State_I, L1Cache_Event_L1_Atomic);
  s_profiler.possibleTransition(L1Cache_State_I, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_S, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_S, L1Cache_Event_L1_WThru);
  s_profiler.possibleTransition(L1Cache_State_S, L1Cache_Event_L1_Atomic);
  s_profiler.possibleTransition(L1Cache_State_S, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_I_S, L1Cache_Event_L1_WThru);
  s_profiler.possibleTransition(L1Cache_State_I_S, L1Cache_Event_L1_Atomic);
  s_profiler.possibleTransition(L1Cache_State_I_S, L1Cache_Event_Data_Done);
  s_profiler.possibleTransition(L1Cache_State_SM, L1Cache_Event_Data_Done);
  s_profiler.possibleTransition(L1Cache_State_I_I, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_SM, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_I_I, L1Cache_Event_L1_WThru);
  s_profiler.possibleTransition(L1Cache_State_I_I, L1Cache_Event_L1_Atomic);
  s_profiler.possibleTransition(L1Cache_State_I_I, L1Cache_Event_Data);
  s_profiler.possibleTransition(L1Cache_State_SM, L1Cache_Event_Data);
  s_profiler.possibleTransition(L1Cache_State_I_I, L1Cache_Event_Data_Done);
  s_profiler.possibleTransition(L1Cache_State_I_I, L1Cache_Event_DataAtomic);
  s_profiler.possibleTransition(L1Cache_State_I_I, L1Cache_Event_DataAtomic_Done);
  s_profiler.possibleTransition(L1Cache_State_I_I, L1Cache_Event_Ack);
  s_profiler.possibleTransition(L1Cache_State_I_I, L1Cache_Event_Ack_Done);
  s_profiler.possibleTransition(L1Cache_State_SM, L1Cache_Event_L1_WThru);
  s_profiler.possibleTransition(L1Cache_State_SM, L1Cache_Event_L1_Atomic);
  s_profiler.possibleTransition(L1Cache_State_SM, L1Cache_Event_Ack);
  s_profiler.possibleTransition(L1Cache_State_SM, L1Cache_Event_Ack_Done);
}

void L1Cache_Controller::print(ostream& out) const { out << "[L1Cache_Controller " << m_chip_ptr->getID() << " " << m_version << "]"; }

// Actions

/** \brief Issue GETS*/
void L1Cache_Controller::a_issueGETS(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_GETS;
      (out_msg).m_Requestor = m_machineID;
      (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
      DEBUG_SLICC(MedPrio, "../protocols/FUSION/cachelease2-L1cache.sm:374: ", addr);
;
      DEBUG_SLICC(MedPrio, "../protocols/FUSION/cachelease2-L1cache.sm:375: ", (out_msg).m_Destination);
;
      (out_msg).m_MessageSize = MessageSizeType_Control;
      (out_msg).m_Prefetch = ((*in_msg_ptr)).m_Prefetch;
      (out_msg).m_AccessMode = ((*in_msg_ptr)).m_AccessMode;
      (out_msg).m_Space = ((*in_msg_ptr)).m_Space;
      (out_msg).m_RequestSize = (get_DATA_BLOCK_BYTES());
      (out_msg).m_deltaRequested = (L1Cache_getDelta_Access(addr));
      (out_msg).m_memfetch = ((*in_msg_ptr)).m_memfetch;
      ((*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_MSG_LATENCY);
    }
  }
}

/** \brief send upgrade to the L2 cache*/
void L1Cache_Controller::u_sendUpgradeToL2(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
            if (ASSERT_FLAG && !((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).isPresent(addr)))) {
        cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:390, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

      }
;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_DATA_UPGRADE;
      (out_msg).m_Requestor = m_machineID;
      (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
      (out_msg).m_MessageSize = (IntToMessageSizeType(((*in_msg_ptr)).m_Size));
      (out_msg).m_Space = ((*in_msg_ptr)).m_Space;
      (out_msg).m_RequestSize = ((*in_msg_ptr)).m_Size;
      (out_msg).m_Dirty = (true);
      (out_msg).m_liveUntilTime = ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_liveUntilTime;
      (out_msg).m_memfetch = ((*in_msg_ptr)).m_memfetch;
      ((*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_DATA_LATENCY);
    }
  }
}

/** \brief send data to the L2 cache from TBE*/
void L1Cache_Controller::d2t_sendDataToL2_fromTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_DATA;
      (out_msg).m_DataBlk = ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_DataBlk;
      (out_msg).m_Requestor = m_machineID;
      (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
      (out_msg).m_MessageSize = (IntToMessageSizeType(((*in_msg_ptr)).m_Size));
      (out_msg).m_Space = ((*in_msg_ptr)).m_Space;
      (out_msg).m_RequestSize = ((*in_msg_ptr)).m_Size;
      (out_msg).m_Dirty = (true);
      (out_msg).m_memfetch = ((*in_msg_ptr)).m_memfetch;
      ((*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_DATA_LATENCY);
    }
  }
}

/** \brief send Atomic data to the L2 cache from TBE*/
void L1Cache_Controller::d2t_sendAtomicDataToL2_fromTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_DATA_ATOMIC;
      (out_msg).m_DataBlk = ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_DataBlk;
      (out_msg).m_Requestor = m_machineID;
      (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
      (out_msg).m_MessageSize = (IntToMessageSizeType(((*in_msg_ptr)).m_Size));
      (out_msg).m_Space = ((*in_msg_ptr)).m_Space;
      (out_msg).m_RequestSize = ((*in_msg_ptr)).m_Size;
      (out_msg).m_Dirty = (true);
      (out_msg).m_memfetch = ((*in_msg_ptr)).m_memfetch;
      ((*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_DATA_LATENCY);
    }
  }
}

/** \brief If not prefetch, notify sequencer the load completed.*/
void L1Cache_Controller::h_load_hit(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((*(dynamic_cast<Sequencer*>(m_chip_ptr->getSequencer(m_version)))).readCallback(addr));
}

/** \brief If not prefetch, notify sequencer that store completed.*/
void L1Cache_Controller::hh_store_hit(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((*(dynamic_cast<Sequencer*>(m_chip_ptr->getSequencer(m_version)))).writeCallback(((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_memfetch));
  }
}

/** \brief Allocate TBE*/
void L1Cache_Controller::i_allocateTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).allocate(addr));
    ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_isPrefetch = (false);
    ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_Space = ((*in_msg_ptr)).m_Space;
    ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_ThreadID = ((*in_msg_ptr)).m_ThreadID;
  }
}

/** \brief Allocate TBE with lifetime from Cache*/
void L1Cache_Controller::i_allocateTBEwTime(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).allocate(addr));
    ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_isPrefetch = (false);
    ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_Space = ((*in_msg_ptr)).m_Space;
    ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_ThreadID = ((*in_msg_ptr)).m_ThreadID;
        if (ASSERT_FLAG && !((L1Cache_isL1CacheTagPresent(addr)))) {
      cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:474, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

    }
;
    ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_liveUntilTime = ((L1Cache_getL1CacheEntry(addr))).m_liveUntilTime;
  }
}

/** \brief Pop mandatory queue.*/
void L1Cache_Controller::k_popMandatoryQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).dequeue());
}

/** \brief Pop Incoming Response queue and profile the delay within this virtual network*/
void L1Cache_Controller::o_popIncomingResponseQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_DATA)) {
      (profileBandwidth(("L2_DATA"), ((*in_msg_ptr)).m_MessageSize));
    } else {
      if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_ACK)) {
        (profileBandwidth(("L2_MSG"), ((*in_msg_ptr)).m_MessageSize));
      } else {
        if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_DATA_ATOMIC)) {
          (profileBandwidth(("L2_ATOMIC"), ((*in_msg_ptr)).m_MessageSize));
        } else {
                    cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:494, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid L1 response type") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
        }
      }
    }
  }
  (((*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version]))).dequeue());
}

/** \brief Deallocate TBE*/
void L1Cache_Controller::s_deallocateTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
    if (ASSERT_FLAG && !((((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_pendingReads == (0)))) {
    cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:501, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

  }
;
    if (ASSERT_FLAG && !((((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_pendingWrites == (0)))) {
    cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:502, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

  }
;
  (((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).deallocate(addr));
}

/** \brief Update L1 block's lifetime from reponse msg*/
void L1Cache_Controller::t_updateL1Lifetime(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
        if (ASSERT_FLAG && !((L1Cache_isL1CacheTagPresent(((*in_msg_ptr)).m_Address)))) {
      cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:508, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

    }
;
    ((L1Cache_getL1CacheEntry(addr))).m_liveUntilTime = ((*in_msg_ptr)).m_liveUntilTime;
  }
}

/** \brief Write data to cache from L2 response queue*/
void L1Cache_Controller::dd_writeDataToL1Cache(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
        if (ASSERT_FLAG && !((L1Cache_isL1CacheTagPresent(((*in_msg_ptr)).m_Address)))) {
      cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:515, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

    }
;
    ((L1Cache_getL1CacheEntry(addr))).m_DataBlk = ((*in_msg_ptr)).m_DataBlk;
  }
}

/** \brief Write data to cache from TBE*/
void L1Cache_Controller::dt_writeDataToL1CacheFromTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
    if (ASSERT_FLAG && !((L1Cache_isL1CacheTagPresent(addr)))) {
    cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:521, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

  }
;
  ((L1Cache_getL1CacheEntry(addr))).m_DataBlk = ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_DataBlk;
}

/** \brief Deallocate L1 cache block.  Sets the cache to not present, allowing a replacement in parallel with a fetch.*/
void L1Cache_Controller::ff_deallocateL1CacheBlock(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if ((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).isTagPresent(addr))) {
    (((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).deallocate(addr));
  } else {
        cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:529, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("cannot deallocate, L1 block not present") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
  }
}

/** \brief Set L1 D-cache tag equal to tag of block B.*/
void L1Cache_Controller::oo_allocateL1DCacheBlock(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if (((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).isTagPresent(addr)) == (false))) {
    (((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).allocate(addr));
  }
}

/** \brief recycle L1 request queue*/
void L1Cache_Controller::z_recycleMandatoryQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).recycle());
}

/** \brief stall - i.e. do nothing*/
void L1Cache_Controller::z_stall(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
}

/** \brief Profile a demand miss*/
void L1Cache_Controller::pM_profileMiss(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
        if (ASSERT_FLAG && !((((*in_msg_ptr)).m_profiled == (false)))) {
      cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:549, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

    }
;
    (profile_L1Cache_request_g((*in_msg_ptr), m_chip_ptr->getID(), (true)));
  }
}

/** \brief Profile a demand hit*/
void L1Cache_Controller::pH_profileHit(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
        if (ASSERT_FLAG && !((((*in_msg_ptr)).m_profiled == (false)))) {
      cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:556, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

    }
;
    (profile_L1Cache_request_g((*in_msg_ptr), m_chip_ptr->getID(), (false)));
  }
}

/** \brief Increment pending read count*/
void L1Cache_Controller::pr_incPendingRead(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
    if (ASSERT_FLAG && !(((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).isPresent(addr)) == (true)))) {
    cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:564, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

  }
;
  ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_pendingReads = (((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_pendingReads + (1));
}

/** \brief Increment pending write count*/
void L1Cache_Controller::pw_incPendingWrite(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
    if (ASSERT_FLAG && !(((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).isPresent(addr)) == (true)))) {
    cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:568, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

  }
;
  ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_pendingWrites = (((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_pendingWrites + (1));
}

/** \brief Decrement pending read count*/
void L1Cache_Controller::pr_decPendingRead(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
    if (ASSERT_FLAG && !(((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).isPresent(addr)) == (true)))) {
    cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:573, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

  }
;
  ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_pendingReads = (((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_pendingReads - (1));
    if (ASSERT_FLAG && !((((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_pendingReads >= (0)))) {
    cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:575, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

  }
;
}

/** \brief Decrement pending write count*/
void L1Cache_Controller::pw_decPendingWrite(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
    if (ASSERT_FLAG && !(((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).isPresent(addr)) == (true)))) {
    cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:578, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

  }
;
  ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_pendingWrites = (((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_pendingWrites - (1));
    if (ASSERT_FLAG && !((((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_pendingWrites >= (0)))) {
    cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:580, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

  }
;
}

