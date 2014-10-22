/** \file CoherenceRequestType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef CoherenceRequestType_H
#define CoherenceRequestType_H

#include "Global.h"

/** \enum CoherenceRequestType
  * \brief ...
  */
enum CoherenceRequestType {
  CoherenceRequestType_FIRST,
  CoherenceRequestType_GETS = CoherenceRequestType_FIRST,  /**< Get Shared */
  CoherenceRequestType_GET_INSTR,  /**< Get Instruction */
  CoherenceRequestType_DATA_UPGRADE,  /**< Write Data from L1, but L1 is also holding onto a valid copy */
  CoherenceRequestType_DATA,  /**< Data from L2 on a read */
  CoherenceRequestType_DATA_ATOMIC,  /**< Data and request/response for Atomic */
  CoherenceRequestType_MEMORY_DATA,  /**< Data */
  CoherenceRequestType_MEMORY_READ,  /**< Read Memory */
  CoherenceRequestType_MEMORY_WB,  /**< Coherence Type for writing data on memory port */
  CoherenceRequestType_GETX,  /**< Get eXclusive */
  CoherenceRequestType_UPGRADE,  /**< UPGRADE to exclusive */
  CoherenceRequestType_INV,  /**< INValidate */
  CoherenceRequestType_PUTX,  /**< replacement message */
  CoherenceRequestType_PUTX_ACC,  /**< Clean writeback from Accelerator */
  CoherenceRequestType_NUM
};
CoherenceRequestType string_to_CoherenceRequestType(const string& str);
string CoherenceRequestType_to_string(const CoherenceRequestType& obj);
CoherenceRequestType &operator++( CoherenceRequestType &e);
ostream& operator<<(ostream& out, const CoherenceRequestType& obj);

#endif // CoherenceRequestType_H
