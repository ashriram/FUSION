/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L1Cache_Controller.h"

bool L1Cache_Controller::L1Cache_is_write(CacheRequestType param_type)
{
  if (((param_type == CacheRequestType_ST) || (param_type == CacheRequestType_ATOMIC))) {
    return (true);
  } else {
    if ((param_type == CacheRequestType_LD)) {
      return (false);
    } else {
            cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:266, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid CacheRequestType") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
    }
  }
}

