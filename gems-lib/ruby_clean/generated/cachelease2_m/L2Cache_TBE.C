/** \file L2Cache_TBE.C
  * 
  * Auto generated C++ code started by symbols/Type.C:479
  */

#include "L2Cache_TBE.h"

/** \brief Print the state of this object */
void L2Cache_TBE::print(ostream& out) const
{
  out << "[L2Cache_TBE: ";
  out << "Address=" << m_Address << " ";
  out << "TBEState=" << m_TBEState << " ";
  out << "DataBlk=" << m_DataBlk << " ";
  out << "Dirty=" << m_Dirty << " ";
  out << "L1_GetS_IDs=" << m_L1_GetS_IDs << " ";
  out << "L1_WBAck_ID=" << m_L1_WBAck_ID << " ";
  out << "CPURequestor=" << m_CPURequestor << " ";
  out << "pendingAcks=" << m_pendingAcks << " ";
  out << "DataReady=" << m_DataReady << " ";
  out << "isPrefetch=" << m_isPrefetch << " ";
  out << "Space=" << m_Space << " ";
  out << "deltaRequested=" << m_deltaRequested << " ";
  out << "RequestSize=" << m_RequestSize << " ";
  out << "liveUntilTime=" << m_liveUntilTime << " ";
  out << "memfetch=" << m_memfetch << " ";
  out << "mfset=" << m_mfset << " ";
  out << "]";
}
