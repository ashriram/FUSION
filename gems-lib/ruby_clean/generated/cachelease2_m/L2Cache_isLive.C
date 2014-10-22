/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L2Cache_Controller.h"

bool L2Cache_Controller::L2Cache_isLive(Address param_addr)
{
    if (ASSERT_FLAG && !((L2Cache_isL2CacheTagPresent(param_addr)))) {
    cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L2cache_m.sm:230, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

  }
;
  return ((time_to_int(((L2Cache_getL2CacheEntry(param_addr))).m_liveUntilTime)) >= (time_to_int((get_time()))));
}

