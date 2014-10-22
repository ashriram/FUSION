/** \file L2Cache.C
  * 
  * Auto generated C++ code started by symbols/StateMachine.C:327
  * Created by slicc definition of Module "Cache Leasing v2 L2 Cache CMP"
  */

#include "Global.h"
#include "RubySlicc_includes.h"
#include "L2Cache_Controller.h"
#include "L2Cache_State.h"
#include "L2Cache_Event.h"
#include "Types.h"
#include "System.h"
#include "Chip.h"

stringstream L2Cache_transitionComment;
#define APPEND_TRANSITION_COMMENT(str) (L2Cache_transitionComment << str)
/** \brief static profiler defn */
L2Cache_Profiler L2Cache_Controller::s_profiler;

/** \brief constructor */
L2Cache_Controller::L2Cache_Controller(Chip* chip_ptr, int version)
{
  m_chip_ptr = chip_ptr;
  m_id = m_chip_ptr->getID();
  m_version = version;
  m_machineID.type = MachineType_L2Cache;
  m_machineID.num = m_id*RubyConfig::numberOfL2CachePerChip()+m_version;
  (*(m_chip_ptr->m_L2Cache_L2ExpireTriggerQueue_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_L2Cache_responseToL2TCache_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_L2Cache_requestToL2TCache_vec[m_version])).setConsumer(this);


  s_profiler.possibleTransition(L2Cache_State_NP, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_NP, L2Cache_Event_L1_Write);
  s_profiler.possibleTransition(L2Cache_State_NP, L2Cache_Event_L1_Upgrade_NT);
  s_profiler.possibleTransition(L2Cache_State_NP, L2Cache_Event_L2_Atomic);
  s_profiler.possibleTransition(L2Cache_State_IS, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_S, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_E, L2Cache_Event_L1_Write);
  s_profiler.possibleTransition(L2Cache_State_S, L2Cache_Event_L1_Upgrade_T);
  s_profiler.possibleTransition(L2Cache_State_S, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_S, L2Cache_Event_L2_Replacement_clean);
  s_profiler.possibleTransition(L2Cache_State_SS, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_SS, L2Cache_Event_L2_Replacement_clean);
  s_profiler.possibleTransition(L2Cache_State_SS, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_E, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_E, L2Cache_Event_L1_Upgrade_NT);
  s_profiler.possibleTransition(L2Cache_State_E, L2Cache_Event_L2_Atomic);
  s_profiler.possibleTransition(L2Cache_State_E, L2Cache_Event_L2_Replacement_clean);
  s_profiler.possibleTransition(L2Cache_State_E, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_MI, L2Cache_Event_L2_Expire);
  s_profiler.possibleTransition(L2Cache_State_MI_Ack, L2Cache_Event_WB_Ack);
  s_profiler.possibleTransition(L2Cache_State_IS, L2Cache_Event_L1_Write);
  s_profiler.possibleTransition(L2Cache_State_IS, L2Cache_Event_L1_Upgrade_NT);
  s_profiler.possibleTransition(L2Cache_State_IS, L2Cache_Event_L2_Atomic);
  s_profiler.possibleTransition(L2Cache_State_IM, L2Cache_Event_L1_Write);
  s_profiler.possibleTransition(L2Cache_State_IM, L2Cache_Event_L1_Upgrade_NT);
  s_profiler.possibleTransition(L2Cache_State_IM, L2Cache_Event_L2_Atomic);
  s_profiler.possibleTransition(L2Cache_State_IMA, L2Cache_Event_L1_Write);
  s_profiler.possibleTransition(L2Cache_State_IMA, L2Cache_Event_L1_Upgrade_NT);
  s_profiler.possibleTransition(L2Cache_State_IMA, L2Cache_Event_L2_Atomic);
  s_profiler.possibleTransition(L2Cache_State_MI, L2Cache_Event_L1_Write);
  s_profiler.possibleTransition(L2Cache_State_MI, L2Cache_Event_L1_Upgrade_NT);
  s_profiler.possibleTransition(L2Cache_State_MI, L2Cache_Event_L2_Atomic);
  s_profiler.possibleTransition(L2Cache_State_MI_Ack, L2Cache_Event_L1_Write);
  s_profiler.possibleTransition(L2Cache_State_MI_Ack, L2Cache_Event_L1_Upgrade_NT);
  s_profiler.possibleTransition(L2Cache_State_MI_Ack, L2Cache_Event_L2_Atomic);
  s_profiler.possibleTransition(L2Cache_State_IM, L2Cache_Event_Data);
  s_profiler.possibleTransition(L2Cache_State_IMA, L2Cache_Event_Data);
  s_profiler.possibleTransition(L2Cache_State_IS, L2Cache_Event_Data);
  s_profiler.possibleTransition(L2Cache_State_ISS, L2Cache_Event_Data);
  s_profiler.possibleTransition(L2Cache_State_IM, L2Cache_Event_Data_all_Acks);
  s_profiler.possibleTransition(L2Cache_State_IMA, L2Cache_Event_Data_all_Acks);
  s_profiler.possibleTransition(L2Cache_State_IS, L2Cache_Event_Data_all_Acks);
  s_profiler.possibleTransition(L2Cache_State_ISS, L2Cache_Event_Data_all_Acks);
  s_profiler.possibleTransition(L2Cache_State_IMA, L2Cache_Event_Ack);
  s_profiler.possibleTransition(L2Cache_State_IM, L2Cache_Event_Ack);
  s_profiler.possibleTransition(L2Cache_State_IS, L2Cache_Event_Ack);
  s_profiler.possibleTransition(L2Cache_State_ISS, L2Cache_Event_Ack);
  s_profiler.possibleTransition(L2Cache_State_IMA, L2Cache_Event_Ack_all);
  s_profiler.possibleTransition(L2Cache_State_IM, L2Cache_Event_Ack_all);
  s_profiler.possibleTransition(L2Cache_State_IS, L2Cache_Event_Ack_all);
  s_profiler.possibleTransition(L2Cache_State_ISS, L2Cache_Event_Ack_all);
  s_profiler.possibleTransition(L2Cache_State_SS, L2Cache_Event_Fwd_GETX);
  s_profiler.possibleTransition(L2Cache_State_SS, L2Cache_Event_Fwd_GETS);
  s_profiler.possibleTransition(L2Cache_State_SS, L2Cache_Event_Inv);
  s_profiler.possibleTransition(L2Cache_State_S, L2Cache_Event_Fwd_GETX);
  s_profiler.possibleTransition(L2Cache_State_S, L2Cache_Event_Fwd_GETS);
  s_profiler.possibleTransition(L2Cache_State_S, L2Cache_Event_Inv);
  s_profiler.possibleTransition(L2Cache_State_E, L2Cache_Event_Inv);
}

void L2Cache_Controller::print(ostream& out) const { out << "[L2Cache_Controller " << m_chip_ptr->getID() << " " << m_version << "]"; }

// Actions

/** \brief fetch data from memory*/
void L2Cache_Controller::a_issueFetchToMemory(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_GETX;
      (out_msg).m_Requestor = m_machineID;
      (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
      (out_msg).m_OriginalRequestorMachId = m_machineID;
      (out_msg).m_MessageSize = MessageSizeType_Control;
      ((*(m_chip_ptr->m_L2Cache_requestFromL2TCache_vec[m_version]))).enqueue(out_msg, L2_to_MEM_MSG_LATENCY);
    }
  }
}

/** \brief fetch data from memory for store*/
void L2Cache_Controller::a_issueFetchToMemoryForStore(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_GETX;
      (out_msg).m_Requestor = m_machineID;
      (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
      (out_msg).m_OriginalRequestorMachId = m_machineID;
      (out_msg).m_MessageSize = MessageSizeType_Control;
      ((*(m_chip_ptr->m_L2Cache_requestFromL2TCache_vec[m_version]))).enqueue(out_msg, L2_to_MEM_MSG_LATENCY);
    }
  }
}

/** \brief send data to the L2 cache (PUTX)*/
void L2Cache_Controller::c_exclusiveReplacement(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if (((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Dirty) {
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_Dirty = ((L2Cache_getL2CacheEntry(addr))).m_Dirty;
      (out_msg).m_Sender = m_machineID;
      (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
      (out_msg).m_Type = CoherenceResponseType_DATA_ACC;
      (out_msg).m_MessageSize = MessageSizeType_Data;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2TCache_vec[m_version]))).enqueue(out_msg, L1_to_L2_DATA_LATENCY);
    }
  } else {
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_Dirty = ((L2Cache_getL2CacheEntry(addr))).m_Dirty;
      (out_msg).m_Requestor = m_machineID;
      (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
      (out_msg).m_Type = CoherenceRequestType_PUTX_ACC;
      (out_msg).m_MessageSize = MessageSizeType_Writeback_Control;
      ((*(m_chip_ptr->m_L2Cache_requestFromL2TCache_vec[m_version]))).enqueue(out_msg, L1_to_L2_DATA_LATENCY);
    }
  }
}

/** \brief Send data+timestamp from cache to requestor in request queue*/
void L2Cache_Controller::ds_sendDataToRequestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
        if (ASSERT_FLAG && !(((time_to_int(((L2Cache_getL2CacheEntry(addr))).m_liveUntilTime)) >= (time_to_int((get_time())))))) {
      cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:515, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

    }
;
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_Sender = m_machineID;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_Requestor));
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_Dirty = ((L2Cache_getL2CacheEntry(addr))).m_Dirty;
      (out_msg).m_MessageSize = (IntToMessageSizeType(((*in_msg_ptr)).m_RequestSize));
      (out_msg).m_AckCount = (0);
      (out_msg).m_Space = ((*in_msg_ptr)).m_Space;
      (out_msg).m_RequestSize = ((*in_msg_ptr)).m_RequestSize;
      (out_msg).m_liveUntilTime = ((L2Cache_getL2CacheEntry(addr))).m_liveUntilTime;
      (((out_msg).m_mfset).insert(((*in_msg_ptr)).m_Requestor, ((*in_msg_ptr)).m_memfetch));
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_to_L1_DATA_LATENCY);
    }
  }
}

/** \brief Send data+timestamp from cache to all GetS IDs from TBE*/
void L2Cache_Controller::dst_sendDataToGetSRequestors(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
    if (ASSERT_FLAG && !((((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs).count()) > (0)))) {
    cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:534, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

  }
;
    if (ASSERT_FLAG && !(((time_to_int(((L2Cache_getL2CacheEntry(addr))).m_liveUntilTime)) >= (time_to_int((get_time())))))) {
    cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:535, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

  }
;
  {
    ResponseMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceResponseType_DATA;
    (out_msg).m_Sender = m_machineID;
    (out_msg).m_Destination = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs;
    (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
    (out_msg).m_Dirty = ((L2Cache_getL2CacheEntry(addr))).m_Dirty;
    (out_msg).m_MessageSize = (IntToMessageSizeType(((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_RequestSize));
    (out_msg).m_Space = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Space;
    (out_msg).m_RequestSize = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_RequestSize;
        if (ASSERT_FLAG && !((L2Cache_isL2CacheTagPresent(addr)))) {
      cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:546, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

    }
;
    (out_msg).m_liveUntilTime = ((L2Cache_getL2CacheEntry(addr))).m_liveUntilTime;
    (out_msg).m_mfset = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_mfset;
    ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_to_L1_DATA_LATENCY);
  }
}

/** \brief Send atomic data from cache to requestor in response queue*/
void L2Cache_Controller::ds_sendAtomicDataGlobalToRequestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA_ATOMIC;
      (out_msg).m_Sender = m_machineID;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_Requestor));
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_Dirty = ((L2Cache_getL2CacheEntry(addr))).m_Dirty;
      (out_msg).m_MessageSize = (IntToMessageSizeType(((*in_msg_ptr)).m_RequestSize));
      (out_msg).m_AckCount = (0);
      (out_msg).m_Space = ((*in_msg_ptr)).m_Space;
      (out_msg).m_RequestSize = ((*in_msg_ptr)).m_RequestSize;
      (out_msg).m_liveUntilTime = ((L2Cache_getL2CacheEntry(addr))).m_liveUntilTime;
      (out_msg).m_memfetch = ((*in_msg_ptr)).m_memfetch;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_to_L1_DATA_LATENCY);
    }
  }
}

/** \brief Send atomic data + timestamp from cache to requestor from TBE*/
void L2Cache_Controller::dst_sendAtomicDataToGetSRequestors(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    ResponseMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceResponseType_DATA_ATOMIC;
    (out_msg).m_Sender = m_machineID;
    (((out_msg).m_Destination).add(((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_WBAck_ID));
    (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
    (out_msg).m_Dirty = ((L2Cache_getL2CacheEntry(addr))).m_Dirty;
    (out_msg).m_MessageSize = (IntToMessageSizeType(((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_RequestSize));
    (out_msg).m_Space = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Space;
    (out_msg).m_RequestSize = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_RequestSize;
        if (ASSERT_FLAG && !((L2Cache_isL2CacheTagPresent(addr)))) {
      cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:582, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

    }
;
    (out_msg).m_liveUntilTime = ((L2Cache_getL2CacheEntry(addr))).m_liveUntilTime;
    (out_msg).m_memfetch = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_memfetch;
    ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_to_L1_DATA_LATENCY);
  }
}

/** \brief Send Ack (non-global) from cache to requestor*/
void L2Cache_Controller::wa_sendAckToRequestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_ACK;
      (out_msg).m_Sender = m_machineID;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_Requestor));
      (out_msg).m_MessageSize = MessageSizeType_Response_Control;
      (out_msg).m_Space = ((*in_msg_ptr)).m_Space;
      (out_msg).m_RequestSize = ((*in_msg_ptr)).m_RequestSize;
      (out_msg).m_liveUntilTime = ((L2Cache_getL2CacheEntry(addr))).m_liveUntilTime;
      (out_msg).m_memfetch = ((*in_msg_ptr)).m_memfetch;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_to_L1_MSG_LATENCY);
    }
  }
}

/** \brief Send ack (non-global) from cache to requestor from TBE*/
void L2Cache_Controller::wat_sendAckToRequestorFromTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    ResponseMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceResponseType_ACK;
    (out_msg).m_Sender = m_machineID;
    (((out_msg).m_Destination).add(((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_WBAck_ID));
    (out_msg).m_MessageSize = MessageSizeType_Response_Control;
    (out_msg).m_Space = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Space;
    (out_msg).m_RequestSize = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_RequestSize;
        if (ASSERT_FLAG && !((L2Cache_isL2CacheTagPresent(addr)))) {
      cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:613, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

    }
;
    (out_msg).m_liveUntilTime = ((L2Cache_getL2CacheEntry(addr))).m_liveUntilTime;
    (out_msg).m_memfetch = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_memfetch;
    ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_to_L1_MSG_LATENCY);
  }
}

/** \brief Allocate TBE from L1 request queue*/
void L2Cache_Controller::i_allocateTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).allocate(addr));
    ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs).clear());
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Dirty = ((L2Cache_getL2CacheEntry(addr))).m_Dirty;
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Space = ((*in_msg_ptr)).m_Space;
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_RequestSize = ((*in_msg_ptr)).m_RequestSize;
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_deltaRequested = ((*in_msg_ptr)).m_deltaRequested;
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_memfetch = ((*in_msg_ptr)).m_memfetch;
  }
}

/** \brief Allocate TBE from L1 response queue*/
void L2Cache_Controller::il_allocateTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).allocate(addr));
    ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs).clear());
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Dirty = ((L2Cache_getL2CacheEntry(addr))).m_Dirty;
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_RequestSize = ((*in_msg_ptr)).m_RequestSize;
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Space = ((*in_msg_ptr)).m_Space;
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_memfetch = ((*in_msg_ptr)).m_memfetch;
  }
}

/** \brief Allocate TBE for L2 replacement*/
void L2Cache_Controller::ir_allocateTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).allocate(addr));
  ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs).clear());
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Dirty = ((L2Cache_getL2CacheEntry(addr))).m_Dirty;
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_liveUntilTime = ((L2Cache_getL2CacheEntry(addr))).m_liveUntilTime;
}

/** \brief Insert expire event into L2 expire trigger queue*/
void L2Cache_Controller::it_insertL2ExpireTriggerQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    L2ExpireTriggerMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_ExpireTime = (getTimePlusInt(((L2Cache_getL2CacheEntry(addr))).m_liveUntilTime, (1)));
        if (ASSERT_FLAG && !(((time_to_int((out_msg).m_ExpireTime)) > (time_to_int((get_time())))))) {
      cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:662, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

    }
;
    ((*(m_chip_ptr->m_L2Cache_L2ExpireTriggerQueue_vec[m_version]))).enqueue(out_msg, (out_msg).m_ExpireTime-get_time());
  }
}

/** \brief Deallocate external TBE*/
void L2Cache_Controller::s_deallocateTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).deallocate(addr));
}

/** \brief Pop incoming L1 request queue*/
void L2Cache_Controller::jj_popL1RequestQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETS)) {
      (profileBandwidth(("L1_MSG"), ((*in_msg_ptr)).m_MessageSize));
    } else {
      if (((((*in_msg_ptr)).m_Type == CoherenceRequestType_DATA) || (((*in_msg_ptr)).m_Type == CoherenceRequestType_DATA_UPGRADE))) {
        (profileBandwidth(("L1_DATA"), ((*in_msg_ptr)).m_MessageSize));
      } else {
        if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_DATA_ATOMIC)) {
          (profileBandwidth(("L1_ATOMIC"), ((*in_msg_ptr)).m_MessageSize));
        } else {
                    cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:680, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid CacheResponseType") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
        }
      }
    }
  }
  (((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).dequeue());
}

/** \brief Pop Incoming Response queue*/
void L2Cache_Controller::o_popIncomingCPUResponseQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_responseToL2TCache_vec[m_version]))).dequeue());
}

/** \brief Pop Incoming Response queue*/
void L2Cache_Controller::o_popIncomingCPURequestQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_requestToL2TCache_vec[m_version]))).dequeue());
}

/** \brief Pop L2 Expire Trigger Queue*/
void L2Cache_Controller::o_popL2ExpireTriggerQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_L2ExpireTriggerQueue_vec[m_version]))).dequeue());
}

/** \brief Write data from mem response queue to cache*/
void L2Cache_Controller::m_writeDataToCache(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2TCache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((L2Cache_getL2CacheEntry(addr))).m_DataBlk = ((*in_msg_ptr)).m_DataBlk;
  }
}

/** \brief Write data from L1 response queue to cache*/
void L2Cache_Controller::mr_writeDataToCacheFromRequest(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
        if (ASSERT_FLAG && !((((*in_msg_ptr)).m_Dirty == (true)))) {
      cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:709, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

    }
;
    ((L2Cache_getL2CacheEntry(addr))).m_DataBlk = ((*in_msg_ptr)).m_DataBlk;
    ((L2Cache_getL2CacheEntry(addr))).m_Dirty = ((*in_msg_ptr)).m_Dirty;
  }
}

/** \brief Write data from TBE to cache (for WB stores)*/
void L2Cache_Controller::mt_writeDataToCacheFromTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
    if (ASSERT_FLAG && !((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Dirty == (true)))) {
    cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:717, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

  }
;
  ((L2Cache_getL2CacheEntry(addr))).m_DataBlk = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_DataBlk;
  ((L2Cache_getL2CacheEntry(addr))).m_Dirty = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Dirty;
}

/** \brief Record L1 GetS for load response*/
void L2Cache_Controller::ss_recordGetSL1ID(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
        if (ASSERT_FLAG && !((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Space == ((*in_msg_ptr)).m_Space))) {
      cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:724, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

    }
;
    ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs).add(((*in_msg_ptr)).m_Requestor));
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_RequestSize = (getIntMax(((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_RequestSize, ((*in_msg_ptr)).m_RequestSize));
    ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_mfset).insert(((*in_msg_ptr)).m_Requestor, ((*in_msg_ptr)).m_memfetch));
  }
}

/** \brief set the MRU entry*/
void L2Cache_Controller::set_setMRU(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).setMRU(addr));
}

/** \brief Set L2 cache tag equal to tag of block B.*/
void L2Cache_Controller::qq_allocateL2CacheBlock(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).isTagPresent(addr)) == (false))) {
    (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).allocate(addr));
  }
}

/** \brief Extend the lifetime of the L2 block according to request*/
void L2Cache_Controller::t_updateL2BlockTime(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((L2Cache_getL2CacheEntry(addr))).m_liveUntilTime = (getTimeMax((getTimePlusTime((get_time()), ((*in_msg_ptr)).m_deltaRequested)), ((L2Cache_getL2CacheEntry(addr))).m_liveUntilTime));
  }
}

/** \brief Increment the L2 time stamp (on writes)*/
void L2Cache_Controller::ti_incrementL2BlockTime(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((L2Cache_getL2CacheEntry(addr))).m_liveUntilTime = (getTimePlusInt(((L2Cache_getL2CacheEntry(addr))).m_liveUntilTime, (1)));
}

/** \brief Extend the lifetime of the L2 block according to request in TBE*/
void L2Cache_Controller::tt_updateL2BlockTime_fromTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((L2Cache_getL2CacheEntry(addr))).m_liveUntilTime = (getTimeMax((getTimePlusTime((get_time()), ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_deltaRequested)), ((L2Cache_getL2CacheEntry(addr))).m_liveUntilTime));
}

/** \brief Set the L2 expire time to now (expire it)*/
void L2Cache_Controller::tn_expireL2BlockTime(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((L2Cache_getL2CacheEntry(addr))).m_liveUntilTime = (get_time());
}

/** \brief Mark block as dirty*/
void L2Cache_Controller::d_markBlockDirty(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((L2Cache_getL2CacheEntry(addr))).m_Dirty = (true);
}

/** \brief Mark block as dirty*/
void L2Cache_Controller::d_markTBEDataReady(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_DataReady = (true);
}

/** \brief Deallocate L2 cache block.  Sets the cache to not present, allowing a replacement in parallel with a fetch.*/
void L2Cache_Controller::rr_deallocateL2CacheBlock(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).deallocate(addr));
}

/** \brief Record L1 WB for store response*/
void L2Cache_Controller::xx_recordGetXL1ID(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/FUSION/cachelease2-L2cache_m.sm:774: ", addr);
;
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_WBAck_ID = ((*in_msg_ptr)).m_Requestor;
  }
  DEBUG_SLICC(MedPrio, "../protocols/FUSION/cachelease2-L2cache_m.sm:778: ", addr);
;
}

/** \brief Update ack count*/
void L2Cache_Controller::q_updateAckCount(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_requestToL2TCache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_pendingAcks = (((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_pendingAcks - ((*in_msg_ptr)).m_AckCount);
    APPEND_TRANSITION_COMMENT(((*in_msg_ptr)).m_AckCount);
;
    APPEND_TRANSITION_COMMENT((" p: "));
;
    APPEND_TRANSITION_COMMENT(((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_pendingAcks);
;
  }
}

/** \brief recycle L1 request queue*/
void L2Cache_Controller::zz_recycleL1RequestQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).recycle());
}

/** \brief recycle L1 response queue*/
void L2Cache_Controller::zc_recycleL1ResponseNetwork(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).recycle());
}

/** \brief stall - i.e. do nothing*/
void L2Cache_Controller::z_stall(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
}

/** \brief Profile a demand miss for request message*/
void L2Cache_Controller::pM_profileRequestMiss(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (profile_L2Cache_request_g((m_chip_ptr->convertRequestToGenericType(((*in_msg_ptr)).m_Type)), ((*in_msg_ptr)).m_MessageSize, m_chip_ptr->getID(), (true)));
  }
}

/** \brief Profile a demand hit for request message*/
void L2Cache_Controller::pH_profileRequestHit(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (profile_L2Cache_request_g((m_chip_ptr->convertRequestToGenericType(((*in_msg_ptr)).m_Type)), ((*in_msg_ptr)).m_MessageSize, m_chip_ptr->getID(), (false)));
  }
}

/** \brief Profile a demand miss for response message*/
void L2Cache_Controller::pM_profileResponseMiss(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (profile_L2Cache_request_g((m_chip_ptr->convertRequestToGenericType(((*in_msg_ptr)).m_Type)), ((*in_msg_ptr)).m_MessageSize, m_chip_ptr->getID(), (true)));
  }
}

/** \brief Profile a demand hit for response message*/
void L2Cache_Controller::pH_profileResponseHit(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (profile_L2Cache_request_g((m_chip_ptr->convertRequestToGenericType(((*in_msg_ptr)).m_Type)), ((*in_msg_ptr)).m_MessageSize, m_chip_ptr->getID(), (false)));
  }
}

