/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L1Cache_Controller.h"

bool L1Cache_Controller::L1Cache_isLive(Address param_addr)
{
  if ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).isPresent(param_addr))) {
    return ((time_to_int(((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(param_addr))).m_liveUntilTime)) >= (time_to_int((get_time()))));
  } else {
    if ((L1Cache_isL1CacheTagPresent(param_addr))) {
      return ((time_to_int(((L1Cache_getL1CacheEntry(param_addr))).m_liveUntilTime)) >= (time_to_int((get_time()))));
    } else {
            cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:193, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid address passed to isLive() in L1") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
    }
  }
}

