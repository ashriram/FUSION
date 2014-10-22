/** \file L2Cache_State.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef L2Cache_State_H
#define L2Cache_State_H

#include "Global.h"

/** \enum L2Cache_State
  * \brief L2 Cache states
  */
enum L2Cache_State {
  L2Cache_State_FIRST,
  L2Cache_State_NP = L2Cache_State_FIRST,  /**< Not present in cache */
  L2Cache_State_E,  /**< L2 cache entry valid but with expired timestamp */
  L2Cache_State_S,  /**< L2 cache entry valid with single sharer */
  L2Cache_State_SS,  /**< L2 cache entry valid with possibly multiple sharers, but at least one */
  L2Cache_State_IS,  /**< L2 idle, got L1_GETS, issued memory fetch, have not seen response yet */
  L2Cache_State_ISS,  /**< L2 idle, got L1_GETS, issued memory fetch, and then saw another GETS */
  L2Cache_State_IM,  /**< L2 idle, got L1 Write, issued memory fetch, have not seen response(s) yet */
  L2Cache_State_IMA,  /**< L2 idle, got Atomic, issued memory fetch, have not seen response(s) yet */
  L2Cache_State_MI,  /**< L2 replacement on valid timestamp, waiting for expire event */
  L2Cache_State_MI_Ack,  /**< Send writeback to CPU; waiting on ack */
  L2Cache_State_NUM
};
L2Cache_State string_to_L2Cache_State(const string& str);
string L2Cache_State_to_string(const L2Cache_State& obj);
L2Cache_State &operator++( L2Cache_State &e);
ostream& operator<<(ostream& out, const L2Cache_State& obj);

#endif // L2Cache_State_H
