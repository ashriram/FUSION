/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L1Cache_Controller.h"

L1Cache_Event L1Cache_Controller::L1Cache_mandatory_request_type_to_event(CacheRequestType param_type)
{
  if ((param_type == CacheRequestType_LD)) {
    return L1Cache_Event_Load;
  } else {
    if ((param_type == CacheRequestType_ST)) {
      return L1Cache_Event_L1_WThru;
    } else {
      if ((param_type == CacheRequestType_ATOMIC)) {
        return L1Cache_Event_L1_Atomic;
      } else {
                cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:256, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid CacheRequestType") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
      }
    }
  }
}

