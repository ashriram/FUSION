// Auto generated C++ code started by symbols/StateMachine.C:427
// L2Cache: Cache Leasing v2 L2 Cache CMP

#include "Global.h"
#include "RubySlicc_includes.h"
#include "L2Cache_Controller.h"
#include "L2Cache_State.h"
#include "L2Cache_Event.h"
#include "Types.h"
#include "System.h"
#include "Chip.h"

void L2Cache_Controller::wakeup()
{

int counter = 0;
  while (true) {
    // Some cases will put us into an infinite loop without this limit
    assert(counter <= RubyConfig::L2CacheTransitionsPerCycle());
    if (counter == RubyConfig::L2CacheTransitionsPerCycle()) {
      g_system_ptr->getProfiler()->controllerBusy(m_machineID); // Count how often we're fully utilized
      g_eventQueue_ptr->scheduleEvent(this, 1); // Wakeup in another cycle and try again
      break;
    }
    // L2CacheInPort L2ExpireTriggerQueue_in
      if ((((*(m_chip_ptr->m_L2Cache_L2ExpireTriggerQueue_vec[m_version]))).isReady())) {
        {
          const L2ExpireTriggerMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const L2ExpireTriggerMsg*>(((*(m_chip_ptr->m_L2Cache_L2ExpireTriggerQueue_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
                    if (ASSERT_FLAG && !((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).isPresent(((*in_msg_ptr)).m_Address)))) {
            cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:363, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

          }
;
                    if (ASSERT_FLAG && !(((time_to_int(((*in_msg_ptr)).m_ExpireTime)) <= (time_to_int((get_time())))))) {
            cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:364, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

          }
;
                    {
            Address addr = ((*in_msg_ptr)).m_Address;
            TransitionResult result = doTransition(L2Cache_Event_L2_Expire, L2Cache_getState(addr), addr);
            if (result == TransitionResult_Valid) {
              counter++;
              continue; // Check the first port again
            }
            if (result == TransitionResult_ResourceStall) {
              g_eventQueue_ptr->scheduleEvent(this, 1);
              // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
            }
            if (result == TransitionResult_ProtocolStall) {
              g_eventQueue_ptr->scheduleEvent(this, 1);
              // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
            }
          }
;
        }
      }

    // L2CacheInPort L1RequestIntraChipL2Network_in
      if ((((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).isReady())) {
        {
          const RequestMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
                    if (ASSERT_FLAG && !(((machineIDToMachineType(((*in_msg_ptr)).m_Requestor)) == MachineType_L1Cache))) {
            cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:375, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

          }
;
                    if (ASSERT_FLAG && !(((((*in_msg_ptr)).m_Destination).isElement(m_machineID)))) {
            cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:376, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

          }
;
          if ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).isTagPresent(((*in_msg_ptr)).m_Address))) {
                        {
              Address addr = ((*in_msg_ptr)).m_Address;
              TransitionResult result = doTransition((L2Cache_L1Cache_request_type_to_event(((*in_msg_ptr)).m_Type, ((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_liveUntilTime)), L2Cache_getState(addr), addr);
              if (result == TransitionResult_Valid) {
                counter++;
                continue; // Check the first port again
              }
              if (result == TransitionResult_ResourceStall) {
                g_eventQueue_ptr->scheduleEvent(this, 1);
                // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
              }
              if (result == TransitionResult_ProtocolStall) {
                g_eventQueue_ptr->scheduleEvent(this, 1);
                // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
              }
            }
;
          } else {
            if ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).cacheAvail(((*in_msg_ptr)).m_Address))) {
                            {
                Address addr = ((*in_msg_ptr)).m_Address;
                TransitionResult result = doTransition((L2Cache_L1Cache_request_type_to_event(((*in_msg_ptr)).m_Type, ((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_liveUntilTime)), L2Cache_getState(addr), addr);
                if (result == TransitionResult_Valid) {
                  counter++;
                  continue; // Check the first port again
                }
                if (result == TransitionResult_ResourceStall) {
                  g_eventQueue_ptr->scheduleEvent(this, 1);
                  // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                }
                if (result == TransitionResult_ProtocolStall) {
                  g_eventQueue_ptr->scheduleEvent(this, 1);
                  // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                }
              }
;
            } else {
              if (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address))))).m_Dirty) {
                                {
                  Address addr = (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address));
                  TransitionResult result = doTransition(L2Cache_Event_L2_Replacement, L2Cache_getState(addr), addr);
                  if (result == TransitionResult_Valid) {
                    counter++;
                    continue; // Check the first port again
                  }
                  if (result == TransitionResult_ResourceStall) {
                    g_eventQueue_ptr->scheduleEvent(this, 1);
                    // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                  }
                  if (result == TransitionResult_ProtocolStall) {
                    g_eventQueue_ptr->scheduleEvent(this, 1);
                    // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                  }
                }
;
              } else {
                                {
                  Address addr = (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address));
                  TransitionResult result = doTransition(L2Cache_Event_L2_Replacement_clean, L2Cache_getState(addr), addr);
                  if (result == TransitionResult_Valid) {
                    counter++;
                    continue; // Check the first port again
                  }
                  if (result == TransitionResult_ResourceStall) {
                    g_eventQueue_ptr->scheduleEvent(this, 1);
                    // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                  }
                  if (result == TransitionResult_ProtocolStall) {
                    g_eventQueue_ptr->scheduleEvent(this, 1);
                    // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                  }
                }
;
              }
            }
          }
        }
      }

    // L2CacheInPort responseCPUNetwork_in
      if ((((*(m_chip_ptr->m_L2Cache_responseToL2TCache_vec[m_version]))).isReady())) {
        {
          const ResponseMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2TCache_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
                    if (ASSERT_FLAG && !(((((*in_msg_ptr)).m_Destination).isElement(m_machineID)))) {
            cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:405, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

          }
;
          if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_DATA)) {
            if (((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(((*in_msg_ptr)).m_Address))).m_pendingAcks - ((*in_msg_ptr)).m_AckCount) == (0))) {
                            {
                Address addr = ((*in_msg_ptr)).m_Address;
                TransitionResult result = doTransition(L2Cache_Event_Data_all_Acks, L2Cache_getState(addr), addr);
                if (result == TransitionResult_Valid) {
                  counter++;
                  continue; // Check the first port again
                }
                if (result == TransitionResult_ResourceStall) {
                  g_eventQueue_ptr->scheduleEvent(this, 1);
                  // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                }
                if (result == TransitionResult_ProtocolStall) {
                  g_eventQueue_ptr->scheduleEvent(this, 1);
                  // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                }
              }
;
            } else {
                            {
                Address addr = ((*in_msg_ptr)).m_Address;
                TransitionResult result = doTransition(L2Cache_Event_Data, L2Cache_getState(addr), addr);
                if (result == TransitionResult_Valid) {
                  counter++;
                  continue; // Check the first port again
                }
                if (result == TransitionResult_ResourceStall) {
                  g_eventQueue_ptr->scheduleEvent(this, 1);
                  // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                }
                if (result == TransitionResult_ProtocolStall) {
                  g_eventQueue_ptr->scheduleEvent(this, 1);
                  // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                }
              }
;
            }
          } else {
            if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_ACK)) {
              if ((((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(((*in_msg_ptr)).m_Address))).m_pendingAcks - ((*in_msg_ptr)).m_AckCount) == (0)) && (((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(((*in_msg_ptr)).m_Address))).m_DataReady == (true)))) {
                                {
                  Address addr = ((*in_msg_ptr)).m_Address;
                  TransitionResult result = doTransition(L2Cache_Event_Ack_all, L2Cache_getState(addr), addr);
                  if (result == TransitionResult_Valid) {
                    counter++;
                    continue; // Check the first port again
                  }
                  if (result == TransitionResult_ResourceStall) {
                    g_eventQueue_ptr->scheduleEvent(this, 1);
                    // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                  }
                  if (result == TransitionResult_ProtocolStall) {
                    g_eventQueue_ptr->scheduleEvent(this, 1);
                    // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                  }
                }
;
              } else {
                                {
                  Address addr = ((*in_msg_ptr)).m_Address;
                  TransitionResult result = doTransition(L2Cache_Event_Ack, L2Cache_getState(addr), addr);
                  if (result == TransitionResult_Valid) {
                    counter++;
                    continue; // Check the first port again
                  }
                  if (result == TransitionResult_ResourceStall) {
                    g_eventQueue_ptr->scheduleEvent(this, 1);
                    // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                  }
                  if (result == TransitionResult_ProtocolStall) {
                    g_eventQueue_ptr->scheduleEvent(this, 1);
                    // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                  }
                }
;
              }
            } else {
              if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_WB_ACK)) {
                                {
                  Address addr = ((*in_msg_ptr)).m_Address;
                  TransitionResult result = doTransition(L2Cache_Event_WB_Ack, L2Cache_getState(addr), addr);
                  if (result == TransitionResult_Valid) {
                    counter++;
                    continue; // Check the first port again
                  }
                  if (result == TransitionResult_ResourceStall) {
                    g_eventQueue_ptr->scheduleEvent(this, 1);
                    // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                  }
                  if (result == TransitionResult_ProtocolStall) {
                    g_eventQueue_ptr->scheduleEvent(this, 1);
                    // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                  }
                }
;
              } else {
                                cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:424, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid L1 response type. I should not be getting DATA_EXCLUSIVES as I don't issue GETSs. Similarly, I should not be triggering DataS_L1 events as I can never be in the IS_I states") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
              }
            }
          }
        }
      }

    // L2CacheInPort requestCPUNetwork_in
      if ((((*(m_chip_ptr->m_L2Cache_requestToL2TCache_vec[m_version]))).isReady())) {
        {
          const RequestMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_requestToL2TCache_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
                    if (ASSERT_FLAG && !(((((*in_msg_ptr)).m_Destination).isElement(m_machineID)))) {
            cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:435, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

          }
;
          if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_INV)) {
                        {
              Address addr = ((*in_msg_ptr)).m_Address;
              TransitionResult result = doTransition(L2Cache_Event_Inv, L2Cache_getState(addr), addr);
              if (result == TransitionResult_Valid) {
                counter++;
                continue; // Check the first port again
              }
              if (result == TransitionResult_ResourceStall) {
                g_eventQueue_ptr->scheduleEvent(this, 1);
                // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
              }
              if (result == TransitionResult_ProtocolStall) {
                g_eventQueue_ptr->scheduleEvent(this, 1);
                // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
              }
            }
;
          } else {
            if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETX)) {
                            {
                Address addr = ((*in_msg_ptr)).m_Address;
                TransitionResult result = doTransition(L2Cache_Event_Fwd_GETX, L2Cache_getState(addr), addr);
                if (result == TransitionResult_Valid) {
                  counter++;
                  continue; // Check the first port again
                }
                if (result == TransitionResult_ResourceStall) {
                  g_eventQueue_ptr->scheduleEvent(this, 1);
                  // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                }
                if (result == TransitionResult_ProtocolStall) {
                  g_eventQueue_ptr->scheduleEvent(this, 1);
                  // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                }
              }
;
            } else {
              if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETS)) {
                                {
                  Address addr = ((*in_msg_ptr)).m_Address;
                  TransitionResult result = doTransition(L2Cache_Event_Fwd_GETS, L2Cache_getState(addr), addr);
                  if (result == TransitionResult_Valid) {
                    counter++;
                    continue; // Check the first port again
                  }
                  if (result == TransitionResult_ResourceStall) {
                    g_eventQueue_ptr->scheduleEvent(this, 1);
                    // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                  }
                  if (result == TransitionResult_ProtocolStall) {
                    g_eventQueue_ptr->scheduleEvent(this, 1);
                    // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                  }
                }
;
              } else {
                                cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:444, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid forwarded request type. Should not get Upgrades as CPU and accelerator do not do read sharing") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
              }
            }
          }
        }
      }

    break;  // If we got this far, we have nothing left todo
  }
}

