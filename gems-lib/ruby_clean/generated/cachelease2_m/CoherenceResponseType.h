/** \file CoherenceResponseType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef CoherenceResponseType_H
#define CoherenceResponseType_H

#include "Global.h"

/** \enum CoherenceResponseType
  * \brief ...
  */
enum CoherenceResponseType {
  CoherenceResponseType_FIRST,
  CoherenceResponseType_MEMORY_ACK = CoherenceResponseType_FIRST,  /**< Ack from memory controller */
  CoherenceResponseType_DATA,  /**< Data from L2 on a read */
  CoherenceResponseType_DATA_ATOMIC,  /**< Data and request/response for Atomic */
  CoherenceResponseType_ACK,  /**< Write ack from L2, write globally committed */
  CoherenceResponseType_MEMORY_DATA,  /**< Data */
  CoherenceResponseType_DATA_EXCLUSIVE,  /**< Data */
  CoherenceResponseType_WB_ACK,  /**< writeback ack */
  CoherenceResponseType_UNBLOCK,  /**< unblock */
  CoherenceResponseType_EXCLUSIVE_UNBLOCK,  /**< exclusive unblock */
  CoherenceResponseType_DATA_ACC,  /**< Writeback data from Accelerator */
  CoherenceResponseType_NUM
};
CoherenceResponseType string_to_CoherenceResponseType(const string& str);
string CoherenceResponseType_to_string(const CoherenceResponseType& obj);
CoherenceResponseType &operator++( CoherenceResponseType &e);
ostream& operator<<(ostream& out, const CoherenceResponseType& obj);

#endif // CoherenceResponseType_H
