/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L1Cache_Controller.h"

L1Cache_State L1Cache_Controller::L1Cache_getState(Address param_addr)
{
  if (((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).isTagPresent(param_addr)) == (true))) {
    DEBUG_SLICC(MedPrio, "../protocols/FUSION/cachelease2-L1cache.sm:219: ", m_chip_ptr->getID());
;
    DEBUG_SLICC(MedPrio, "../protocols/FUSION/cachelease2-L1cache.sm:220: ", param_addr);
;
  }
  if ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).isPresent(param_addr))) {
    if (((((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(param_addr))).m_TBEState == L1Cache_State_SM) && ((L1Cache_isLive(param_addr)) == (false)))) {
      return L1Cache_State_I_I;
    } else {
      return ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(param_addr))).m_TBEState;
    }
  } else {
    if ((L1Cache_isL1CacheTagPresent(param_addr))) {
      if (((L1Cache_isLive(param_addr)) == (false))) {
        return L1Cache_State_I;
      } else {
        return ((L1Cache_getL1CacheEntry(param_addr))).m_CacheState;
      }
    }
  }
  return L1Cache_State_I;
}

