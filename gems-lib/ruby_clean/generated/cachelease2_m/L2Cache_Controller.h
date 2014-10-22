/** \file L2Cache.h
  * 
  * Auto generated C++ code started by symbols/StateMachine.C:252
  * Created by slicc definition of Module "Cache Leasing v2 L2 Cache CMP"
  */

#ifndef L2Cache_CONTROLLER_H
#define L2Cache_CONTROLLER_H

#include "Global.h"
#include "Consumer.h"
#include "TransitionResult.h"
#include "Types.h"
#include "L2Cache_Profiler.h"

extern stringstream L2Cache_transitionComment;
class L2Cache_Controller : public Consumer {
#ifdef CHECK_COHERENCE
  friend class Chip;
#endif /* CHECK_COHERENCE */
public:
  L2Cache_Controller(Chip* chip_ptr, int version);
  void print(ostream& out) const;
  void wakeup();
  static void dumpStats(ostream& out) { s_profiler.dumpStats(out); }
  static void clearStats() { s_profiler.clearStats(); }
private:
  TransitionResult doTransition(L2Cache_Event event, L2Cache_State state, const Address& addr);  // in L2Cache_Transitions.C
  TransitionResult doTransitionWorker(L2Cache_Event event, L2Cache_State state, L2Cache_State& next_state, const Address& addr);  // in L2Cache_Transitions.C
  Chip* m_chip_ptr;
  NodeID m_id;
  NodeID m_version;
  MachineID m_machineID;
  static L2Cache_Profiler s_profiler;
  // Internal functions
  L2Cache_Entry& L2Cache_getL2CacheEntry(Address param_addr);
  void L2Cache_changeL2Permission(Address param_addr, AccessPermission param_permission);
  string L2Cache_getCoherenceRequestTypeStr(CoherenceRequestType param_type);
  bool L2Cache_isL2CacheTagPresent(Address param_addr);
  bool L2Cache_isLive(Address param_addr);
  L2Cache_State L2Cache_getState(Address param_addr);
  string L2Cache_getStateStr(Address param_addr);
  void L2Cache_setState(Address param_addr, L2Cache_State param_state);
  L2Cache_Event L2Cache_L1Cache_request_type_to_event(CoherenceRequestType param_type, Address param_addr, Time param_msgLiveUntilTime);
  void L2Cache_addSharer(Address param_addr, MachineID param_requestor);
  bool L2Cache_isOneSharerLeft(Address param_addr, MachineID param_requestor);
  bool L2Cache_isSharer(Address param_addr, MachineID param_requestor);
  L2Cache_Event L2Cache_L1request_to_event(CoherenceRequestType param_type, Address param_addr, Time param_msgLiveUntilTime);
  // Actions
/** \brief fetch data from memory*/
  void a_issueFetchToMemory(const Address& addr);
/** \brief fetch data from memory for store*/
  void a_issueFetchToMemoryForStore(const Address& addr);
/** \brief send data to the L2 cache (PUTX)*/
  void c_exclusiveReplacement(const Address& addr);
/** \brief Send data+timestamp from cache to requestor in request queue*/
  void ds_sendDataToRequestor(const Address& addr);
/** \brief Send data+timestamp from cache to all GetS IDs from TBE*/
  void dst_sendDataToGetSRequestors(const Address& addr);
/** \brief Send atomic data from cache to requestor in response queue*/
  void ds_sendAtomicDataGlobalToRequestor(const Address& addr);
/** \brief Send atomic data + timestamp from cache to requestor from TBE*/
  void dst_sendAtomicDataToGetSRequestors(const Address& addr);
/** \brief Send Ack (non-global) from cache to requestor*/
  void wa_sendAckToRequestor(const Address& addr);
/** \brief Send ack (non-global) from cache to requestor from TBE*/
  void wat_sendAckToRequestorFromTBE(const Address& addr);
/** \brief Allocate TBE from L1 request queue*/
  void i_allocateTBE(const Address& addr);
/** \brief Allocate TBE from L1 response queue*/
  void il_allocateTBE(const Address& addr);
/** \brief Allocate TBE for L2 replacement*/
  void ir_allocateTBE(const Address& addr);
/** \brief Insert expire event into L2 expire trigger queue*/
  void it_insertL2ExpireTriggerQueue(const Address& addr);
/** \brief Deallocate external TBE*/
  void s_deallocateTBE(const Address& addr);
/** \brief Pop incoming L1 request queue*/
  void jj_popL1RequestQueue(const Address& addr);
/** \brief Pop Incoming Response queue*/
  void o_popIncomingCPUResponseQueue(const Address& addr);
/** \brief Pop Incoming Response queue*/
  void o_popIncomingCPURequestQueue(const Address& addr);
/** \brief Pop L2 Expire Trigger Queue*/
  void o_popL2ExpireTriggerQueue(const Address& addr);
/** \brief Write data from mem response queue to cache*/
  void m_writeDataToCache(const Address& addr);
/** \brief Write data from L1 response queue to cache*/
  void mr_writeDataToCacheFromRequest(const Address& addr);
/** \brief Write data from TBE to cache (for WB stores)*/
  void mt_writeDataToCacheFromTBE(const Address& addr);
/** \brief Record L1 GetS for load response*/
  void ss_recordGetSL1ID(const Address& addr);
/** \brief set the MRU entry*/
  void set_setMRU(const Address& addr);
/** \brief Set L2 cache tag equal to tag of block B.*/
  void qq_allocateL2CacheBlock(const Address& addr);
/** \brief Extend the lifetime of the L2 block according to request*/
  void t_updateL2BlockTime(const Address& addr);
/** \brief Increment the L2 time stamp (on writes)*/
  void ti_incrementL2BlockTime(const Address& addr);
/** \brief Extend the lifetime of the L2 block according to request in TBE*/
  void tt_updateL2BlockTime_fromTBE(const Address& addr);
/** \brief Set the L2 expire time to now (expire it)*/
  void tn_expireL2BlockTime(const Address& addr);
/** \brief Mark block as dirty*/
  void d_markBlockDirty(const Address& addr);
/** \brief Mark block as dirty*/
  void d_markTBEDataReady(const Address& addr);
/** \brief Deallocate L2 cache block.  Sets the cache to not present, allowing a replacement in parallel with a fetch.*/
  void rr_deallocateL2CacheBlock(const Address& addr);
/** \brief Record L1 WB for store response*/
  void xx_recordGetXL1ID(const Address& addr);
/** \brief Update ack count*/
  void q_updateAckCount(const Address& addr);
/** \brief recycle L1 request queue*/
  void zz_recycleL1RequestQueue(const Address& addr);
/** \brief recycle L1 response queue*/
  void zc_recycleL1ResponseNetwork(const Address& addr);
/** \brief stall - i.e. do nothing*/
  void z_stall(const Address& addr);
/** \brief Profile a demand miss for request message*/
  void pM_profileRequestMiss(const Address& addr);
/** \brief Profile a demand hit for request message*/
  void pH_profileRequestHit(const Address& addr);
/** \brief Profile a demand miss for response message*/
  void pM_profileResponseMiss(const Address& addr);
/** \brief Profile a demand hit for response message*/
  void pH_profileResponseHit(const Address& addr);
};
#endif // L2Cache_CONTROLLER_H
