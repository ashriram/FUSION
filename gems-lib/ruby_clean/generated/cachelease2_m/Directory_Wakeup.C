// Auto generated C++ code started by symbols/StateMachine.C:427
// Directory: Cache Lease V2 protocol

#include "Global.h"
#include "RubySlicc_includes.h"
#include "Directory_Controller.h"
#include "Directory_State.h"
#include "Directory_Event.h"
#include "Types.h"
#include "System.h"
#include "Chip.h"

void Directory_Controller::wakeup()
{

int counter = 0;
  while (true) {
    // Some cases will put us into an infinite loop without this limit
    assert(counter <= RubyConfig::DirectoryTransitionsPerCycle());
    if (counter == RubyConfig::DirectoryTransitionsPerCycle()) {
      g_system_ptr->getProfiler()->controllerBusy(m_machineID); // Count how often we're fully utilized
      g_eventQueue_ptr->scheduleEvent(this, 1); // Wakeup in another cycle and try again
      break;
    }
    // DirectoryInPort requestNetwork_in
      if ((((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).isReady())) {
        {
          const MemoryMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const MemoryMsg*>(((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
          if ((((*in_msg_ptr)).m_Type == MemoryRequestType_MEMORY_READ)) {
                        {
              Address addr = ((*in_msg_ptr)).m_Address;
              TransitionResult result = doTransition(Directory_Event_Fetch, Directory_getState(addr), addr);
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
            if ((((*in_msg_ptr)).m_Type == MemoryRequestType_MEMORY_WB)) {
                            {
                Address addr = ((*in_msg_ptr)).m_Address;
                TransitionResult result = doTransition(Directory_Event_Fetch, Directory_getState(addr), addr);
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
                            cerr << "Runtime Error at ../protocols/FUSION/cachelease2-mem.sm:115, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid message") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
            }
          }
        }
      }

    break;  // If we got this far, we have nothing left todo
  }
}

