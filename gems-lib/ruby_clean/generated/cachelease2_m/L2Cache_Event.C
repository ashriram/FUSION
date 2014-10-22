/** \file L2Cache_Event.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "L2Cache_Event.h"

ostream& operator<<(ostream& out, const L2Cache_Event& obj)
{
  out << L2Cache_Event_to_string(obj);
  out << flush;
  return out;
}

string L2Cache_Event_to_string(const L2Cache_Event& obj)
{
  switch(obj) {
  case L2Cache_Event_L1_GETS:
    return "L1_GETS";
  case L2Cache_Event_L1_Write:
    return "L1_Write";
  case L2Cache_Event_L1_Upgrade_T:
    return "L1_Upgrade_T";
  case L2Cache_Event_L1_Upgrade_NT:
    return "L1_Upgrade_NT";
  case L2Cache_Event_L2_Atomic:
    return "L2_Atomic";
  case L2Cache_Event_L2_Expire:
    return "L2_Expire";
  case L2Cache_Event_L2_Replacement:
    return "L2_Replacement";
  case L2Cache_Event_L2_Replacement_clean:
    return "L2_Replacement_clean";
  case L2Cache_Event_Data:
    return "Data";
  case L2Cache_Event_Data_all_Acks:
    return "Data_all_Acks";
  case L2Cache_Event_Ack:
    return "Ack";
  case L2Cache_Event_Ack_all:
    return "Ack_all";
  case L2Cache_Event_WB_Ack:
    return "WB_Ack";
  case L2Cache_Event_Fwd_GETX:
    return "Fwd_GETX";
  case L2Cache_Event_Fwd_GETS:
    return "Fwd_GETS";
  case L2Cache_Event_Inv:
    return "Inv";
  default:
    ERROR_MSG("Invalid range for type L2Cache_Event");
    return "";
  }
}

L2Cache_Event string_to_L2Cache_Event(const string& str)
{
  if (false) {
  } else if (str == "L1_GETS") {
    return L2Cache_Event_L1_GETS;
  } else if (str == "L1_Write") {
    return L2Cache_Event_L1_Write;
  } else if (str == "L1_Upgrade_T") {
    return L2Cache_Event_L1_Upgrade_T;
  } else if (str == "L1_Upgrade_NT") {
    return L2Cache_Event_L1_Upgrade_NT;
  } else if (str == "L2_Atomic") {
    return L2Cache_Event_L2_Atomic;
  } else if (str == "L2_Expire") {
    return L2Cache_Event_L2_Expire;
  } else if (str == "L2_Replacement") {
    return L2Cache_Event_L2_Replacement;
  } else if (str == "L2_Replacement_clean") {
    return L2Cache_Event_L2_Replacement_clean;
  } else if (str == "Data") {
    return L2Cache_Event_Data;
  } else if (str == "Data_all_Acks") {
    return L2Cache_Event_Data_all_Acks;
  } else if (str == "Ack") {
    return L2Cache_Event_Ack;
  } else if (str == "Ack_all") {
    return L2Cache_Event_Ack_all;
  } else if (str == "WB_Ack") {
    return L2Cache_Event_WB_Ack;
  } else if (str == "Fwd_GETX") {
    return L2Cache_Event_Fwd_GETX;
  } else if (str == "Fwd_GETS") {
    return L2Cache_Event_Fwd_GETS;
  } else if (str == "Inv") {
    return L2Cache_Event_Inv;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type L2Cache_Event");
  }
}

L2Cache_Event& operator++( L2Cache_Event& e) {
  assert(e < L2Cache_Event_NUM);
  return e = L2Cache_Event(e+1);
}
