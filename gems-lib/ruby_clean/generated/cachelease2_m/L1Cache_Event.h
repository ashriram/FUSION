/** \file L1Cache_Event.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef L1Cache_Event_H
#define L1Cache_Event_H

#include "Global.h"

/** \enum L1Cache_Event
  * \brief Cache events
  */
enum L1Cache_Event {
  L1Cache_Event_FIRST,
  L1Cache_Event_Load = L1Cache_Event_FIRST,  /**< Load request from the home processor */
  L1Cache_Event_L1_WThru,  /**< Store request from the home processor */
  L1Cache_Event_L1_Atomic,  /**< Atomic request from the home processor */
  L1Cache_Event_L1_Replacement,  /**< L1 Replacement */
  L1Cache_Event_Data,  /**< Data response for load request. Still stores outstanding */
  L1Cache_Event_Data_Done,  /**< Data response for load request and all outstanding accesses are done */
  L1Cache_Event_Ack,  /**< Ack for write request. Still requests outstanding */
  L1Cache_Event_Ack_Done,  /**< Ack for write request and all outstanding accesses are done */
  L1Cache_Event_DataAtomic,  /**< Atomic Data for processor. Still requests outstanding */
  L1Cache_Event_DataAtomic_Done,  /**< Atomic Data for processor and all outstanding requests are done */
  L1Cache_Event_NUM
};
L1Cache_Event string_to_L1Cache_Event(const string& str);
string L1Cache_Event_to_string(const L1Cache_Event& obj);
L1Cache_Event &operator++( L1Cache_Event &e);
ostream& operator<<(ostream& out, const L1Cache_Event& obj);

#endif // L1Cache_Event_H
