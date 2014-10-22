/** \file L2Cache.C
  * 
  * Auto generated C++ code started by symbols/StateMachine.C:327
  * Created by slicc definition of Module "MESI Directory L2 Cache CMP"
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
  (*(m_chip_ptr->m_L2Cache_unblockToL2Cache_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version])).setConsumer(this);


  s_profiler.possibleTransition(L2Cache_State_NP, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_IS, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_ISS, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_IM, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_SS, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_M, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_I_I, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_S_I, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_M_MB, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_MT_IB, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_MT_SB, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_NP, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_SS, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_M, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_MT, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_I_I, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_S_I, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_IS, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_ISS, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_IM, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_M_MB, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_MT_IB, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_MT_SB, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_IM, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_IM, L2Cache_Event_L2_Replacement_clean);
  s_profiler.possibleTransition(L2Cache_State_IS, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_IS, L2Cache_Event_L2_Replacement_clean);
  s_profiler.possibleTransition(L2Cache_State_ISS, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_ISS, L2Cache_Event_L2_Replacement_clean);
  s_profiler.possibleTransition(L2Cache_State_SS_MB, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_SS_MB, L2Cache_Event_L2_Replacement_clean);
  s_profiler.possibleTransition(L2Cache_State_M_MB, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_M_MB, L2Cache_Event_L2_Replacement_clean);
  s_profiler.possibleTransition(L2Cache_State_MT_MB, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_MT_MB, L2Cache_Event_L2_Replacement_clean);
  s_profiler.possibleTransition(L2Cache_State_MT_IIB, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_MT_IIB, L2Cache_Event_L2_Replacement_clean);
  s_profiler.possibleTransition(L2Cache_State_MT_IB, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_MT_IB, L2Cache_Event_L2_Replacement_clean);
  s_profiler.possibleTransition(L2Cache_State_MT_SB, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_MT_SB, L2Cache_Event_L2_Replacement_clean);
  s_profiler.possibleTransition(L2Cache_State_SS_MB, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_SS_MB, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_SS_MB, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_SS_MB, L2Cache_Event_L1_UPGRADE);
  s_profiler.possibleTransition(L2Cache_State_M_MB, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_M_MB, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_M_MB, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_M_MB, L2Cache_Event_L1_UPGRADE);
  s_profiler.possibleTransition(L2Cache_State_MT_MB, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_MT_MB, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_MT_MB, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_MT_MB, L2Cache_Event_L1_UPGRADE);
  s_profiler.possibleTransition(L2Cache_State_MT_IIB, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_MT_IIB, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_MT_IIB, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_MT_IIB, L2Cache_Event_L1_UPGRADE);
  s_profiler.possibleTransition(L2Cache_State_MT_IB, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_MT_IB, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_MT_IB, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_MT_IB, L2Cache_Event_L1_UPGRADE);
  s_profiler.possibleTransition(L2Cache_State_MT_SB, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_MT_SB, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_MT_SB, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_MT_SB, L2Cache_Event_L1_UPGRADE);
  s_profiler.possibleTransition(L2Cache_State_NP, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_NP, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_NP, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_ISS, L2Cache_Event_Mem_Data);
  s_profiler.possibleTransition(L2Cache_State_IS, L2Cache_Event_Mem_Data);
  s_profiler.possibleTransition(L2Cache_State_IM, L2Cache_Event_Mem_Data);
  s_profiler.possibleTransition(L2Cache_State_IS, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_IS, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_ISS, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_ISS, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_IS, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_ISS, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_IM, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_IM, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_IM, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_SS, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_SS, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_SS, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_SS, L2Cache_Event_L1_UPGRADE);
  s_profiler.possibleTransition(L2Cache_State_SS, L2Cache_Event_L2_Replacement_clean);
  s_profiler.possibleTransition(L2Cache_State_SS, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_M, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_M, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_M, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_M, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_M, L2Cache_Event_L2_Replacement_clean);
  s_profiler.possibleTransition(L2Cache_State_MT, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_MT, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_MT, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_MT, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_MT, L2Cache_Event_L2_Replacement_clean);
  s_profiler.possibleTransition(L2Cache_State_MT, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_SS_MB, L2Cache_Event_Unblock_Cancel);
  s_profiler.possibleTransition(L2Cache_State_MT_MB, L2Cache_Event_Unblock_Cancel);
  s_profiler.possibleTransition(L2Cache_State_MT_IB, L2Cache_Event_Unblock_Cancel);
  s_profiler.possibleTransition(L2Cache_State_SS_MB, L2Cache_Event_Exclusive_Unblock);
  s_profiler.possibleTransition(L2Cache_State_M_MB, L2Cache_Event_Exclusive_Unblock);
  s_profiler.possibleTransition(L2Cache_State_MT_MB, L2Cache_Event_Exclusive_Unblock);
  s_profiler.possibleTransition(L2Cache_State_MT_IIB, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_MT_IIB, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_MT_IIB, L2Cache_Event_Unblock);
  s_profiler.possibleTransition(L2Cache_State_MT_IIB, L2Cache_Event_WB_Data);
  s_profiler.possibleTransition(L2Cache_State_MT_IIB, L2Cache_Event_WB_Data_clean);
  s_profiler.possibleTransition(L2Cache_State_MT_IB, L2Cache_Event_WB_Data);
  s_profiler.possibleTransition(L2Cache_State_MT_IB, L2Cache_Event_WB_Data_clean);
  s_profiler.possibleTransition(L2Cache_State_MT_SB, L2Cache_Event_Unblock);
  s_profiler.possibleTransition(L2Cache_State_I_I, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_I_I, L2Cache_Event_L1_UPGRADE);
  s_profiler.possibleTransition(L2Cache_State_I_I, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_I_I, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_S_I, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_S_I, L2Cache_Event_L1_UPGRADE);
  s_profiler.possibleTransition(L2Cache_State_S_I, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_S_I, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_MT_I, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_MT_I, L2Cache_Event_L1_UPGRADE);
  s_profiler.possibleTransition(L2Cache_State_MT_I, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_MT_I, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_MCT_I, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_MCT_I, L2Cache_Event_L1_UPGRADE);
  s_profiler.possibleTransition(L2Cache_State_MCT_I, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_MCT_I, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_M_I, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_M_I, L2Cache_Event_L1_UPGRADE);
  s_profiler.possibleTransition(L2Cache_State_M_I, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_M_I, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_I_I, L2Cache_Event_Ack);
  s_profiler.possibleTransition(L2Cache_State_I_I, L2Cache_Event_Ack_all);
  s_profiler.possibleTransition(L2Cache_State_MT_I, L2Cache_Event_WB_Data);
  s_profiler.possibleTransition(L2Cache_State_MCT_I, L2Cache_Event_WB_Data);
  s_profiler.possibleTransition(L2Cache_State_MCT_I, L2Cache_Event_WB_Data_clean);
  s_profiler.possibleTransition(L2Cache_State_MCT_I, L2Cache_Event_Ack_all);
  s_profiler.possibleTransition(L2Cache_State_MCT_I, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_MCT_I, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_MT_I, L2Cache_Event_Ack_all);
  s_profiler.possibleTransition(L2Cache_State_MT_I, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_MT_I, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_MT_MB, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_MT_MB, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_SS_MB, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_SS_MB, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_MT_I, L2Cache_Event_WB_Data_clean);
  s_profiler.possibleTransition(L2Cache_State_S_I, L2Cache_Event_Ack);
  s_profiler.possibleTransition(L2Cache_State_S_I, L2Cache_Event_Ack_all);
  s_profiler.possibleTransition(L2Cache_State_M_I, L2Cache_Event_Mem_Ack);
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
      (out_msg).m_Type = CoherenceRequestType_GETS;
      (out_msg).m_Requestor = m_machineID;
      (((out_msg).m_Destination).add((map_Address_to_Directory(addr))));
      (out_msg).m_MessageSize = MessageSizeType_Control;
      ((*(m_chip_ptr->m_L2Cache_DirRequestFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_REQUEST_LATENCY);
    }
  }
}

/** \brief Forward request to the exclusive L1*/
void L2Cache_Controller::b_forwardRequestToExclusive(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = ((*in_msg_ptr)).m_Type;
      (out_msg).m_Requestor = ((*in_msg_ptr)).m_Requestor;
      (((out_msg).m_Destination).add(((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Exclusive));
      (out_msg).m_MessageSize = MessageSizeType_Request_Control;
      ((*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_REQUEST_LATENCY);
    }
  }
}

/** \brief Send data to memory*/
void L2Cache_Controller::c_exclusiveReplacement(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    ResponseMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceResponseType_MEMORY_DATA;
    (out_msg).m_Sender = m_machineID;
    (((out_msg).m_Destination).add((map_Address_to_Directory(addr))));
    (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
    (out_msg).m_Dirty = ((L2Cache_getL2CacheEntry(addr))).m_Dirty;
    (out_msg).m_MessageSize = MessageSizeType_Response_Data;
    ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
  }
}

/** \brief Send ack to memory for clean replacement*/
void L2Cache_Controller::c_exclusiveCleanReplacement(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    ResponseMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceResponseType_ACK;
    (out_msg).m_Sender = m_machineID;
    (((out_msg).m_Destination).add((map_Address_to_Directory(addr))));
    (out_msg).m_MessageSize = MessageSizeType_Control;
    ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
  }
}

/** \brief Send data to memory*/
void L2Cache_Controller::ct_exclusiveReplacementFromTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    ResponseMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceResponseType_MEMORY_DATA;
    (out_msg).m_Sender = m_machineID;
    (((out_msg).m_Destination).add((map_Address_to_Directory(addr))));
    (out_msg).m_DataBlk = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_DataBlk;
    (out_msg).m_Dirty = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Dirty;
    (out_msg).m_MessageSize = MessageSizeType_Response_Data;
    ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
  }
}

/** \brief Send data from cache to reqeustor*/
void L2Cache_Controller::d_sendDataToRequestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_Sender = m_machineID;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_Requestor));
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_Dirty = ((L2Cache_getL2CacheEntry(addr))).m_Dirty;
      (out_msg).m_MessageSize = MessageSizeType_Response_Data;
      (out_msg).m_AckCount = ((0) - ((((L2Cache_getL2CacheEntry(addr))).m_Sharers).count()));
      if (((((L2Cache_getL2CacheEntry(addr))).m_Sharers).isElement(((*in_msg_ptr)).m_Requestor))) {
        (out_msg).m_AckCount = ((out_msg).m_AckCount + (1));
      }
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_to_L1_DATA_LATENCY);
    }
  }
}

/** \brief Send exclusive data from cache to reqeustor*/
void L2Cache_Controller::dd_sendExclusiveDataToRequestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA_EXCLUSIVE;
      (out_msg).m_Sender = m_machineID;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_Requestor));
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_Dirty = ((L2Cache_getL2CacheEntry(addr))).m_Dirty;
      (out_msg).m_MessageSize = MessageSizeType_Response_Data;
      (out_msg).m_AckCount = ((0) - ((((L2Cache_getL2CacheEntry(addr))).m_Sharers).count()));
      if (((((L2Cache_getL2CacheEntry(addr))).m_Sharers).isElement(((*in_msg_ptr)).m_Requestor))) {
        (out_msg).m_AckCount = ((out_msg).m_AckCount + (1));
      }
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_to_L1_DATA_LATENCY);
    }
  }
}

/** \brief Send shared data from cache to reqeustor*/
void L2Cache_Controller::ds_sendSharedDataToRequestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_Sender = m_machineID;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_Requestor));
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_Dirty = ((L2Cache_getL2CacheEntry(addr))).m_Dirty;
      (out_msg).m_MessageSize = MessageSizeType_Response_Data;
      (out_msg).m_AckCount = (0);
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_to_L1_DATA_LATENCY);
    }
  }
}

/** \brief Send data from cache to all GetS IDs*/
void L2Cache_Controller::e_sendDataToGetSRequestors(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
    if (ASSERT_FLAG && !((((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs).count()) > (0)))) {
    cerr << "Runtime Error at ../protocols/FUSION/MESI_CMP_directory-L2cache.sm:501, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
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
    (out_msg).m_MessageSize = MessageSizeType_Response_Data;
    ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_to_L1_DATA_LATENCY);
  }
}

/** \brief Send exclusive data from cache to all GetS IDs*/
void L2Cache_Controller::ex_sendExclusiveDataToGetSRequestors(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
    if (ASSERT_FLAG && !((((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs).count()) == (1)))) {
    cerr << "Runtime Error at ../protocols/FUSION/MESI_CMP_directory-L2cache.sm:514, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

  }
;
  {
    ResponseMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceResponseType_DATA_EXCLUSIVE;
    (out_msg).m_Sender = m_machineID;
    (out_msg).m_Destination = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs;
    (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
    (out_msg).m_Dirty = ((L2Cache_getL2CacheEntry(addr))).m_Dirty;
    (out_msg).m_MessageSize = MessageSizeType_Response_Data;
    ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_to_L1_DATA_LATENCY);
  }
}

/** \brief Send data from cache to GetX ID*/
void L2Cache_Controller::ee_sendDataToGetXRequestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    ResponseMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceResponseType_DATA;
    (out_msg).m_Sender = m_machineID;
    (((out_msg).m_Destination).add(((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetX_ID));
    DEBUG_SLICC(MedPrio, "../protocols/FUSION/MESI_CMP_directory-L2cache.sm:533: ", (out_msg).m_Destination);
;
    (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
    (out_msg).m_Dirty = ((L2Cache_getL2CacheEntry(addr))).m_Dirty;
    DEBUG_SLICC(MedPrio, "../protocols/FUSION/MESI_CMP_directory-L2cache.sm:536: ", (out_msg).m_Address);
;
    DEBUG_SLICC(MedPrio, "../protocols/FUSION/MESI_CMP_directory-L2cache.sm:537: ", (out_msg).m_Destination);
;
    DEBUG_SLICC(MedPrio, "../protocols/FUSION/MESI_CMP_directory-L2cache.sm:538: ", (out_msg).m_DataBlk);
;
    (out_msg).m_MessageSize = MessageSizeType_Response_Data;
    ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_to_L1_DATA_LATENCY);
  }
}

/** \brief invalidate sharers for L2 replacement*/
void L2Cache_Controller::f_sendInvToSharers(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    RequestMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceRequestType_INV;
    (out_msg).m_Requestor = m_machineID;
    (out_msg).m_Destination = ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers;
    (out_msg).m_MessageSize = MessageSizeType_Request_Control;
    ((*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_to_L1_MSG_LATENCY);
  }
}

/** \brief invalidate sharers for request, requestor is sharer*/
void L2Cache_Controller::fwm_sendFwdInvToSharersMinusRequestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_INV;
      (out_msg).m_Requestor = ((*in_msg_ptr)).m_Requestor;
      (out_msg).m_Destination = ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers;
      (((out_msg).m_Destination).remove(((*in_msg_ptr)).m_Requestor));
      (out_msg).m_MessageSize = MessageSizeType_Request_Control;
      ((*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_to_L1_MSG_LATENCY);
    }
  }
}

/** \brief Allocate TBE for internal/external request(isPrefetch=0, number of invalidates=0)*/
void L2Cache_Controller::i_allocateTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).allocate(addr));
  ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs).clear());
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Dirty = ((L2Cache_getL2CacheEntry(addr))).m_Dirty;
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_pendingAcks = ((((L2Cache_getL2CacheEntry(addr))).m_Sharers).count());
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
        if (ASSERT_FLAG && !(((machineIDToMachineType(((*in_msg_ptr)).m_Requestor)) == MachineType_L1Cache))) {
      cerr << "Runtime Error at ../protocols/FUSION/MESI_CMP_directory-L2cache.sm:599, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

    }
;
    if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_PUTX)) {
      if (((*in_msg_ptr)).m_Dirty) {
        (profileBandwidth(("L1_DATA_PX"), ((*in_msg_ptr)).m_MessageSize));
        (profileBandwidthBytes(("DATA_PX_D"), (get_byte_mask_count(((*in_msg_ptr)).m_DirtyMask)), (true)));
        (profileBandwidthBytes(("DATA_PX_C"), ((get_DATA_BLOCK_BYTES()) - (get_byte_mask_count(((*in_msg_ptr)).m_DirtyMask))), (false)));
      } else {
        (profileBandwidth(("L1_DATA_PC"), ((*in_msg_ptr)).m_MessageSize));
      }
    } else {
      (profileBandwidth(("L1_COHMSG"), ((*in_msg_ptr)).m_MessageSize));
    }
  }
  (profileMsgDelay((0), (((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief Pop incoming unblock queue*/
void L2Cache_Controller::k_popUnblockQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_unblockToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
        if (ASSERT_FLAG && !(((machineIDToMachineType(((*in_msg_ptr)).m_Sender)) == MachineType_L1Cache))) {
      cerr << "Runtime Error at ../protocols/FUSION/MESI_CMP_directory-L2cache.sm:620, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

    }
;
    if (((((*in_msg_ptr)).m_Type == CoherenceResponseType_EXCLUSIVE_UNBLOCK) || (((*in_msg_ptr)).m_Type == CoherenceResponseType_UNBLOCK))) {
      (profileBandwidth(("L1_COHMSG"), ((*in_msg_ptr)).m_MessageSize));
    } else {
            cerr << "Runtime Error at ../protocols/FUSION/MESI_CMP_directory-L2cache.sm:625, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("unknown unblock message") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
    }
  }
  (profileMsgDelay((0), (((*(m_chip_ptr->m_L2Cache_unblockToL2Cache_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief Pop Incoming Response queue*/
void L2Cache_Controller::o_popIncomingResponseQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if (((machineIDToMachineType(((*in_msg_ptr)).m_Sender)) == MachineType_L1Cache)) {
      if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_DATA)) {
        if (((*in_msg_ptr)).m_Dirty) {
          (profileBandwidth(("L1_DATA_PX"), ((*in_msg_ptr)).m_MessageSize));
          (profileBandwidthBytes(("DATA_PX_D"), (get_byte_mask_count(((*in_msg_ptr)).m_DirtyMask)), (true)));
          (profileBandwidthBytes(("DATA_PX_C"), ((get_DATA_BLOCK_BYTES()) - (get_byte_mask_count(((*in_msg_ptr)).m_DirtyMask))), (false)));
        } else {
          (profileBandwidth(("L1_DATA_PC"), ((*in_msg_ptr)).m_MessageSize));
        }
      } else {
        if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_ACK)) {
          (profileBandwidth(("L1_COHMSG_RCLACK"), ((*in_msg_ptr)).m_MessageSize));
        } else {
                    cerr << "Runtime Error at ../protocols/FUSION/MESI_CMP_directory-L2cache.sm:650, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("unknown message type") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
        }
      }
    }
  }
  (profileMsgDelay((3), (((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief Write data from response queue to cache*/
void L2Cache_Controller::m_writeDataToCache(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((L2Cache_getL2CacheEntry(addr))).m_DataBlk = ((*in_msg_ptr)).m_DataBlk;
    ((L2Cache_getL2CacheEntry(addr))).m_Dirty = ((*in_msg_ptr)).m_Dirty;
  }
}

/** \brief Write data from response queue to cache*/
void L2Cache_Controller::mr_writeDataToCacheFromRequest(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((L2Cache_getL2CacheEntry(addr))).m_DataBlk = ((*in_msg_ptr)).m_DataBlk;
    ((L2Cache_getL2CacheEntry(addr))).m_Dirty = ((*in_msg_ptr)).m_Dirty;
  }
}

/** \brief update pending ack count*/
void L2Cache_Controller::q_updateAck(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).peek());
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

/** \brief Write data from response queue to TBE*/
void L2Cache_Controller::qq_writeDataToTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_DataBlk = ((*in_msg_ptr)).m_DataBlk;
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Dirty = ((*in_msg_ptr)).m_Dirty;
  }
}

/** \brief Stall*/
void L2Cache_Controller::z_stall(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
}

/** \brief Record L1 GetS for load response*/
void L2Cache_Controller::ss_recordGetSL1ID(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs).add(((*in_msg_ptr)).m_Requestor));
  }
}

/** \brief Record L1 GetX for store response*/
void L2Cache_Controller::xx_recordGetXL1ID(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetX_ID = ((*in_msg_ptr)).m_Requestor;
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

/** \brief Deallocate L2 cache block.  Sets the cache to not present, allowing a replacement in parallel with a fetch.*/
void L2Cache_Controller::rr_deallocateL2CacheBlock(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).deallocate(addr));
}

/** \brief Send writeback ACK*/
void L2Cache_Controller::t_sendWBAck(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_WB_ACK;
      (out_msg).m_Sender = m_machineID;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_Requestor));
      (out_msg).m_MessageSize = MessageSizeType_Response_Control;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_to_L1_MSG_LATENCY);
    }
  }
}

/** \brief Send ACK to upgrader*/
void L2Cache_Controller::ts_sendInvAckToUpgrader(const Address& addr)
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
      (out_msg).m_AckCount = (((0) - ((((L2Cache_getL2CacheEntry(addr))).m_Sharers).count())) + (1));
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_to_L1_MSG_LATENCY);
    }
  }
}

/** \brief Profile the demand miss*/
void L2Cache_Controller::uu_profileMiss(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
  }
}

/** \brief Profile this transition at the L2 because Dir won't see the request*/
void L2Cache_Controller::ww_profileMissNoDir(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
  }
}

/** \brief Add L1 sharer to list*/
void L2Cache_Controller::nn_addSharer(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (L2Cache_addSharer(addr, ((*in_msg_ptr)).m_Requestor));
    APPEND_TRANSITION_COMMENT(((L2Cache_getL2CacheEntry(addr))).m_Sharers);
;
  }
}

/** \brief Add L1 sharer to list*/
void L2Cache_Controller::nnu_addSharerFromUnblock(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_unblockToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (L2Cache_addSharer(addr, ((*in_msg_ptr)).m_Sender));
  }
}

/** \brief Remove L1 Request sharer from list*/
void L2Cache_Controller::kk_removeRequestSharer(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers).remove(((*in_msg_ptr)).m_Requestor));
  }
}

/** \brief Remove all L1 sharers from list*/
void L2Cache_Controller::ll_clearSharers(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers).clear());
  }
}

/** \brief set the exclusive owner*/
void L2Cache_Controller::mm_markExclusive(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers).clear());
    ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Exclusive = ((*in_msg_ptr)).m_Requestor;
    (L2Cache_addSharer(addr, ((*in_msg_ptr)).m_Requestor));
  }
}

/** \brief set the exclusive owner*/
void L2Cache_Controller::mmu_markExclusiveFromUnblock(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_unblockToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers).clear());
    ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Exclusive = ((*in_msg_ptr)).m_Sender;
    (L2Cache_addSharer(addr, ((*in_msg_ptr)).m_Sender));
  }
}

/** \brief recycle L1 request queue*/
void L2Cache_Controller::zz_recycleL1RequestQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).recycle());
}

/** \brief recycle memory request*/
void L2Cache_Controller::zn_recycleResponseNetwork(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).recycle());
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
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (profile_L2Cache_request_g((m_chip_ptr->convertResponseToGenericType(((*in_msg_ptr)).m_Type)), ((*in_msg_ptr)).m_MessageSize, m_chip_ptr->getID(), (true)));
  }
}

/** \brief Profile a demand hit for response message*/
void L2Cache_Controller::pH_profileResponseHit(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (profile_L2Cache_request_g((m_chip_ptr->convertResponseToGenericType(((*in_msg_ptr)).m_Type)), ((*in_msg_ptr)).m_MessageSize, m_chip_ptr->getID(), (false)));
  }
}

