/** \file L1Cache.h
  * 
  * Auto generated C++ code started by symbols/StateMachine.C:252
  * Created by slicc definition of Module "Cache Leasing v2 L1 Cache CMP"
  */

#ifndef L1Cache_CONTROLLER_H
#define L1Cache_CONTROLLER_H

#include "Global.h"
#include "Consumer.h"
#include "TransitionResult.h"
#include "Types.h"
#include "L1Cache_Profiler.h"

extern stringstream L1Cache_transitionComment;
class L1Cache_Controller : public Consumer {
#ifdef CHECK_COHERENCE
  friend class Chip;
#endif /* CHECK_COHERENCE */
public:
  L1Cache_Controller(Chip* chip_ptr, int version);
  void print(ostream& out) const;
  void wakeup();
  static void dumpStats(ostream& out) { s_profiler.dumpStats(out); }
  static void clearStats() { s_profiler.clearStats(); }
private:
  TransitionResult doTransition(L1Cache_Event event, L1Cache_State state, const Address& addr);  // in L1Cache_Transitions.C
  TransitionResult doTransitionWorker(L1Cache_Event event, L1Cache_State state, L1Cache_State& next_state, const Address& addr);  // in L1Cache_Transitions.C
  Chip* m_chip_ptr;
  NodeID m_id;
  NodeID m_version;
  MachineID m_machineID;
  static L1Cache_Profiler s_profiler;
  // Internal functions
  L1Cache_Entry& L1Cache_getL1CacheEntry(Address param_addr);
  void L1Cache_changeL1Permission(Address param_addr, AccessPermission param_permission);
  Time L1Cache_getDelta_Access(Address param_addr);
  bool L1Cache_isL1CacheTagPresent(Address param_addr);
  bool L1Cache_isLive(Address param_addr);
  void L1Cache_setState(Address param_addr, L1Cache_State param_state);
  L1Cache_State L1Cache_getState(Address param_addr);
  L1Cache_Event L1Cache_mandatory_request_type_to_event(CacheRequestType param_type);
  bool L1Cache_is_write(CacheRequestType param_type);
  Address L1Cache_getDummyAddress();
  int L1Cache_get_pending_reads(Address param_addr);
  int L1Cache_get_pending_writes(Address param_addr);
  // Actions
/** \brief Issue GETS*/
  void a_issueGETS(const Address& addr);
/** \brief send upgrade to the L2 cache*/
  void u_sendUpgradeToL2(const Address& addr);
/** \brief send data to the L2 cache from TBE*/
  void d2t_sendDataToL2_fromTBE(const Address& addr);
/** \brief send Atomic data to the L2 cache from TBE*/
  void d2t_sendAtomicDataToL2_fromTBE(const Address& addr);
/** \brief If not prefetch, notify sequencer the load completed.*/
  void h_load_hit(const Address& addr);
/** \brief If not prefetch, notify sequencer that store completed.*/
  void hh_store_hit(const Address& addr);
/** \brief Allocate TBE*/
  void i_allocateTBE(const Address& addr);
/** \brief Allocate TBE with lifetime from Cache*/
  void i_allocateTBEwTime(const Address& addr);
/** \brief Pop mandatory queue.*/
  void k_popMandatoryQueue(const Address& addr);
/** \brief Pop Incoming Response queue and profile the delay within this virtual network*/
  void o_popIncomingResponseQueue(const Address& addr);
/** \brief Deallocate TBE*/
  void s_deallocateTBE(const Address& addr);
/** \brief Update L1 block's lifetime from reponse msg*/
  void t_updateL1Lifetime(const Address& addr);
/** \brief Write data to cache from L2 response queue*/
  void dd_writeDataToL1Cache(const Address& addr);
/** \brief Write data to cache from TBE*/
  void dt_writeDataToL1CacheFromTBE(const Address& addr);
/** \brief Deallocate L1 cache block.  Sets the cache to not present, allowing a replacement in parallel with a fetch.*/
  void ff_deallocateL1CacheBlock(const Address& addr);
/** \brief Set L1 D-cache tag equal to tag of block B.*/
  void oo_allocateL1DCacheBlock(const Address& addr);
/** \brief recycle L1 request queue*/
  void z_recycleMandatoryQueue(const Address& addr);
/** \brief stall - i.e. do nothing*/
  void z_stall(const Address& addr);
/** \brief Profile a demand miss*/
  void pM_profileMiss(const Address& addr);
/** \brief Profile a demand hit*/
  void pH_profileHit(const Address& addr);
/** \brief Increment pending read count*/
  void pr_incPendingRead(const Address& addr);
/** \brief Increment pending write count*/
  void pw_incPendingWrite(const Address& addr);
/** \brief Decrement pending read count*/
  void pr_decPendingRead(const Address& addr);
/** \brief Decrement pending write count*/
  void pw_decPendingWrite(const Address& addr);
};
#endif // L1Cache_CONTROLLER_H
