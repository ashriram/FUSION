/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L1Cache_Controller.h"

int L1Cache_Controller::L1Cache_get_pending_writes(Address param_addr)
{
    if (ASSERT_FLAG && !(((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).isPresent(param_addr)) == (true)))) {
    cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:280, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

  }
;
  return ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(param_addr))).m_pendingWrites;
}

