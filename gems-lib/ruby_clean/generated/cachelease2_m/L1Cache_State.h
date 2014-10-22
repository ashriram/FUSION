/** \file L1Cache_State.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef L1Cache_State_H
#define L1Cache_State_H

#include "Global.h"

/** \enum L1Cache_State
  * \brief Cache states
  */
enum L1Cache_State {
  L1Cache_State_FIRST,
  L1Cache_State_I = L1Cache_State_FIRST,  /**< a L1 cache entry Idle */
  L1Cache_State_S,  /**< a L1 cache entry Valid */
  L1Cache_State_I_S,  /**< L1 idle, issued GETS , have not seen response yet */
  L1Cache_State_I_I,  /**< Issued at least one write, go to I when all requests are done */
  L1Cache_State_SM,  /**< Write Upgrade sent, have not seen Data or Ack yet */
  L1Cache_State_NUM
};
L1Cache_State string_to_L1Cache_State(const string& str);
string L1Cache_State_to_string(const L1Cache_State& obj);
L1Cache_State &operator++( L1Cache_State &e);
ostream& operator<<(ostream& out, const L1Cache_State& obj);

#endif // L1Cache_State_H
