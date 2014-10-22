/** \file FenceTriggerMsg.h
  * 
  * Auto generated C++ code started by symbols/Type.C:227
  */

#ifndef FenceTriggerMsg_H
#define FenceTriggerMsg_H

#include "Global.h"
#include "Allocator.h"
#include "Address.h"
#include "TriggerType.h"
#include "Message.h"
class FenceTriggerMsg :  public Message {
public:
  FenceTriggerMsg() 
  : Message()
  {
    // m_Address has no default
    m_Type = TriggerType_NUM; // default value of TriggerType
    m_ThreadID = 0; // default value of int
    m_FenceCompleteTime = 0; // default value of Time
  }
  ~FenceTriggerMsg() { };
  FenceTriggerMsg(const Address& local_Address, const TriggerType& local_Type, const int& local_ThreadID, const Time& local_FenceCompleteTime)
  : Message()
  {
    m_Address = local_Address;
    m_Type = local_Type;
    m_ThreadID = local_ThreadID;
    m_FenceCompleteTime = local_FenceCompleteTime;
  }
  Message* clone() const { checkAllocator(); return s_allocator_ptr->allocate(*this); }
  void destroy() { checkAllocator(); s_allocator_ptr->deallocate(this); }
  static Allocator<FenceTriggerMsg>* s_allocator_ptr;
  static void checkAllocator() { if (s_allocator_ptr == NULL) { s_allocator_ptr = new Allocator<FenceTriggerMsg>; }}
  // Const accessors methods for each field
/** \brief Const accessor method for Address field.
  * \return Address field
  */
  const Address& getAddress() const { return m_Address; }
/** \brief Const accessor method for Type field.
  * \return Type field
  */
  const TriggerType& getType() const { return m_Type; }
/** \brief Const accessor method for ThreadID field.
  * \return ThreadID field
  */
  const int& getThreadID() const { return m_ThreadID; }
/** \brief Const accessor method for FenceCompleteTime field.
  * \return FenceCompleteTime field
  */
  const Time& getFenceCompleteTime() const { return m_FenceCompleteTime; }

  // Non const Accessors methods for each field
/** \brief Non-const accessor method for Address field.
  * \return Address field
  */
  Address& getAddress() { return m_Address; }
/** \brief Non-const accessor method for Type field.
  * \return Type field
  */
  TriggerType& getType() { return m_Type; }
/** \brief Non-const accessor method for ThreadID field.
  * \return ThreadID field
  */
  int& getThreadID() { return m_ThreadID; }
/** \brief Non-const accessor method for FenceCompleteTime field.
  * \return FenceCompleteTime field
  */
  Time& getFenceCompleteTime() { return m_FenceCompleteTime; }

  // Mutator methods for each field
/** \brief Mutator method for Address field */
  void setAddress(const Address& local_Address) { m_Address = local_Address; }
/** \brief Mutator method for Type field */
  void setType(const TriggerType& local_Type) { m_Type = local_Type; }
/** \brief Mutator method for ThreadID field */
  void setThreadID(const int& local_ThreadID) { m_ThreadID = local_ThreadID; }
/** \brief Mutator method for FenceCompleteTime field */
  void setFenceCompleteTime(const Time& local_FenceCompleteTime) { m_FenceCompleteTime = local_FenceCompleteTime; }

  void print(ostream& out) const;
//private:
  Address m_Address; /**< Line address for this request*/
  TriggerType m_Type; /**< Type of trigger*/
  int m_ThreadID; /**< Warp whose fence is completing*/
  Time m_FenceCompleteTime; /**< Time that fence should complete*/
};
// Output operator declaration
ostream& operator<<(ostream& out, const FenceTriggerMsg& obj);

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const FenceTriggerMsg& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif // FenceTriggerMsg_H
