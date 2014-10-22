/** \file L2ExpireTriggerMsg.h
  * 
  * Auto generated C++ code started by symbols/Type.C:227
  */

#ifndef L2ExpireTriggerMsg_H
#define L2ExpireTriggerMsg_H

#include "Global.h"
#include "Allocator.h"
#include "Address.h"
#include "Message.h"
class L2ExpireTriggerMsg :  public Message {
public:
  L2ExpireTriggerMsg() 
  : Message()
  {
    // m_Address has no default
    m_ExpireTime = 0; // default value of Time
  }
  ~L2ExpireTriggerMsg() { };
  L2ExpireTriggerMsg(const Address& local_Address, const Time& local_ExpireTime)
  : Message()
  {
    m_Address = local_Address;
    m_ExpireTime = local_ExpireTime;
  }
  Message* clone() const { checkAllocator(); return s_allocator_ptr->allocate(*this); }
  void destroy() { checkAllocator(); s_allocator_ptr->deallocate(this); }
  static Allocator<L2ExpireTriggerMsg>* s_allocator_ptr;
  static void checkAllocator() { if (s_allocator_ptr == NULL) { s_allocator_ptr = new Allocator<L2ExpireTriggerMsg>; }}
  // Const accessors methods for each field
/** \brief Const accessor method for Address field.
  * \return Address field
  */
  const Address& getAddress() const { return m_Address; }
/** \brief Const accessor method for ExpireTime field.
  * \return ExpireTime field
  */
  const Time& getExpireTime() const { return m_ExpireTime; }

  // Non const Accessors methods for each field
/** \brief Non-const accessor method for Address field.
  * \return Address field
  */
  Address& getAddress() { return m_Address; }
/** \brief Non-const accessor method for ExpireTime field.
  * \return ExpireTime field
  */
  Time& getExpireTime() { return m_ExpireTime; }

  // Mutator methods for each field
/** \brief Mutator method for Address field */
  void setAddress(const Address& local_Address) { m_Address = local_Address; }
/** \brief Mutator method for ExpireTime field */
  void setExpireTime(const Time& local_ExpireTime) { m_ExpireTime = local_ExpireTime; }

  void print(ostream& out) const;
//private:
  Address m_Address; /**< Line address for this request*/
  Time m_ExpireTime; /**< Time scheduled for expiry*/
};
// Output operator declaration
ostream& operator<<(ostream& out, const L2ExpireTriggerMsg& obj);

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const L2ExpireTriggerMsg& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif // L2ExpireTriggerMsg_H
