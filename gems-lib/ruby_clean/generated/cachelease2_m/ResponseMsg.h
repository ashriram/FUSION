/** \file ResponseMsg.h
  * 
  * Auto generated C++ code started by symbols/Type.C:227
  */

#ifndef ResponseMsg_H
#define ResponseMsg_H

#include "Global.h"
#include "Allocator.h"
#include "Address.h"
#include "CoherenceResponseType.h"
#include "MachineID.h"
#include "NetDest.h"
#include "DataBlock.h"
#include "MessageSizeType.h"
#include "MemorySpaceType.h"
#include "MemfetchSet.h"
#include "NetworkMessage.h"
class ResponseMsg :  public NetworkMessage {
public:
  ResponseMsg() 
  : NetworkMessage()
  {
    // m_Address has no default
    m_Type = CoherenceResponseType_NUM; // default value of CoherenceResponseType
    // m_Sender has no default
    // m_Destination has no default
    // m_DataBlk has no default
    m_Dirty = false; // default for this field 
    m_AckCount = 0; // default for this field 
    m_MessageSize = MessageSizeType_Undefined; // default value of MessageSizeType
    m_Space = MemorySpaceType_NULL; // default value of MemorySpaceType
    m_RequestSize = 0; // default value of int
    m_liveUntilTime = 0; // default value of Time
    // m_memfetch has no default
    // m_mfset has no default
  }
  ~ResponseMsg() { };
  ResponseMsg(const Address& local_Address, const CoherenceResponseType& local_Type, const MachineID& local_Sender, const NetDest& local_Destination, const DataBlock& local_DataBlk, const bool& local_Dirty, const int& local_AckCount, const MessageSizeType& local_MessageSize, const MemorySpaceType& local_Space, const int& local_RequestSize, const Time& local_liveUntilTime, const uint64& local_memfetch, const MemfetchSet& local_mfset)
  : NetworkMessage()
  {
    m_Address = local_Address;
    m_Type = local_Type;
    m_Sender = local_Sender;
    m_Destination = local_Destination;
    m_DataBlk = local_DataBlk;
    m_Dirty = local_Dirty;
    m_AckCount = local_AckCount;
    m_MessageSize = local_MessageSize;
    m_Space = local_Space;
    m_RequestSize = local_RequestSize;
    m_liveUntilTime = local_liveUntilTime;
    m_memfetch = local_memfetch;
    m_mfset = local_mfset;
  }
  Message* clone() const { checkAllocator(); return s_allocator_ptr->allocate(*this); }
  void destroy() { checkAllocator(); s_allocator_ptr->deallocate(this); }
  static Allocator<ResponseMsg>* s_allocator_ptr;
  static void checkAllocator() { if (s_allocator_ptr == NULL) { s_allocator_ptr = new Allocator<ResponseMsg>; }}
  // Const accessors methods for each field
/** \brief Const accessor method for Address field.
  * \return Address field
  */
  const Address& getAddress() const { return m_Address; }
/** \brief Const accessor method for Type field.
  * \return Type field
  */
  const CoherenceResponseType& getType() const { return m_Type; }
/** \brief Const accessor method for Sender field.
  * \return Sender field
  */
  const MachineID& getSender() const { return m_Sender; }
/** \brief Const accessor method for Destination field.
  * \return Destination field
  */
  const NetDest& getDestination() const { return m_Destination; }
/** \brief Const accessor method for DataBlk field.
  * \return DataBlk field
  */
  const DataBlock& getDataBlk() const { return m_DataBlk; }
/** \brief Const accessor method for Dirty field.
  * \return Dirty field
  */
  const bool& getDirty() const { return m_Dirty; }
/** \brief Const accessor method for AckCount field.
  * \return AckCount field
  */
  const int& getAckCount() const { return m_AckCount; }
/** \brief Const accessor method for MessageSize field.
  * \return MessageSize field
  */
  const MessageSizeType& getMessageSize() const { return m_MessageSize; }
/** \brief Const accessor method for Space field.
  * \return Space field
  */
  const MemorySpaceType& getSpace() const { return m_Space; }
/** \brief Const accessor method for RequestSize field.
  * \return RequestSize field
  */
  const int& getRequestSize() const { return m_RequestSize; }
/** \brief Const accessor method for liveUntilTime field.
  * \return liveUntilTime field
  */
  const Time& getliveUntilTime() const { return m_liveUntilTime; }
/** \brief Const accessor method for memfetch field.
  * \return memfetch field
  */
  const uint64& getmemfetch() const { return m_memfetch; }
/** \brief Const accessor method for mfset field.
  * \return mfset field
  */
  const MemfetchSet& getmfset() const { return m_mfset; }

  // Non const Accessors methods for each field
/** \brief Non-const accessor method for Address field.
  * \return Address field
  */
  Address& getAddress() { return m_Address; }
/** \brief Non-const accessor method for Type field.
  * \return Type field
  */
  CoherenceResponseType& getType() { return m_Type; }
/** \brief Non-const accessor method for Sender field.
  * \return Sender field
  */
  MachineID& getSender() { return m_Sender; }
/** \brief Non-const accessor method for Destination field.
  * \return Destination field
  */
  NetDest& getDestination() { return m_Destination; }
/** \brief Non-const accessor method for DataBlk field.
  * \return DataBlk field
  */
  DataBlock& getDataBlk() { return m_DataBlk; }
/** \brief Non-const accessor method for Dirty field.
  * \return Dirty field
  */
  bool& getDirty() { return m_Dirty; }
/** \brief Non-const accessor method for AckCount field.
  * \return AckCount field
  */
  int& getAckCount() { return m_AckCount; }
/** \brief Non-const accessor method for MessageSize field.
  * \return MessageSize field
  */
  MessageSizeType& getMessageSize() { return m_MessageSize; }
/** \brief Non-const accessor method for Space field.
  * \return Space field
  */
  MemorySpaceType& getSpace() { return m_Space; }
/** \brief Non-const accessor method for RequestSize field.
  * \return RequestSize field
  */
  int& getRequestSize() { return m_RequestSize; }
/** \brief Non-const accessor method for liveUntilTime field.
  * \return liveUntilTime field
  */
  Time& getliveUntilTime() { return m_liveUntilTime; }
/** \brief Non-const accessor method for memfetch field.
  * \return memfetch field
  */
  uint64& getmemfetch() { return m_memfetch; }
/** \brief Non-const accessor method for mfset field.
  * \return mfset field
  */
  MemfetchSet& getmfset() { return m_mfset; }

  // Mutator methods for each field
/** \brief Mutator method for Address field */
  void setAddress(const Address& local_Address) { m_Address = local_Address; }
/** \brief Mutator method for Type field */
  void setType(const CoherenceResponseType& local_Type) { m_Type = local_Type; }
/** \brief Mutator method for Sender field */
  void setSender(const MachineID& local_Sender) { m_Sender = local_Sender; }
/** \brief Mutator method for Destination field */
  void setDestination(const NetDest& local_Destination) { m_Destination = local_Destination; }
/** \brief Mutator method for DataBlk field */
  void setDataBlk(const DataBlock& local_DataBlk) { m_DataBlk = local_DataBlk; }
/** \brief Mutator method for Dirty field */
  void setDirty(const bool& local_Dirty) { m_Dirty = local_Dirty; }
/** \brief Mutator method for AckCount field */
  void setAckCount(const int& local_AckCount) { m_AckCount = local_AckCount; }
/** \brief Mutator method for MessageSize field */
  void setMessageSize(const MessageSizeType& local_MessageSize) { m_MessageSize = local_MessageSize; }
/** \brief Mutator method for Space field */
  void setSpace(const MemorySpaceType& local_Space) { m_Space = local_Space; }
/** \brief Mutator method for RequestSize field */
  void setRequestSize(const int& local_RequestSize) { m_RequestSize = local_RequestSize; }
/** \brief Mutator method for liveUntilTime field */
  void setliveUntilTime(const Time& local_liveUntilTime) { m_liveUntilTime = local_liveUntilTime; }
/** \brief Mutator method for memfetch field */
  void setmemfetch(const uint64& local_memfetch) { m_memfetch = local_memfetch; }
/** \brief Mutator method for mfset field */
  void setmfset(const MemfetchSet& local_mfset) { m_mfset = local_mfset; }

  void print(ostream& out) const;
//private:
  Address m_Address; /**< Physical address for this request*/
  CoherenceResponseType m_Type; /**< Type of response (Ack, Data, etc)*/
  MachineID m_Sender; /**< What component sent the data*/
  NetDest m_Destination; /**< Node to whom the data is sent*/
  DataBlock m_DataBlk; /**< Data for the cache line*/
  bool m_Dirty; /**< Dirty bit*/
  int m_AckCount; /**< number of acks in this message*/
  MessageSizeType m_MessageSize; /**< size category of the message*/
  MemorySpaceType m_Space; /**< Memory space of request (GLOBAL, LOCAL)*/
  int m_RequestSize; /**< Size of requested data from core*/
  Time m_liveUntilTime; /**< Lifetime of block returned by L2*/
  uint64 m_memfetch; /**< Memfetch pointer of request*/
  MemfetchSet m_mfset; /**< Memfetch pointers returning from L2 (were merged)*/
};
// Output operator declaration
ostream& operator<<(ostream& out, const ResponseMsg& obj);

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const ResponseMsg& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif // ResponseMsg_H
