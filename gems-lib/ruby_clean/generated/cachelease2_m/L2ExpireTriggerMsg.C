/** \file L2ExpireTriggerMsg.C
  * 
  * Auto generated C++ code started by symbols/Type.C:479
  */

#include "L2ExpireTriggerMsg.h"

Allocator<L2ExpireTriggerMsg>* L2ExpireTriggerMsg::s_allocator_ptr = NULL;
/** \brief Print the state of this object */
void L2ExpireTriggerMsg::print(ostream& out) const
{
  out << "[L2ExpireTriggerMsg: ";
  out << "Address=" << m_Address << " ";
  out << "ExpireTime=" << m_ExpireTime << " ";
  out << "Time=" << getTime() << " ";
  out << "]";
}
