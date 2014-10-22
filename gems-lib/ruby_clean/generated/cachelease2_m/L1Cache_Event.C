/** \file L1Cache_Event.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "L1Cache_Event.h"

ostream& operator<<(ostream& out, const L1Cache_Event& obj)
{
  out << L1Cache_Event_to_string(obj);
  out << flush;
  return out;
}

string L1Cache_Event_to_string(const L1Cache_Event& obj)
{
  switch(obj) {
  case L1Cache_Event_Load:
    return "Load";
  case L1Cache_Event_L1_WThru:
    return "L1_WThru";
  case L1Cache_Event_L1_Atomic:
    return "L1_Atomic";
  case L1Cache_Event_L1_Replacement:
    return "L1_Replacement";
  case L1Cache_Event_Data:
    return "Data";
  case L1Cache_Event_Data_Done:
    return "Data_Done";
  case L1Cache_Event_Ack:
    return "Ack";
  case L1Cache_Event_Ack_Done:
    return "Ack_Done";
  case L1Cache_Event_DataAtomic:
    return "DataAtomic";
  case L1Cache_Event_DataAtomic_Done:
    return "DataAtomic_Done";
  default:
    ERROR_MSG("Invalid range for type L1Cache_Event");
    return "";
  }
}

L1Cache_Event string_to_L1Cache_Event(const string& str)
{
  if (false) {
  } else if (str == "Load") {
    return L1Cache_Event_Load;
  } else if (str == "L1_WThru") {
    return L1Cache_Event_L1_WThru;
  } else if (str == "L1_Atomic") {
    return L1Cache_Event_L1_Atomic;
  } else if (str == "L1_Replacement") {
    return L1Cache_Event_L1_Replacement;
  } else if (str == "Data") {
    return L1Cache_Event_Data;
  } else if (str == "Data_Done") {
    return L1Cache_Event_Data_Done;
  } else if (str == "Ack") {
    return L1Cache_Event_Ack;
  } else if (str == "Ack_Done") {
    return L1Cache_Event_Ack_Done;
  } else if (str == "DataAtomic") {
    return L1Cache_Event_DataAtomic;
  } else if (str == "DataAtomic_Done") {
    return L1Cache_Event_DataAtomic_Done;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type L1Cache_Event");
  }
}

L1Cache_Event& operator++( L1Cache_Event& e) {
  assert(e < L1Cache_Event_NUM);
  return e = L1Cache_Event(e+1);
}
