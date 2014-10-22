/** \file L1Cache.C
  * 
  * Auto generated C++ code started by symbols/StateMachine.C:327
  * Created by slicc definition of Module "MESI Directory L1 Cache CMP"
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
  (*(m_chip_ptr->m_L1Cache_requestToL1Cache_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version])).setConsumer(this);


  s_profiler.possibleTransition(L1Cache_State_IS, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_IS, L1Cache_Event_Ifetch);
  s_profiler.possibleTransition(L1Cache_State_IS, L1Cache_Event_Store);
  s_profiler.possibleTransition(L1Cache_State_IM, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_IM, L1Cache_Event_Ifetch);
  s_profiler.possibleTransition(L1Cache_State_IM, L1Cache_Event_Store);
  s_profiler.possibleTransition(L1Cache_State_IS_I, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_IS_I, L1Cache_Event_Ifetch);
  s_profiler.possibleTransition(L1Cache_State_IS_I, L1Cache_Event_Store);
  s_profiler.possibleTransition(L1Cache_State_M_I, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_M_I, L1Cache_Event_Ifetch);
  s_profiler.possibleTransition(L1Cache_State_M_I, L1Cache_Event_Store);
  s_profiler.possibleTransition(L1Cache_State_E_I, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_E_I, L1Cache_Event_Ifetch);
  s_profiler.possibleTransition(L1Cache_State_E_I, L1Cache_Event_Store);
  s_profiler.possibleTransition(L1Cache_State_SM, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_SM, L1Cache_Event_Ifetch);
  s_profiler.possibleTransition(L1Cache_State_SM, L1Cache_Event_Store);
  s_profiler.possibleTransition(L1Cache_State_IS, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_IM, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_IS_I, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_M_I, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_E_I, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_SM, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_NP, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_I, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_NP, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_I, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_NP, L1Cache_Event_Ifetch);
  s_profiler.possibleTransition(L1Cache_State_I, L1Cache_Event_Ifetch);
  s_profiler.possibleTransition(L1Cache_State_NP, L1Cache_Event_Store);
  s_profiler.possibleTransition(L1Cache_State_I, L1Cache_Event_Store);
  s_profiler.possibleTransition(L1Cache_State_NP, L1Cache_Event_Inv);
  s_profiler.possibleTransition(L1Cache_State_I, L1Cache_Event_Inv);
  s_profiler.possibleTransition(L1Cache_State_S, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_S, L1Cache_Event_Ifetch);
  s_profiler.possibleTransition(L1Cache_State_S, L1Cache_Event_Store);
  s_profiler.possibleTransition(L1Cache_State_S, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_S, L1Cache_Event_Inv);
  s_profiler.possibleTransition(L1Cache_State_E, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_E, L1Cache_Event_Ifetch);
  s_profiler.possibleTransition(L1Cache_State_E, L1Cache_Event_Store);
  s_profiler.possibleTransition(L1Cache_State_E, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_E, L1Cache_Event_Inv);
  s_profiler.possibleTransition(L1Cache_State_E, L1Cache_Event_Fwd_GETX);
  s_profiler.possibleTransition(L1Cache_State_E, L1Cache_Event_Fwd_GETS);
  s_profiler.possibleTransition(L1Cache_State_E, L1Cache_Event_Fwd_GET_INSTR);
  s_profiler.possibleTransition(L1Cache_State_M, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_M, L1Cache_Event_Ifetch);
  s_profiler.possibleTransition(L1Cache_State_M, L1Cache_Event_Store);
  s_profiler.possibleTransition(L1Cache_State_M, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_M_I, L1Cache_Event_WB_Ack);
  s_profiler.possibleTransition(L1Cache_State_M, L1Cache_Event_Inv);
  s_profiler.possibleTransition(L1Cache_State_M_I, L1Cache_Event_Inv);
  s_profiler.possibleTransition(L1Cache_State_M, L1Cache_Event_Fwd_GETX);
  s_profiler.possibleTransition(L1Cache_State_M, L1Cache_Event_Fwd_GETS);
  s_profiler.possibleTransition(L1Cache_State_M, L1Cache_Event_Fwd_GET_INSTR);
  s_profiler.possibleTransition(L1Cache_State_M_I, L1Cache_Event_Fwd_GETX);
  s_profiler.possibleTransition(L1Cache_State_M_I, L1Cache_Event_Fwd_GETS);
  s_profiler.possibleTransition(L1Cache_State_M_I, L1Cache_Event_Fwd_GET_INSTR);
  s_profiler.possibleTransition(L1Cache_State_IS, L1Cache_Event_Inv);
  s_profiler.possibleTransition(L1Cache_State_IS_I, L1Cache_Event_Inv);
  s_profiler.possibleTransition(L1Cache_State_IS, L1Cache_Event_Data_all_Acks);
  s_profiler.possibleTransition(L1Cache_State_IS_I, L1Cache_Event_Data_all_Acks);
  s_profiler.possibleTransition(L1Cache_State_IS, L1Cache_Event_DataS_fromL1);
  s_profiler.possibleTransition(L1Cache_State_IS_I, L1Cache_Event_DataS_fromL1);
  s_profiler.possibleTransition(L1Cache_State_IS_I, L1Cache_Event_Data_Exclusive);
  s_profiler.possibleTransition(L1Cache_State_IS, L1Cache_Event_Data_Exclusive);
  s_profiler.possibleTransition(L1Cache_State_IM, L1Cache_Event_Inv);
  s_profiler.possibleTransition(L1Cache_State_SM, L1Cache_Event_Inv);
  s_profiler.possibleTransition(L1Cache_State_IM, L1Cache_Event_Data);
  s_profiler.possibleTransition(L1Cache_State_IM, L1Cache_Event_Data_all_Acks);
  s_profiler.possibleTransition(L1Cache_State_SM, L1Cache_Event_Ack);
  s_profiler.possibleTransition(L1Cache_State_IM, L1Cache_Event_Ack);
  s_profiler.possibleTransition(L1Cache_State_SM, L1Cache_Event_Ack_all);
  s_profiler.possibleTransition(L1Cache_State_SINK_WB_ACK, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_SINK_WB_ACK, L1Cache_Event_Store);
  s_profiler.possibleTransition(L1Cache_State_SINK_WB_ACK, L1Cache_Event_Ifetch);
  s_profiler.possibleTransition(L1Cache_State_SINK_WB_ACK, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_SINK_WB_ACK, L1Cache_Event_Inv);
  s_profiler.possibleTransition(L1Cache_State_SINK_WB_ACK, L1Cache_Event_WB_Ack);
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
      DEBUG_SLICC(MedPrio, "../protocols/FUSION/MESI_CMP_directory-L1cache.sm:370: ", addr);
;
      DEBUG_SLICC(MedPrio, "../protocols/FUSION/MESI_CMP_directory-L1cache.sm:371: ", (out_msg).m_Destination);
;
      (out_msg).m_MessageSize = MessageSizeType_Control;
      (out_msg).m_Prefetch = ((*in_msg_ptr)).m_Prefetch;
      (out_msg).m_AccessMode = ((*in_msg_ptr)).m_AccessMode;
      ((*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_MSG_LATENCY);
    }
  }
}

/** \brief Issue GETINSTR*/
void L1Cache_Controller::ai_issueGETINSTR(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_GET_INSTR;
      (out_msg).m_Requestor = m_machineID;
      (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
      DEBUG_SLICC(MedPrio, "../protocols/FUSION/MESI_CMP_directory-L1cache.sm:386: ", addr);
;
      DEBUG_SLICC(MedPrio, "../protocols/FUSION/MESI_CMP_directory-L1cache.sm:387: ", (out_msg).m_Destination);
;
      (out_msg).m_MessageSize = MessageSizeType_Control;
      (out_msg).m_Prefetch = ((*in_msg_ptr)).m_Prefetch;
      (out_msg).m_AccessMode = ((*in_msg_ptr)).m_AccessMode;
      ((*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_MSG_LATENCY);
    }
  }
}

/** \brief Issue GETX*/
void L1Cache_Controller::b_issueGETX(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_GETX;
      (out_msg).m_Requestor = m_machineID;
      DEBUG_SLICC(MedPrio, "../protocols/FUSION/MESI_CMP_directory-L1cache.sm:402: ", m_machineID);
;
      (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
      DEBUG_SLICC(MedPrio, "../protocols/FUSION/MESI_CMP_directory-L1cache.sm:404: ", addr);
;
      DEBUG_SLICC(MedPrio, "../protocols/FUSION/MESI_CMP_directory-L1cache.sm:405: ", (out_msg).m_Destination);
;
      (out_msg).m_MessageSize = MessageSizeType_Control;
      (out_msg).m_Prefetch = ((*in_msg_ptr)).m_Prefetch;
      (out_msg).m_AccessMode = ((*in_msg_ptr)).m_AccessMode;
      ((*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_MSG_LATENCY);
    }
  }
}

/** \brief Issue Upgrade*/
void L1Cache_Controller::c_issueUPGRADE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_UPGRADE;
      (out_msg).m_Requestor = m_machineID;
      (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
      DEBUG_SLICC(MedPrio, "../protocols/FUSION/MESI_CMP_directory-L1cache.sm:420: ", addr);
;
      DEBUG_SLICC(MedPrio, "../protocols/FUSION/MESI_CMP_directory-L1cache.sm:421: ", (out_msg).m_Destination);
;
      (out_msg).m_MessageSize = MessageSizeType_Control;
      (out_msg).m_Prefetch = ((*in_msg_ptr)).m_Prefetch;
      (out_msg).m_AccessMode = ((*in_msg_ptr)).m_AccessMode;
      ((*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_MSG_LATENCY);
    }
  }
}

/** \brief send data to requestor*/
void L1Cache_Controller::d_sendDataToRequestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L1Cache_requestToL1Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_DataBlk = ((L1Cache_getL1CacheEntry(addr))).m_DataBlk;
      (out_msg).m_Dirty = ((L1Cache_getL1CacheEntry(addr))).m_Dirty;
      (out_msg).m_Sender = m_machineID;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_Requestor));
      (out_msg).m_MessageSize = MessageSizeType_Response_Data;
      (out_msg).m_DirtyMask = ((L1Cache_getL1CacheEntry(addr))).m_DirtyMask;
      ((*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_DATA_LATENCY);
    }
  }
}

/** \brief send data to the L2 cache because of M downgrade*/
void L1Cache_Controller::d2_sendDataToL2(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    ResponseMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceResponseType_DATA;
    (out_msg).m_DataBlk = ((L1Cache_getL1CacheEntry(addr))).m_DataBlk;
    (out_msg).m_Dirty = ((L1Cache_getL1CacheEntry(addr))).m_Dirty;
    (out_msg).m_Sender = m_machineID;
    (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
    (out_msg).m_MessageSize = MessageSizeType_Response_Data;
    (out_msg).m_DirtyMask = ((L1Cache_getL1CacheEntry(addr))).m_DirtyMask;
    ((*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_DATA_LATENCY);
  }
}

/** \brief send data to requestor*/
void L1Cache_Controller::dt_sendDataToRequestor_fromTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L1Cache_requestToL1Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_DataBlk = ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_DataBlk;
      (out_msg).m_Dirty = ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_Dirty;
      (out_msg).m_Sender = m_machineID;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_Requestor));
      (out_msg).m_MessageSize = MessageSizeType_Response_Data;
      (out_msg).m_DirtyMask = ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_AccessMask;
      ((*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_DATA_LATENCY);
    }
  }
}

/** \brief send data to the L2 cache from TBE*/
void L1Cache_Controller::d2t_sendDataToL2_fromTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    ResponseMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceResponseType_DATA;
    (out_msg).m_DataBlk = ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_DataBlk;
    (out_msg).m_Dirty = ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_Dirty;
    (out_msg).m_Sender = m_machineID;
    (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
    (out_msg).m_MessageSize = MessageSizeType_Response_Data;
    (out_msg).m_DirtyMask = ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_AccessMask;
    ((*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_DATA_LATENCY);
  }
}

/** \brief Update dirty mask from a sequencer request.*/
void L1Cache_Controller::dm_from_seq(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((L1Cache_getL1CacheEntry(addr))).m_DirtyMask = (or_byte_masks(((L1Cache_getL1CacheEntry(addr))).m_DirtyMask, ((*in_msg_ptr)).m_AccessMask));
  }
}

/** \brief Update dirty mask from a TBE.*/
void L1Cache_Controller::dm_from_tbe(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((L1Cache_getL1CacheEntry(addr))).m_DirtyMask = (or_byte_masks(((L1Cache_getL1CacheEntry(addr))).m_DirtyMask, ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_AccessMask));
}

/** \brief Update dirty mask from a ResponseMsg (might have been forwarded and not seen by L2).*/
void L1Cache_Controller::dm_from_resp(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((L1Cache_getL1CacheEntry(addr))).m_DirtyMask = (or_byte_masks(((L1Cache_getL1CacheEntry(addr))).m_DirtyMask, ((*in_msg_ptr)).m_DirtyMask));
  }
}

/** \brief send data to the L2 cache*/
void L1Cache_Controller::f_sendDataToL2(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    ResponseMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceResponseType_DATA;
    (out_msg).m_DataBlk = ((L1Cache_getL1CacheEntry(addr))).m_DataBlk;
    (out_msg).m_Dirty = ((L1Cache_getL1CacheEntry(addr))).m_Dirty;
    (out_msg).m_Sender = m_machineID;
    (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
    (out_msg).m_MessageSize = MessageSizeType_Writeback_Data;
    (out_msg).m_DirtyMask = ((L1Cache_getL1CacheEntry(addr))).m_DirtyMask;
    ((*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_DATA_LATENCY);
  }
}

/** \brief send data to the L2 cache from TBE*/
void L1Cache_Controller::ft_sendDataToL2_fromTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    ResponseMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceResponseType_DATA;
    (out_msg).m_DataBlk = ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_DataBlk;
    (out_msg).m_Dirty = ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_Dirty;
    (out_msg).m_Sender = m_machineID;
    (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
    (out_msg).m_MessageSize = MessageSizeType_Writeback_Data;
    (out_msg).m_DirtyMask = ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_AccessMask;
    ((*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_DATA_LATENCY);
  }
}

/** \brief send invalidate ack*/
void L1Cache_Controller::fi_sendInvAck(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L1Cache_requestToL1Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_ACK;
      (out_msg).m_Sender = m_machineID;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_Requestor));
      (out_msg).m_MessageSize = MessageSizeType_Response_Control;
      (out_msg).m_AckCount = (1);
      ((*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_MSG_LATENCY);
    }
  }
}

/** \brief send data to the L2 cache (PUTX)*/
void L1Cache_Controller::g_issuePUTX(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    RequestMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceRequestType_PUTX;
    (out_msg).m_DataBlk = ((L1Cache_getL1CacheEntry(addr))).m_DataBlk;
    (out_msg).m_Dirty = ((L1Cache_getL1CacheEntry(addr))).m_Dirty;
    (out_msg).m_Requestor = m_machineID;
    (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
    if (((L1Cache_getL1CacheEntry(addr))).m_Dirty) {
      (out_msg).m_MessageSize = MessageSizeType_Writeback_Data;
    } else {
      (out_msg).m_MessageSize = MessageSizeType_Writeback_Control;
    }
    (out_msg).m_DirtyMask = ((L1Cache_getL1CacheEntry(addr))).m_DirtyMask;
    ((*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_DATA_LATENCY);
  }
}

/** \brief send unblock to the L2 cache*/
void L1Cache_Controller::j_sendUnblock(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    ResponseMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceResponseType_UNBLOCK;
    (out_msg).m_Sender = m_machineID;
    (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
    (out_msg).m_MessageSize = MessageSizeType_Response_Control;
    ((*(m_chip_ptr->m_L1Cache_unblockFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_MSG_LATENCY);
  }
}

/** \brief send exclusive unblock to the L2 cache*/
void L1Cache_Controller::jj_sendExclusiveUnblock(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    ResponseMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceResponseType_EXCLUSIVE_UNBLOCK;
    (out_msg).m_Sender = m_machineID;
    (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
    (out_msg).m_MessageSize = MessageSizeType_Response_Control;
    ((*(m_chip_ptr->m_L1Cache_unblockFromL1Cache_vec[m_version]))).enqueue(out_msg, L1_to_L2_MSG_LATENCY);
  }
}

/** \brief If not prefetch, notify sequencer the load completed.*/
void L1Cache_Controller::h_load_hit(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/FUSION/MESI_CMP_directory-L1cache.sm:595: ", ((L1Cache_getL1CacheEntry(addr))).m_DataBlk);
;
  ((*(dynamic_cast<Sequencer*>(m_chip_ptr->getSequencer(m_version)))).readCallback(addr, ((L1Cache_getL1CacheEntry(addr))).m_DataBlk));
}

/** \brief If not prefetch, notify sequencer that store completed.*/
void L1Cache_Controller::hh_store_hit(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/FUSION/MESI_CMP_directory-L1cache.sm:600: ", ((L1Cache_getL1CacheEntry(addr))).m_DataBlk);
;
  ((*(dynamic_cast<Sequencer*>(m_chip_ptr->getSequencer(m_version)))).writeCallback(addr, ((L1Cache_getL1CacheEntry(addr))).m_DataBlk));
  ((L1Cache_getL1CacheEntry(addr))).m_Dirty = (true);
}

/** \brief Allocate TBE (isPrefetch=0, number of invalidates=0)*/
void L1Cache_Controller::i_allocateTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).allocate(addr));
  ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_isPrefetch = (false);
  ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_Dirty = ((L1Cache_getL1CacheEntry(addr))).m_Dirty;
  ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_DataBlk = ((L1Cache_getL1CacheEntry(addr))).m_DataBlk;
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_reqSize = ((*in_msg_ptr)).m_Size;
    ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_AccessMask = ((*in_msg_ptr)).m_AccessMask;
  }
}

/** \brief Pop mandatory queue.*/
void L1Cache_Controller::k_popMandatoryQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).dequeue());
}

/** \brief Pop incoming request queue and profile the delay within this virtual network*/
void L1Cache_Controller::l_popRequestQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L1Cache_requestToL1Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_INV)) {
      if (((machineIDToMachineType(((*in_msg_ptr)).m_Requestor)) == MachineType_L2Cache)) {
        (profileBandwidth(("L2_COHMSG_RCL"), ((*in_msg_ptr)).m_MessageSize));
      } else {
        (profileBandwidth(("L2_COHMSG_INV"), ((*in_msg_ptr)).m_MessageSize));
      }
    } else {
      if (((((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETX) || (((*in_msg_ptr)).m_Type == CoherenceRequestType_UPGRADE)) || (((*in_msg_ptr)).m_Type == CoherenceRequestType_GETS)) || (((*in_msg_ptr)).m_Type == CoherenceRequestType_GET_INSTR))) {
        (profileBandwidth(("L2_COHMSG_FWD"), ((*in_msg_ptr)).m_MessageSize));
      } else {
                cerr << "Runtime Error at ../protocols/FUSION/MESI_CMP_directory-L1cache.sm:641, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Profiling: Invalid forwarded request type") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
      }
    }
  }
  (profileMsgDelay((2), (((*(m_chip_ptr->m_L1Cache_requestToL1Cache_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief Pop Incoming Response queue and profile the delay within this virtual network*/
void L1Cache_Controller::o_popIncomingResponseQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
        if (ASSERT_FLAG && !(((((*in_msg_ptr)).m_Destination).isElement(m_machineID)))) {
      cerr << "Runtime Error at ../protocols/FUSION/MESI_CMP_directory-L1cache.sm:650, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

    }
;
    if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_DATA_EXCLUSIVE)) {
            if (ASSERT_FLAG && !(((machineIDToMachineType(((*in_msg_ptr)).m_Sender)) == MachineType_L2Cache))) {
        cerr << "Runtime Error at ../protocols/FUSION/MESI_CMP_directory-L1cache.sm:652, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

      }
;
      (profileBandwidth(("L2_DATA_S"), ((*in_msg_ptr)).m_MessageSize));
    } else {
      if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_DATA)) {
        if (((machineIDToMachineType(((*in_msg_ptr)).m_Sender)) == MachineType_L1Cache)) {
          if (((L1Cache_getState(((*in_msg_ptr)).m_Address)) == L1Cache_State_IM)) {
            (profileBandwidth(("L1_DATA_GX"), ((*in_msg_ptr)).m_MessageSize));
          } else {
            (profileBandwidth(("L1_DATA_F"), ((*in_msg_ptr)).m_MessageSize));
          }
        } else {
          if (((L1Cache_getState(((*in_msg_ptr)).m_Address)) == L1Cache_State_IM)) {
            (profileBandwidth(("L2_DATA_GX"), ((*in_msg_ptr)).m_MessageSize));
          } else {
            (profileBandwidth(("L2_DATA_S"), ((*in_msg_ptr)).m_MessageSize));
          }
        }
      } else {
        if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_ACK)) {
          if (((machineIDToMachineType(((*in_msg_ptr)).m_Sender)) == MachineType_L1Cache)) {
            (profileBandwidth(("L1_COHMSG_INVACK"), ((*in_msg_ptr)).m_MessageSize));
          } else {
            (profileBandwidth(("L2_COHMSG"), ((*in_msg_ptr)).m_MessageSize));
          }
        } else {
          if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_WB_ACK)) {
            (profileBandwidth(("L2_COHMSG"), ((*in_msg_ptr)).m_MessageSize));
          } else {
                        cerr << "Runtime Error at ../protocols/FUSION/MESI_CMP_directory-L1cache.sm:684, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Profiler: Invalid L1 response type") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
          }
        }
      }
    }
  }
  (profileMsgDelay((3), (((*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief Deallocate TBE*/
void L1Cache_Controller::s_deallocateTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).deallocate(addr));
}

/** \brief Write data to cache*/
void L1Cache_Controller::u_writeDataToL1Cache(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((L1Cache_getL1CacheEntry(addr))).m_DataBlk = ((*in_msg_ptr)).m_DataBlk;
    ((L1Cache_getL1CacheEntry(addr))).m_Dirty = ((*in_msg_ptr)).m_Dirty;
  }
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if (((L1Cache_getState(((*in_msg_ptr)).m_Address)) == L1Cache_State_IM)) {
      (profileBandwidthBytes(("DATA_GX_OW"), ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_reqSize, (false)));
      (profileBandwidthBytes(("DATA_GX_C"), ((get_DATA_BLOCK_BYTES()) - ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_reqSize), (true)));
    }
  }
}

/** \brief Update ack count*/
void L1Cache_Controller::q_updateAckCount(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_pendingAcks = (((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_pendingAcks - ((*in_msg_ptr)).m_AckCount);
    APPEND_TRANSITION_COMMENT(((*in_msg_ptr)).m_AckCount);
;
    APPEND_TRANSITION_COMMENT((" p: "));
;
    APPEND_TRANSITION_COMMENT(((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_pendingAcks);
;
  }
}

/** \brief Stall*/
void L1Cache_Controller::z_stall(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
}

/** \brief Deallocate L1 cache block.  Sets the cache to not present, allowing a replacement in parallel with a fetch.*/
void L1Cache_Controller::ff_deallocateL1CacheBlock(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if ((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).isTagPresent(addr))) {
    (((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).deallocate(addr));
  } else {
    (((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).deallocate(addr));
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

/** \brief Set L1 I-cache tag equal to tag of block B.*/
void L1Cache_Controller::pp_allocateL1ICacheBlock(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if (((((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).isTagPresent(addr)) == (false))) {
    (((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).allocate(addr));
  }
}

/** \brief recycle L1 request queue*/
void L1Cache_Controller::zz_recycleRequestQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L1Cache_requestToL1Cache_vec[m_version]))).recycle());
}

/** \brief recycle L1 request queue*/
void L1Cache_Controller::z_recycleMandatoryQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).recycle());
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
      cerr << "Runtime Error at ../protocols/FUSION/MESI_CMP_directory-L1cache.sm:756, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
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
      cerr << "Runtime Error at ../protocols/FUSION/MESI_CMP_directory-L1cache.sm:763, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

    }
;
    (profile_L1Cache_request_g((*in_msg_ptr), m_chip_ptr->getID(), (false)));
  }
}

