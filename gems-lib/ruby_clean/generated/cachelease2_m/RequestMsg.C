/** \file RequestMsg.C
  * 
  * Auto generated C++ code started by symbols/Type.C:479
  */

#include "RequestMsg.h"

Allocator<RequestMsg>* RequestMsg::s_allocator_ptr = NULL;
/** \brief Print the state of this object */
void RequestMsg::print(ostream& out) const
{
  out << "[RequestMsg: ";
  out << "Address=" << m_Address << " ";
  out << "Type=" << m_Type << " ";
  out << "AccessMode=" << m_AccessMode << " ";
  out << "Requestor=" << m_Requestor << " ";
  out << "Destination=" << m_Destination << " ";
  out << "OriginalRequestorMachId=" << m_OriginalRequestorMachId << " ";
  out << "MessageSize=" << m_MessageSize << " ";
  out << "DataBlk=" << m_DataBlk << " ";
  out << "Dirty=" << m_Dirty << " ";
  out << "Prefetch=" << m_Prefetch << " ";
  out << "Space=" << m_Space << " ";
  out << "RequestSize=" << m_RequestSize << " ";
  out << "deltaRequested=" << m_deltaRequested << " ";
  out << "liveUntilTime=" << m_liveUntilTime << " ";
  out << "memfetch=" << m_memfetch << " ";
  out << "Time=" << getTime() << " ";
  out << "]";
}
