/** \file L1Cache_TBE.h
  * 
  * Auto generated C++ code started by symbols/Type.C:227
  */

#ifndef L1Cache_TBE_H
#define L1Cache_TBE_H

#include "Global.h"
#include "Allocator.h"
#include "Address.h"
#include "L1Cache_State.h"
#include "DataBlock.h"
#include "MemorySpaceType.h"
class L1Cache_TBE {
public:
  L1Cache_TBE() 
  {
    // m_Address has no default
    m_TBEState = L1Cache_State_I; // default value of L1Cache_State
    // m_DataBlk has no default
    m_isPrefetch = false; // default value of bool
    m_pendingAcks = 0; // default for this field 
    m_Space = MemorySpaceType_NULL; // default value of MemorySpaceType
    m_ThreadID = 0; // default value of int
    m_liveUntilTime = 0; // default value of Time
    m_pendingReads = 0; // default value of int
    m_pendingWrites = 0; // default value of int
  }
  ~L1Cache_TBE() { };
  L1Cache_TBE(const Address& local_Address, const L1Cache_State& local_TBEState, const DataBlock& local_DataBlk, const bool& local_isPrefetch, const int& local_pendingAcks, const MemorySpaceType& local_Space, const int& local_ThreadID, const Time& local_liveUntilTime, const int& local_pendingReads, const int& local_pendingWrites)
  {
    m_Address = local_Address;
    m_TBEState = local_TBEState;
    m_DataBlk = local_DataBlk;
    m_isPrefetch = local_isPrefetch;
    m_pendingAcks = local_pendingAcks;
    m_Space = local_Space;
    m_ThreadID = local_ThreadID;
    m_liveUntilTime = local_liveUntilTime;
    m_pendingReads = local_pendingReads;
    m_pendingWrites = local_pendingWrites;
  }
  // Const accessors methods for each field
/** \brief Const accessor method for Address field.
  * \return Address field
  */
  const Address& getAddress() const { return m_Address; }
/** \brief Const accessor method for TBEState field.
  * \return TBEState field
  */
  const L1Cache_State& getTBEState() const { return m_TBEState; }
/** \brief Const accessor method for DataBlk field.
  * \return DataBlk field
  */
  const DataBlock& getDataBlk() const { return m_DataBlk; }
/** \brief Const accessor method for isPrefetch field.
  * \return isPrefetch field
  */
  const bool& getisPrefetch() const { return m_isPrefetch; }
/** \brief Const accessor method for pendingAcks field.
  * \return pendingAcks field
  */
  const int& getpendingAcks() const { return m_pendingAcks; }
/** \brief Const accessor method for Space field.
  * \return Space field
  */
  const MemorySpaceType& getSpace() const { return m_Space; }
/** \brief Const accessor method for ThreadID field.
  * \return ThreadID field
  */
  const int& getThreadID() const { return m_ThreadID; }
/** \brief Const accessor method for liveUntilTime field.
  * \return liveUntilTime field
  */
  const Time& getliveUntilTime() const { return m_liveUntilTime; }
/** \brief Const accessor method for pendingReads field.
  * \return pendingReads field
  */
  const int& getpendingReads() const { return m_pendingReads; }
/** \brief Const accessor method for pendingWrites field.
  * \return pendingWrites field
  */
  const int& getpendingWrites() const { return m_pendingWrites; }

  // Non const Accessors methods for each field
/** \brief Non-const accessor method for Address field.
  * \return Address field
  */
  Address& getAddress() { return m_Address; }
/** \brief Non-const accessor method for TBEState field.
  * \return TBEState field
  */
  L1Cache_State& getTBEState() { return m_TBEState; }
/** \brief Non-const accessor method for DataBlk field.
  * \return DataBlk field
  */
  DataBlock& getDataBlk() { return m_DataBlk; }
/** \brief Non-const accessor method for isPrefetch field.
  * \return isPrefetch field
  */
  bool& getisPrefetch() { return m_isPrefetch; }
/** \brief Non-const accessor method for pendingAcks field.
  * \return pendingAcks field
  */
  int& getpendingAcks() { return m_pendingAcks; }
/** \brief Non-const accessor method for Space field.
  * \return Space field
  */
  MemorySpaceType& getSpace() { return m_Space; }
/** \brief Non-const accessor method for ThreadID field.
  * \return ThreadID field
  */
  int& getThreadID() { return m_ThreadID; }
/** \brief Non-const accessor method for liveUntilTime field.
  * \return liveUntilTime field
  */
  Time& getliveUntilTime() { return m_liveUntilTime; }
/** \brief Non-const accessor method for pendingReads field.
  * \return pendingReads field
  */
  int& getpendingReads() { return m_pendingReads; }
/** \brief Non-const accessor method for pendingWrites field.
  * \return pendingWrites field
  */
  int& getpendingWrites() { return m_pendingWrites; }

  // Mutator methods for each field
/** \brief Mutator method for Address field */
  void setAddress(const Address& local_Address) { m_Address = local_Address; }
/** \brief Mutator method for TBEState field */
  void setTBEState(const L1Cache_State& local_TBEState) { m_TBEState = local_TBEState; }
/** \brief Mutator method for DataBlk field */
  void setDataBlk(const DataBlock& local_DataBlk) { m_DataBlk = local_DataBlk; }
/** \brief Mutator method for isPrefetch field */
  void setisPrefetch(const bool& local_isPrefetch) { m_isPrefetch = local_isPrefetch; }
/** \brief Mutator method for pendingAcks field */
  void setpendingAcks(const int& local_pendingAcks) { m_pendingAcks = local_pendingAcks; }
/** \brief Mutator method for Space field */
  void setSpace(const MemorySpaceType& local_Space) { m_Space = local_Space; }
/** \brief Mutator method for ThreadID field */
  void setThreadID(const int& local_ThreadID) { m_ThreadID = local_ThreadID; }
/** \brief Mutator method for liveUntilTime field */
  void setliveUntilTime(const Time& local_liveUntilTime) { m_liveUntilTime = local_liveUntilTime; }
/** \brief Mutator method for pendingReads field */
  void setpendingReads(const int& local_pendingReads) { m_pendingReads = local_pendingReads; }
/** \brief Mutator method for pendingWrites field */
  void setpendingWrites(const int& local_pendingWrites) { m_pendingWrites = local_pendingWrites; }

  void print(ostream& out) const;
//private:
  Address m_Address; /**< Physical address for this TBE*/
  L1Cache_State m_TBEState; /**< Transient state*/
  DataBlock m_DataBlk; /**< Buffer for the data block*/
  bool m_isPrefetch; /**< Set if this was caused by a prefetch*/
  int m_pendingAcks; /**< number of pending acks*/
  MemorySpaceType m_Space; /**< Memory space of request (GLOBAL, LOCAL)*/
  int m_ThreadID; /**< The SMT thread that initiated this request*/
  Time m_liveUntilTime; /**< lifetime of the cache block*/
  int m_pendingReads; /**< Number of outstanding read requests (should not exceed 1)*/
  int m_pendingWrites; /**< Number of outstanding write requests*/
};
// Output operator declaration
ostream& operator<<(ostream& out, const L1Cache_TBE& obj);

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const L1Cache_TBE& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif // L1Cache_TBE_H
