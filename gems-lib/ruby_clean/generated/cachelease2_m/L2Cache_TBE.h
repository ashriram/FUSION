/** \file L2Cache_TBE.h
  * 
  * Auto generated C++ code started by symbols/Type.C:227
  */

#ifndef L2Cache_TBE_H
#define L2Cache_TBE_H

#include "Global.h"
#include "Allocator.h"
#include "Address.h"
#include "L2Cache_State.h"
#include "DataBlock.h"
#include "NetDest.h"
#include "MachineID.h"
#include "NetDest.h"
#include "MemorySpaceType.h"
#include "MemfetchSet.h"
class L2Cache_TBE {
public:
  L2Cache_TBE() 
  {
    // m_Address has no default
    m_TBEState = L2Cache_State_NP; // default value of L2Cache_State
    // m_DataBlk has no default
    m_Dirty = false; // default for this field 
    // m_L1_GetS_IDs has no default
    // m_L1_WBAck_ID has no default
    // m_CPURequestor has no default
    m_pendingAcks = 0; // default for this field 
    m_DataReady = false; // default for this field 
    m_isPrefetch = false; // default value of bool
    m_Space = MemorySpaceType_NULL; // default value of MemorySpaceType
    m_deltaRequested = 0; // default value of Time
    m_RequestSize = 0; // default value of int
    m_liveUntilTime = 0; // default value of Time
    // m_memfetch has no default
    // m_mfset has no default
  }
  ~L2Cache_TBE() { };
  L2Cache_TBE(const Address& local_Address, const L2Cache_State& local_TBEState, const DataBlock& local_DataBlk, const bool& local_Dirty, const NetDest& local_L1_GetS_IDs, const MachineID& local_L1_WBAck_ID, const NetDest& local_CPURequestor, const int& local_pendingAcks, const bool& local_DataReady, const bool& local_isPrefetch, const MemorySpaceType& local_Space, const Time& local_deltaRequested, const int& local_RequestSize, const Time& local_liveUntilTime, const uint64& local_memfetch, const MemfetchSet& local_mfset)
  {
    m_Address = local_Address;
    m_TBEState = local_TBEState;
    m_DataBlk = local_DataBlk;
    m_Dirty = local_Dirty;
    m_L1_GetS_IDs = local_L1_GetS_IDs;
    m_L1_WBAck_ID = local_L1_WBAck_ID;
    m_CPURequestor = local_CPURequestor;
    m_pendingAcks = local_pendingAcks;
    m_DataReady = local_DataReady;
    m_isPrefetch = local_isPrefetch;
    m_Space = local_Space;
    m_deltaRequested = local_deltaRequested;
    m_RequestSize = local_RequestSize;
    m_liveUntilTime = local_liveUntilTime;
    m_memfetch = local_memfetch;
    m_mfset = local_mfset;
  }
  // Const accessors methods for each field
/** \brief Const accessor method for Address field.
  * \return Address field
  */
  const Address& getAddress() const { return m_Address; }
/** \brief Const accessor method for TBEState field.
  * \return TBEState field
  */
  const L2Cache_State& getTBEState() const { return m_TBEState; }
/** \brief Const accessor method for DataBlk field.
  * \return DataBlk field
  */
  const DataBlock& getDataBlk() const { return m_DataBlk; }
/** \brief Const accessor method for Dirty field.
  * \return Dirty field
  */
  const bool& getDirty() const { return m_Dirty; }
/** \brief Const accessor method for L1_GetS_IDs field.
  * \return L1_GetS_IDs field
  */
  const NetDest& getL1_GetS_IDs() const { return m_L1_GetS_IDs; }
/** \brief Const accessor method for L1_WBAck_ID field.
  * \return L1_WBAck_ID field
  */
  const MachineID& getL1_WBAck_ID() const { return m_L1_WBAck_ID; }
/** \brief Const accessor method for CPURequestor field.
  * \return CPURequestor field
  */
  const NetDest& getCPURequestor() const { return m_CPURequestor; }
/** \brief Const accessor method for pendingAcks field.
  * \return pendingAcks field
  */
  const int& getpendingAcks() const { return m_pendingAcks; }
/** \brief Const accessor method for DataReady field.
  * \return DataReady field
  */
  const bool& getDataReady() const { return m_DataReady; }
/** \brief Const accessor method for isPrefetch field.
  * \return isPrefetch field
  */
  const bool& getisPrefetch() const { return m_isPrefetch; }
/** \brief Const accessor method for Space field.
  * \return Space field
  */
  const MemorySpaceType& getSpace() const { return m_Space; }
/** \brief Const accessor method for deltaRequested field.
  * \return deltaRequested field
  */
  const Time& getdeltaRequested() const { return m_deltaRequested; }
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
/** \brief Non-const accessor method for TBEState field.
  * \return TBEState field
  */
  L2Cache_State& getTBEState() { return m_TBEState; }
/** \brief Non-const accessor method for DataBlk field.
  * \return DataBlk field
  */
  DataBlock& getDataBlk() { return m_DataBlk; }
/** \brief Non-const accessor method for Dirty field.
  * \return Dirty field
  */
  bool& getDirty() { return m_Dirty; }
/** \brief Non-const accessor method for L1_GetS_IDs field.
  * \return L1_GetS_IDs field
  */
  NetDest& getL1_GetS_IDs() { return m_L1_GetS_IDs; }
/** \brief Non-const accessor method for L1_WBAck_ID field.
  * \return L1_WBAck_ID field
  */
  MachineID& getL1_WBAck_ID() { return m_L1_WBAck_ID; }
/** \brief Non-const accessor method for CPURequestor field.
  * \return CPURequestor field
  */
  NetDest& getCPURequestor() { return m_CPURequestor; }
/** \brief Non-const accessor method for pendingAcks field.
  * \return pendingAcks field
  */
  int& getpendingAcks() { return m_pendingAcks; }
/** \brief Non-const accessor method for DataReady field.
  * \return DataReady field
  */
  bool& getDataReady() { return m_DataReady; }
/** \brief Non-const accessor method for isPrefetch field.
  * \return isPrefetch field
  */
  bool& getisPrefetch() { return m_isPrefetch; }
/** \brief Non-const accessor method for Space field.
  * \return Space field
  */
  MemorySpaceType& getSpace() { return m_Space; }
/** \brief Non-const accessor method for deltaRequested field.
  * \return deltaRequested field
  */
  Time& getdeltaRequested() { return m_deltaRequested; }
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
/** \brief Mutator method for TBEState field */
  void setTBEState(const L2Cache_State& local_TBEState) { m_TBEState = local_TBEState; }
/** \brief Mutator method for DataBlk field */
  void setDataBlk(const DataBlock& local_DataBlk) { m_DataBlk = local_DataBlk; }
/** \brief Mutator method for Dirty field */
  void setDirty(const bool& local_Dirty) { m_Dirty = local_Dirty; }
/** \brief Mutator method for L1_GetS_IDs field */
  void setL1_GetS_IDs(const NetDest& local_L1_GetS_IDs) { m_L1_GetS_IDs = local_L1_GetS_IDs; }
/** \brief Mutator method for L1_WBAck_ID field */
  void setL1_WBAck_ID(const MachineID& local_L1_WBAck_ID) { m_L1_WBAck_ID = local_L1_WBAck_ID; }
/** \brief Mutator method for CPURequestor field */
  void setCPURequestor(const NetDest& local_CPURequestor) { m_CPURequestor = local_CPURequestor; }
/** \brief Mutator method for pendingAcks field */
  void setpendingAcks(const int& local_pendingAcks) { m_pendingAcks = local_pendingAcks; }
/** \brief Mutator method for DataReady field */
  void setDataReady(const bool& local_DataReady) { m_DataReady = local_DataReady; }
/** \brief Mutator method for isPrefetch field */
  void setisPrefetch(const bool& local_isPrefetch) { m_isPrefetch = local_isPrefetch; }
/** \brief Mutator method for Space field */
  void setSpace(const MemorySpaceType& local_Space) { m_Space = local_Space; }
/** \brief Mutator method for deltaRequested field */
  void setdeltaRequested(const Time& local_deltaRequested) { m_deltaRequested = local_deltaRequested; }
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
  Address m_Address; /**< Physical address for this TBE*/
  L2Cache_State m_TBEState; /**< Transient state*/
  DataBlock m_DataBlk; /**< Buffer for the data block*/
  bool m_Dirty; /**< Data is Dirty*/
  NetDest m_L1_GetS_IDs; /**< Set of the internal processors that want the block in shared state*/
  MachineID m_L1_WBAck_ID; /**< ID of the L1 cache to forward the block to once we get a response*/
  NetDest m_CPURequestor; /**< CPU requestor CPU L2 has to fwd back to*/
  int m_pendingAcks; /**< number of pending acks*/
  bool m_DataReady; /**< Have I got the data*/
  bool m_isPrefetch; /**< Set if this was caused by a prefetch*/
  MemorySpaceType m_Space; /**< Memory space of request (GLOBAL, LOCAL)*/
  Time m_deltaRequested; /**< Delta time requested*/
  int m_RequestSize; /**< Size of request data*/
  Time m_liveUntilTime; /**< Live until time for L2 replacement TBEs*/
  uint64 m_memfetch; /**< Memfetch of requestor thread*/
  MemfetchSet m_mfset; /**< Set of memfetchs received so far in this TBE*/
};
// Output operator declaration
ostream& operator<<(ostream& out, const L2Cache_TBE& obj);

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const L2Cache_TBE& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif // L2Cache_TBE_H
