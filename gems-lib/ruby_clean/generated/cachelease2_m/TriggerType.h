/** \file TriggerType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef TriggerType_H
#define TriggerType_H

#include "Global.h"

/** \enum TriggerType
  * \brief ...
  */
enum TriggerType {
  TriggerType_FIRST,
  TriggerType_FENCE = TriggerType_FIRST,  /**< When all writes have performed globally */
  TriggerType_NUM
};
TriggerType string_to_TriggerType(const string& str);
string TriggerType_to_string(const TriggerType& obj);
TriggerType &operator++( TriggerType &e);
ostream& operator<<(ostream& out, const TriggerType& obj);

#endif // TriggerType_H
