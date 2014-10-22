// Auto generated C++ code started by symbols/StateMachine.C:475
// L1Cache: Cache Leasing v2 L1 Cache CMP

#include "Global.h"
#include "L1Cache_Controller.h"
#include "L1Cache_State.h"
#include "L1Cache_Event.h"
#include "Types.h"
#include "System.h"
#include "Chip.h"

#define HASH_FUN(state, event)  ((int(state)*L1Cache_Event_NUM)+int(event))

#define GET_TRANSITION_COMMENT() (L1Cache_transitionComment.str())
#define CLEAR_TRANSITION_COMMENT() (L1Cache_transitionComment.str(""))

TransitionResult L1Cache_Controller::doTransition(L1Cache_Event event, L1Cache_State state, const Address& addr
)
{
  L1Cache_State next_state = state;

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
      g_system_ptr->getProfiler()->profileTransition("L1Cache", m_chip_ptr->getID(), m_version, addr, 
        L1Cache_State_to_string(state), 
        L1Cache_Event_to_string(event), 
        L1Cache_State_to_string(next_state), GET_TRANSITION_COMMENT());
    }
    CLEAR_TRANSITION_COMMENT();
    L1Cache_setState(addr, next_state);
    
  } else if (result == TransitionResult_ResourceStall) {
    if (PROTOCOL_DEBUG_TRACE) {
      g_system_ptr->getProfiler()->profileTransition("L1Cache", m_chip_ptr->getID(), m_version, addr, 
        L1Cache_State_to_string(state), 
        L1Cache_Event_to_string(event), 
        L1Cache_State_to_string(next_state), 
        "Resource Stall");
    }
  } else if (result == TransitionResult_ProtocolStall) {
    DEBUG_MSG(GENERATED_COMP,HighPrio,"stalling");
    DEBUG_NEWLINE(GENERATED_COMP, MedPrio);
    if (PROTOCOL_DEBUG_TRACE) {
      g_system_ptr->getProfiler()->profileTransition("L1Cache", m_chip_ptr->getID(), m_version, addr, 
        L1Cache_State_to_string(state), 
        L1Cache_Event_to_string(event), 
        L1Cache_State_to_string(next_state), 
        "Protocol Stall");
    }
  }
  return result;
}

TransitionResult L1Cache_Controller::doTransitionWorker(L1Cache_Event event, L1Cache_State state, L1Cache_State& next_state, const Address& addr
)
{

  switch(HASH_FUN(state, event)) {
  case HASH_FUN(L1Cache_State_I, L1Cache_Event_Load):
  {
    next_state = L1Cache_State_I_S;
    if (!(*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pM_profileMiss(addr);
    oo_allocateL1DCacheBlock(addr);
    i_allocateTBE(addr);
    pr_incPendingRead(addr);
    a_issueGETS(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_I, L1Cache_Event_L1_WThru):
  {
    next_state = L1Cache_State_I_I;
    if (!(*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pM_profileMiss(addr);
    i_allocateTBE(addr);
    pw_incPendingWrite(addr);
    d2t_sendDataToL2_fromTBE(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_I, L1Cache_Event_L1_Atomic):
  {
    next_state = L1Cache_State_I_I;
    if (!(*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pM_profileMiss(addr);
    i_allocateTBE(addr);
    pw_incPendingWrite(addr);
    d2t_sendAtomicDataToL2_fromTBE(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_I, L1Cache_Event_L1_Replacement):
  {
    ff_deallocateL1CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_S, L1Cache_Event_Load):
  {
    pH_profileHit(addr);
    h_load_hit(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_S, L1Cache_Event_L1_WThru):
  {
    next_state = L1Cache_State_SM;
    if (!(*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pH_profileHit(addr);
    i_allocateTBEwTime(addr);
    pw_incPendingWrite(addr);
    u_sendUpgradeToL2(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_S, L1Cache_Event_L1_Atomic):
  {
    next_state = L1Cache_State_I_I;
    if (!(*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pH_profileHit(addr);
    i_allocateTBEwTime(addr);
    pw_incPendingWrite(addr);
    d2t_sendAtomicDataToL2_fromTBE(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_S, L1Cache_Event_L1_Replacement):
  {
    next_state = L1Cache_State_I;
    ff_deallocateL1CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_I_S, L1Cache_Event_L1_WThru):
  {
    next_state = L1Cache_State_I_I;
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pM_profileMiss(addr);
    pw_incPendingWrite(addr);
    d2t_sendDataToL2_fromTBE(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_I_S, L1Cache_Event_L1_Atomic):
  {
    next_state = L1Cache_State_I_I;
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pM_profileMiss(addr);
    pw_incPendingWrite(addr);
    d2t_sendAtomicDataToL2_fromTBE(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_I_S, L1Cache_Event_Data_Done):
  case HASH_FUN(L1Cache_State_SM, L1Cache_Event_Data_Done):
  {
    next_state = L1Cache_State_S;
    pr_decPendingRead(addr);
    dd_writeDataToL1Cache(addr);
    t_updateL1Lifetime(addr);
    h_load_hit(addr);
    s_deallocateTBE(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_I_S, L1Cache_Event_L1_Replacement):
  case HASH_FUN(L1Cache_State_I_I, L1Cache_Event_L1_Replacement):
  case HASH_FUN(L1Cache_State_SM, L1Cache_Event_L1_Replacement):
  {
    return TransitionResult_ProtocolStall;
  }
  case HASH_FUN(L1Cache_State_I_I, L1Cache_Event_Load):
  case HASH_FUN(L1Cache_State_SM, L1Cache_Event_Load):
  {
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pM_profileMiss(addr);
    pr_incPendingRead(addr);
    a_issueGETS(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_I_I, L1Cache_Event_L1_WThru):
  {
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pM_profileMiss(addr);
    pw_incPendingWrite(addr);
    d2t_sendDataToL2_fromTBE(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_I_I, L1Cache_Event_L1_Atomic):
  {
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pM_profileMiss(addr);
    pw_incPendingWrite(addr);
    d2t_sendAtomicDataToL2_fromTBE(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_I_I, L1Cache_Event_Data):
  case HASH_FUN(L1Cache_State_SM, L1Cache_Event_Data):
  {
    pr_decPendingRead(addr);
    h_load_hit(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_I_I, L1Cache_Event_Data_Done):
  {
    next_state = L1Cache_State_I;
    pr_decPendingRead(addr);
    h_load_hit(addr);
    s_deallocateTBE(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_I_I, L1Cache_Event_DataAtomic):
  case HASH_FUN(L1Cache_State_I_I, L1Cache_Event_Ack):
  {
    pw_decPendingWrite(addr);
    hh_store_hit(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_I_I, L1Cache_Event_DataAtomic_Done):
  case HASH_FUN(L1Cache_State_I_I, L1Cache_Event_Ack_Done):
  {
    next_state = L1Cache_State_I;
    pw_decPendingWrite(addr);
    hh_store_hit(addr);
    s_deallocateTBE(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_SM, L1Cache_Event_L1_WThru):
  {
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pH_profileHit(addr);
    pw_incPendingWrite(addr);
    u_sendUpgradeToL2(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_SM, L1Cache_Event_L1_Atomic):
  {
    next_state = L1Cache_State_I_I;
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pH_profileHit(addr);
    pw_incPendingWrite(addr);
    d2t_sendAtomicDataToL2_fromTBE(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_SM, L1Cache_Event_Ack):
  {
    pw_decPendingWrite(addr);
    hh_store_hit(addr);
    t_updateL1Lifetime(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_SM, L1Cache_Event_Ack_Done):
  {
    next_state = L1Cache_State_S;
    pw_decPendingWrite(addr);
    hh_store_hit(addr);
    t_updateL1Lifetime(addr);
    s_deallocateTBE(addr);
    o_popIncomingResponseQueue(addr);
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
