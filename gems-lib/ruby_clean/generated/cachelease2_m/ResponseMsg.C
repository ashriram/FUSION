/** \file ResponseMsg.C
  * 
  * Auto generated C++ code started by symbols/Type.C:479
  */

#include "ResponseMsg.h"

Allocator<ResponseMsg>* ResponseMsg::s_allocator_ptr = NULL;
/** \brief Print the state of this object */
void ResponseMsg::print(ostream& out) const
{
  out << "[ResponseMsg: ";
  out << "Address=" << m_Address << " ";
  out << "Type=" << m_Type << " ";
  out << "Sender=" << m_Sender << " ";
  out << "Destination=" << m_Destination << " ";
  out << "DataBlk=" << m_DataBlk << " ";
  out << "Dirty=" << m_Dirty << " ";
  out << "AckCount=" << m_AckCount << " ";
  out << "MessageSize=" << m_MessageSize << " ";
  out << "Space=" << m_Space << " ";
  out << "RequestSize=" << m_RequestSize << " ";
  out << "liveUntilTime=" << m_liveUntilTime << " ";
  out << "memfetch=" << m_memfetch << " ";
  out << "mfset=" << m_mfset << " ";
  out << "Time=" << getTime() << " ";
  out << "]";
}
