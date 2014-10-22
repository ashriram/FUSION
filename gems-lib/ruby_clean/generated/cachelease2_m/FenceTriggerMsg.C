/** \file FenceTriggerMsg.C
  * 
  * Auto generated C++ code started by symbols/Type.C:479
  */

#include "FenceTriggerMsg.h"

Allocator<FenceTriggerMsg>* FenceTriggerMsg::s_allocator_ptr = NULL;
/** \brief Print the state of this object */
void FenceTriggerMsg::print(ostream& out) const
{
  out << "[FenceTriggerMsg: ";
  out << "Address=" << m_Address << " ";
  out << "Type=" << m_Type << " ";
  out << "ThreadID=" << m_ThreadID << " ";
  out << "FenceCompleteTime=" << m_FenceCompleteTime << " ";
  out << "Time=" << getTime() << " ";
  out << "]";
}
