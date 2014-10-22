// Auto generated C++ code started by symbols/StateMachine.C:475
// L2Cache: Cache Leasing v2 L2 Cache CMP

#include "Global.h"
#include "L2Cache_Controller.h"
#include "L2Cache_State.h"
#include "L2Cache_Event.h"
#include "Types.h"
#include "System.h"
#include "Chip.h"

#define HASH_FUN(state, event)  ((int(state)*L2Cache_Event_NUM)+int(event))

#define GET_TRANSITION_COMMENT() (L2Cache_transitionComment.str())
#define CLEAR_TRANSITION_COMMENT() (L2Cache_transitionComment.str(""))

TransitionResult L2Cache_Controller::doTransition(L2Cache_Event event, L2Cache_State state, const Address& addr
)
{
  L2Cache_State next_state = state;

  DEBUG_NEWLINE(GENERATED_COMP, MedPrio);
  DEBUG_MSG(GENERATED_COMP, MedPrio,*this);
  DEBUG_EXPR(GENERATED_COMP, MedPrio,g_eventQueue_ptr->getTime());
  DEBUG_EXPR(GENERATED_COMP, MedPrio,state);
  DEBUG_EXPR(GENERATED_COMP, MedPrio,event);
  DEBUG_EXPR(GENERATED_COMP, MedPrio,addr);

  TransitionResult result = doTransitionWorker(event, state, next_state, addr);

  if (result == TransitionResult_Valid) {
    DEBUG_EXPR(GENERATED_COMP, MedPrio, next_state);
    DEBUG_NEWLINE(GENERATED_COMP, MedPrio);
    s_profiler.countTransition(state, event);
    if (PROTOCOL_DEBUG_TRACE) {
      g_system_ptr->getProfiler()->profileTransition("L2Cache", m_chip_ptr->getID(), m_version, addr, 
        L2Cache_State_to_string(state), 
        L2Cache_Event_to_string(event), 
        L2Cache_State_to_string(next_state), GET_TRANSITION_COMMENT());
    }
    CLEAR_TRANSITION_COMMENT();
    L2Cache_setState(addr, next_state);
    
  } else if (result == TransitionResult_ResourceStall) {
    if (PROTOCOL_DEBUG_TRACE) {
      g_system_ptr->getProfiler()->profileTransition("L2Cache", m_chip_ptr->getID(), m_version, addr, 
        L2Cache_State_to_string(state), 
        L2Cache_Event_to_string(event), 
        L2Cache_State_to_string(next_state), 
        "Resource Stall");
    }
  } else if (result == TransitionResult_ProtocolStall) {
    DEBUG_MSG(GENERATED_COMP,HighPrio,"stalling");
    DEBUG_NEWLINE(GENERATED_COMP, MedPrio);
    if (PROTOCOL_DEBUG_TRACE) {
      g_system_ptr->getProfiler()->profileTransition("L2Cache", m_chip_ptr->getID(), m_version, addr, 
        L2Cache_State_to_string(state), 
        L2Cache_Event_to_string(event), 
        L2Cache_State_to_string(next_state), 
        "Protocol Stall");
    }
  }
  return result;
}

TransitionResult L2Cache_Controller::doTransitionWorker(L2Cache_Event event, L2Cache_State state, L2Cache_State& next_state, const Address& addr
)
{

  switch(HASH_FUN(state, event)) {
  case HASH_FUN(L2Cache_State_NP, L2Cache_Event_L1_GETS):
  {
    next_state = L2Cache_State_IS;
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_requestFromL2TCache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pM_profileRequestMiss(addr);
    qq_allocateL2CacheBlock(addr);
    i_allocateTBE(addr);
    ss_recordGetSL1ID(addr);
    a_issueFetchToMemory(addr);
    jj_popL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_NP, L2Cache_Event_L1_Write):
  case HASH_FUN(L2Cache_State_NP, L2Cache_Event_L1_Upgrade_NT):
  {
    next_state = L2Cache_State_IM;
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_requestFromL2TCache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pM_profileResponseMiss(addr);
    qq_allocateL2CacheBlock(addr);
    d_markBlockDirty(addr);
    il_allocateTBE(addr);
    xx_recordGetXL1ID(addr);
    a_issueFetchToMemoryForStore(addr);
    jj_popL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_NP, L2Cache_Event_L2_Atomic):
  {
    next_state = L2Cache_State_IMA;
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_requestFromL2TCache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pM_profileResponseMiss(addr);
    qq_allocateL2CacheBlock(addr);
    d_markBlockDirty(addr);
    il_allocateTBE(addr);
    xx_recordGetXL1ID(addr);
    a_issueFetchToMemoryForStore(addr);
    jj_popL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_IS, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_IS, L2Cache_Event_L2_Replacement_clean):
  case HASH_FUN(L2Cache_State_IM, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_IM, L2Cache_Event_L2_Replacement_clean):
  case HASH_FUN(L2Cache_State_IMA, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_IMA, L2Cache_Event_L2_Replacement_clean):
  case HASH_FUN(L2Cache_State_IM, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_IMA, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_MI, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_MI_Ack, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_S, L2Cache_Event_L1_Write):
  case HASH_FUN(L2Cache_State_SS, L2Cache_Event_L1_Write):
  case HASH_FUN(L2Cache_State_S, L2Cache_Event_L1_Upgrade_NT):
  case HASH_FUN(L2Cache_State_SS, L2Cache_Event_L1_Upgrade_NT):
  case HASH_FUN(L2Cache_State_S, L2Cache_Event_L2_Atomic):
  case HASH_FUN(L2Cache_State_SS, L2Cache_Event_L2_Atomic):
  case HASH_FUN(L2Cache_State_SS, L2Cache_Event_L1_Upgrade_T):
  {
    return TransitionResult_ProtocolStall;
  }
  case HASH_FUN(L2Cache_State_IS, L2Cache_Event_L1_GETS):
  {
    next_state = L2Cache_State_ISS;
    pH_profileRequestHit(addr);
    ss_recordGetSL1ID(addr);
    jj_popL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_S, L2Cache_Event_L1_GETS):
  {
    next_state = L2Cache_State_SS;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pH_profileRequestHit(addr);
    t_updateL2BlockTime(addr);
    ds_sendDataToRequestor(addr);
    set_setMRU(addr);
    jj_popL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_E, L2Cache_Event_L1_Write):
  case HASH_FUN(L2Cache_State_E, L2Cache_Event_L1_Upgrade_NT):
  {
    next_state = L2Cache_State_S;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pH_profileResponseHit(addr);
    d_markBlockDirty(addr);
    ti_incrementL2BlockTime(addr);
    wa_sendAckToRequestor(addr);
    mr_writeDataToCacheFromRequest(addr);
    set_setMRU(addr);
    jj_popL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_S, L2Cache_Event_L1_Upgrade_T):
  {
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pH_profileResponseHit(addr);
    d_markBlockDirty(addr);
    ti_incrementL2BlockTime(addr);
    wa_sendAckToRequestor(addr);
    mr_writeDataToCacheFromRequest(addr);
    set_setMRU(addr);
    jj_popL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_S, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_S, L2Cache_Event_L2_Replacement_clean):
  case HASH_FUN(L2Cache_State_SS, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_SS, L2Cache_Event_L2_Replacement_clean):
  {
    next_state = L2Cache_State_MI;
    if (!(*(m_chip_ptr->m_L2Cache_L2ExpireTriggerQueue_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    ir_allocateTBE(addr);
    it_insertL2ExpireTriggerQueue(addr);
    rr_deallocateL2CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_SS, L2Cache_Event_L1_GETS):
  {
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pH_profileRequestHit(addr);
    t_updateL2BlockTime(addr);
    ds_sendDataToRequestor(addr);
    set_setMRU(addr);
    jj_popL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_E, L2Cache_Event_L1_GETS):
  {
    next_state = L2Cache_State_S;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pH_profileRequestHit(addr);
    t_updateL2BlockTime(addr);
    ds_sendDataToRequestor(addr);
    set_setMRU(addr);
    jj_popL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_E, L2Cache_Event_L2_Atomic):
  {
    next_state = L2Cache_State_S;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pH_profileResponseHit(addr);
    d_markBlockDirty(addr);
    ti_incrementL2BlockTime(addr);
    ds_sendAtomicDataGlobalToRequestor(addr);
    mr_writeDataToCacheFromRequest(addr);
    set_setMRU(addr);
    jj_popL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_E, L2Cache_Event_L2_Replacement_clean):
  case HASH_FUN(L2Cache_State_E, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_E, L2Cache_Event_Inv):
  {
    next_state = L2Cache_State_MI_Ack;
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_requestFromL2TCache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2TCache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    ir_allocateTBE(addr);
    c_exclusiveReplacement(addr);
    rr_deallocateL2CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_MI, L2Cache_Event_L2_Expire):
  {
    next_state = L2Cache_State_MI_Ack;
    if (!(*(m_chip_ptr->m_L2Cache_requestFromL2TCache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2TCache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    c_exclusiveReplacement(addr);
    o_popL2ExpireTriggerQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_MI_Ack, L2Cache_Event_WB_Ack):
  {
    next_state = L2Cache_State_NP;
    o_popIncomingCPUResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_IS, L2Cache_Event_L1_Write):
  case HASH_FUN(L2Cache_State_IS, L2Cache_Event_L1_Upgrade_NT):
  case HASH_FUN(L2Cache_State_IS, L2Cache_Event_L2_Atomic):
  case HASH_FUN(L2Cache_State_IM, L2Cache_Event_L1_Write):
  case HASH_FUN(L2Cache_State_IM, L2Cache_Event_L1_Upgrade_NT):
  case HASH_FUN(L2Cache_State_IM, L2Cache_Event_L2_Atomic):
  case HASH_FUN(L2Cache_State_IMA, L2Cache_Event_L1_Write):
  case HASH_FUN(L2Cache_State_IMA, L2Cache_Event_L1_Upgrade_NT):
  case HASH_FUN(L2Cache_State_IMA, L2Cache_Event_L2_Atomic):
  case HASH_FUN(L2Cache_State_MI, L2Cache_Event_L1_Write):
  case HASH_FUN(L2Cache_State_MI, L2Cache_Event_L1_Upgrade_NT):
  case HASH_FUN(L2Cache_State_MI, L2Cache_Event_L2_Atomic):
  case HASH_FUN(L2Cache_State_MI_Ack, L2Cache_Event_L1_Write):
  case HASH_FUN(L2Cache_State_MI_Ack, L2Cache_Event_L1_Upgrade_NT):
  case HASH_FUN(L2Cache_State_MI_Ack, L2Cache_Event_L2_Atomic):
  {
    zz_recycleL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_IM, L2Cache_Event_Data):
  case HASH_FUN(L2Cache_State_IMA, L2Cache_Event_Data):
  case HASH_FUN(L2Cache_State_IS, L2Cache_Event_Data):
  case HASH_FUN(L2Cache_State_ISS, L2Cache_Event_Data):
  {
    m_writeDataToCache(addr);
    d_markTBEDataReady(addr);
    o_popIncomingCPUResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_IM, L2Cache_Event_Data_all_Acks):
  {
    next_state = L2Cache_State_E;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    m_writeDataToCache(addr);
    tn_expireL2BlockTime(addr);
    mt_writeDataToCacheFromTBE(addr);
    wat_sendAckToRequestorFromTBE(addr);
    s_deallocateTBE(addr);
    o_popIncomingCPUResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_IMA, L2Cache_Event_Data_all_Acks):
  {
    next_state = L2Cache_State_E;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    m_writeDataToCache(addr);
    tn_expireL2BlockTime(addr);
    mt_writeDataToCacheFromTBE(addr);
    dst_sendAtomicDataToGetSRequestors(addr);
    s_deallocateTBE(addr);
    o_popIncomingCPUResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_IS, L2Cache_Event_Data_all_Acks):
  {
    next_state = L2Cache_State_S;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    m_writeDataToCache(addr);
    tt_updateL2BlockTime_fromTBE(addr);
    dst_sendDataToGetSRequestors(addr);
    s_deallocateTBE(addr);
    o_popIncomingCPUResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_ISS, L2Cache_Event_Data_all_Acks):
  {
    next_state = L2Cache_State_SS;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    m_writeDataToCache(addr);
    tt_updateL2BlockTime_fromTBE(addr);
    dst_sendDataToGetSRequestors(addr);
    s_deallocateTBE(addr);
    o_popIncomingCPUResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_IMA, L2Cache_Event_Ack):
  case HASH_FUN(L2Cache_State_IM, L2Cache_Event_Ack):
  case HASH_FUN(L2Cache_State_IS, L2Cache_Event_Ack):
  case HASH_FUN(L2Cache_State_ISS, L2Cache_Event_Ack):
  {
    q_updateAckCount(addr);
    o_popIncomingCPUResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_IMA, L2Cache_Event_Ack_all):
  {
    next_state = L2Cache_State_E;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    tn_expireL2BlockTime(addr);
    mt_writeDataToCacheFromTBE(addr);
    dst_sendAtomicDataToGetSRequestors(addr);
    s_deallocateTBE(addr);
    o_popIncomingCPUResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_IM, L2Cache_Event_Ack_all):
  {
    next_state = L2Cache_State_E;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    tn_expireL2BlockTime(addr);
    mt_writeDataToCacheFromTBE(addr);
    wat_sendAckToRequestorFromTBE(addr);
    s_deallocateTBE(addr);
    o_popIncomingCPUResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_IS, L2Cache_Event_Ack_all):
  {
    next_state = L2Cache_State_S;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    tt_updateL2BlockTime_fromTBE(addr);
    dst_sendDataToGetSRequestors(addr);
    s_deallocateTBE(addr);
    o_popIncomingCPUResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_ISS, L2Cache_Event_Ack_all):
  {
    next_state = L2Cache_State_SS;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    tt_updateL2BlockTime_fromTBE(addr);
    dst_sendDataToGetSRequestors(addr);
    s_deallocateTBE(addr);
    o_popIncomingCPUResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_SS, L2Cache_Event_Fwd_GETX):
  case HASH_FUN(L2Cache_State_SS, L2Cache_Event_Fwd_GETS):
  case HASH_FUN(L2Cache_State_SS, L2Cache_Event_Inv):
  case HASH_FUN(L2Cache_State_S, L2Cache_Event_Fwd_GETX):
  case HASH_FUN(L2Cache_State_S, L2Cache_Event_Fwd_GETS):
  case HASH_FUN(L2Cache_State_S, L2Cache_Event_Inv):
  {
    next_state = L2Cache_State_MI;
    if (!(*(m_chip_ptr->m_L2Cache_L2ExpireTriggerQueue_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    ir_allocateTBE(addr);
    it_insertL2ExpireTriggerQueue(addr);
    rr_deallocateL2CacheBlock(addr);
    o_popIncomingCPURequestQueue(addr);
    return TransitionResult_Valid;
  }
  default:
    WARN_EXPR(m_id);
    WARN_EXPR(m_version);
    WARN_EXPR(g_eventQueue_ptr->getTime());
    WARN_EXPR(addr);
    WARN_EXPR(event);
    WARN_EXPR(state);
    ERROR_MSG("Invalid transition");
  }
  return TransitionResult_Valid;
}
