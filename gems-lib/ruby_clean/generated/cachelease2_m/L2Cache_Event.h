/** \file L2Cache_Event.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef L2Cache_Event_H
#define L2Cache_Event_H

#include "Global.h"

/** \enum L2Cache_Event
  * \brief L2 Cache events
  */
enum L2Cache_Event {
  L2Cache_Event_FIRST,
  L2Cache_Event_L1_GETS = L2Cache_Event_FIRST,  /**< a L1D GETS request for a block maped to us */
  L2Cache_Event_L1_Write,  /**< data from L1 due to a write miss in L1 */
  L2Cache_Event_L1_Upgrade_T,  /**< data from L1 due to a write hit in L1. Timestamps between L1 and L2 match. */
  L2Cache_Event_L1_Upgrade_NT,  /**< data from L1 due to a write hit in L1. Timestamps between L1 and L2 do not match. */
  L2Cache_Event_L2_Atomic,  /**< Atomic request and data from L1 */
  L2Cache_Event_L2_Expire,  /**< L2 block lifetime expired */
  L2Cache_Event_L2_Replacement,  /**< L2 Replacement */
  L2Cache_Event_L2_Replacement_clean,  /**< L2 Replacement, but data is clean */
  L2Cache_Event_Data,  /**< data from CPU, not seen all Acks yet */
  L2Cache_Event_Data_all_Acks,  /**< data from CPU, seen all acks */
  L2Cache_Event_Ack,  /**< Not seen all acks yet; possibly seen data */
  L2Cache_Event_Ack_all,  /**< Seen all acks and already seen data */
  L2Cache_Event_WB_Ack,  /**< Write back ack */
  L2Cache_Event_Fwd_GETX,  /**< We send data back to L2 with original requestor ID. Only one outstanding to Accelerator protocol from CPU Side */
  L2Cache_Event_Fwd_GETS,  /**< We send data back to L2 with original requestor ID. Only one outstanding to Accelerator protocol from CPU Side */
  L2Cache_Event_Inv,  /**< We send data back to L2 with original requestor ID. Only one outstanding to Accelerator protocol from CPU Side */
  L2Cache_Event_NUM
};
L2Cache_Event string_to_L2Cache_Event(const string& str);
string L2Cache_Event_to_string(const L2Cache_Event& obj);
L2Cache_Event &operator++( L2Cache_Event &e);
ostream& operator<<(ostream& out, const L2Cache_Event& obj);

#endif // L2Cache_Event_H
