// Auto generated C++ code started by symbols/StateMachine.C:427
// L1Cache: Cache Leasing v2 L1 Cache CMP

#include "Global.h"
#include "RubySlicc_includes.h"
#include "L1Cache_Controller.h"
#include "L1Cache_State.h"
#include "L1Cache_Event.h"
#include "Types.h"
#include "System.h"
#include "Chip.h"

void L1Cache_Controller::wakeup()
{

int counter = 0;
  while (true) {
    // Some cases will put us into an infinite loop without this limit
    assert(counter <= RubyConfig::L1CacheTransitionsPerCycle());
    if (counter == RubyConfig::L1CacheTransitionsPerCycle()) {
      g_system_ptr->getProfiler()->controllerBusy(m_machineID); // Count how often we're fully utilized
      g_eventQueue_ptr->scheduleEvent(this, 1); // Wakeup in another cycle and try again
      break;
    }
    // L1CacheInPort responseIntraChipL1Network_in
      if ((((*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version]))).isReady())) {
        {
          const ResponseMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
                    if (ASSERT_FLAG && !(((((*in_msg_ptr)).m_Destination).isElement(m_machineID)))) {
            cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:295, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

          }
;
          if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_DATA)) {
                        if (ASSERT_FLAG && !(((L1Cache_get_pending_reads(((*in_msg_ptr)).m_Address)) == (1)))) {
              cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:299, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

            }
;
            if (((L1Cache_get_pending_writes(((*in_msg_ptr)).m_Address)) > (0))) {
                            {
                Address addr = ((*in_msg_ptr)).m_Address;
                TransitionResult result = doTransition(L1Cache_Event_Data, L1Cache_getState(addr), addr);
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
                TransitionResult result = doTransition(L1Cache_Event_Data_Done, L1Cache_getState(addr), addr);
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
            if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_DATA_ATOMIC)) {
                            if (ASSERT_FLAG && !(((L1Cache_get_pending_writes(((*in_msg_ptr)).m_Address)) > (0)))) {
                cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:307, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

              }
;
              if ((((L1Cache_get_pending_reads(((*in_msg_ptr)).m_Address)) > (0)) || ((L1Cache_get_pending_writes(((*in_msg_ptr)).m_Address)) > (1)))) {
                                {
                  Address addr = ((*in_msg_ptr)).m_Address;
                  TransitionResult result = doTransition(L1Cache_Event_DataAtomic, L1Cache_getState(addr), addr);
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
                  TransitionResult result = doTransition(L1Cache_Event_DataAtomic_Done, L1Cache_getState(addr), addr);
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
                                if (ASSERT_FLAG && !(((L1Cache_get_pending_writes(((*in_msg_ptr)).m_Address)) > (0)))) {
                  cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:315, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

                }
;
                if ((((L1Cache_get_pending_reads(((*in_msg_ptr)).m_Address)) > (0)) || ((L1Cache_get_pending_writes(((*in_msg_ptr)).m_Address)) > (1)))) {
                                    {
                    Address addr = ((*in_msg_ptr)).m_Address;
                    TransitionResult result = doTransition(L1Cache_Event_Ack, L1Cache_getState(addr), addr);
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
                    TransitionResult result = doTransition(L1Cache_Event_Ack_Done, L1Cache_getState(addr), addr);
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
                                cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:322, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid L1 response type") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
              }
            }
          }
        }
      }

    // L1CacheInPort mandatoryQueue_in
      if ((((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).isReady())) {
        {
          const CacheMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
          if ((((*in_msg_ptr)).m_Type == CacheRequestType_ST)) {
                        {
              Address addr = ((*in_msg_ptr)).m_Address;
              TransitionResult result = doTransition((L1Cache_mandatory_request_type_to_event(((*in_msg_ptr)).m_Type)), L1Cache_getState(addr), addr);
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
            if ((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).isTagPresent(((*in_msg_ptr)).m_Address))) {
                            {
                Address addr = ((*in_msg_ptr)).m_Address;
                TransitionResult result = doTransition((L1Cache_mandatory_request_type_to_event(((*in_msg_ptr)).m_Type)), L1Cache_getState(addr), addr);
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
              if ((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).cacheAvail(((*in_msg_ptr)).m_Address))) {
                                {
                  Address addr = ((*in_msg_ptr)).m_Address;
                  TransitionResult result = doTransition((L1Cache_mandatory_request_type_to_event(((*in_msg_ptr)).m_Type)), L1Cache_getState(addr), addr);
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
                  Address addr = (((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address));
                  TransitionResult result = doTransition(L1Cache_Event_L1_Replacement, L1Cache_getState(addr), addr);
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

    break;  // If we got this far, we have nothing left todo
  }
}

