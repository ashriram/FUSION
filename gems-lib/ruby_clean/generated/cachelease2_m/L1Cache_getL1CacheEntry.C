/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L1Cache_Controller.h"

L1Cache_Entry& L1Cache_Controller::L1Cache_getL1CacheEntry(Address param_addr)
{
  if ((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).isTagPresent(param_addr))) {
    return (((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).lookup(param_addr));
  } else {
    DEBUG_SLICC(MedPrio, "../protocols/FUSION/cachelease2-L1cache.sm:166: ", param_addr);
;
        cerr << "Runtime Error at ../protocols/FUSION/cachelease2-L1cache.sm:167, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("cannot get L1 entry, L1 block not present") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
  }
}

