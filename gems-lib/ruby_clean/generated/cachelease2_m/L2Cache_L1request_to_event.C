/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L2Cache_Controller.h"

L2Cache_Event L2Cache_Controller::L2Cache_L1request_to_event(CoherenceRequestType param_type, Address param_addr, Time param_msgLiveUntilTime)
{
  if ((param_type == CoherenceRequestType_DATA)) {
    return L2Cache_Event_L1_Write;
  } else {
    if ((param_type == CoherenceRequestType_DATA_ATOMIC)) {
      return L2Cache_Event_L2_Atomic;
    } else {
      if ((param_type == CoherenceRequestType_DATA_UPGRADE)) {
        if (((L2Cache_isL2CacheTagPresent(param_addr)) && ((L2Cache_isLive(param_addr)) == (true)))) {
          if ((((L2Cache_getL2CacheEntry(param_addr))).m_liveUntilTime == param_msgLiveUntilTime)) {
            return L2Cache_Event_L1_Upgrade_T;
          } else {
            return L2Cache_Event_L1_Upgrade_NT;
          }
        } else {
          return L2Cache_Event_L1_Upgrade_NT;
        }
      } else {
                cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:338, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("unknown message type") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
      }
    }
  }
}

