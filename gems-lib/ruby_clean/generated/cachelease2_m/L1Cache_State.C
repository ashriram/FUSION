/** \file L1Cache_State.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "L1Cache_State.h"

ostream& operator<<(ostream& out, const L1Cache_State& obj)
{
  out << L1Cache_State_to_string(obj);
  out << flush;
  return out;
}

string L1Cache_State_to_string(const L1Cache_State& obj)
{
  switch(obj) {
  case L1Cache_State_I:
    return "I";
  case L1Cache_State_S:
    return "S";
  case L1Cache_State_I_S:
    return "I_S";
  case L1Cache_State_I_I:
    return "I_I";
  case L1Cache_State_SM:
    return "SM";
  default:
    ERROR_MSG("Invalid range for type L1Cache_State");
    return "";
  }
}

L1Cache_State string_to_L1Cache_State(const string& str)
{
  if (false) {
  } else if (str == "I") {
    return L1Cache_State_I;
  } else if (str == "S") {
    return L1Cache_State_S;
  } else if (str == "I_S") {
    return L1Cache_State_I_S;
  } else if (str == "I_I") {
    return L1Cache_State_I_I;
  } else if (str == "SM") {
    return L1Cache_State_SM;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type L1Cache_State");
  }
}

L1Cache_State& operator++( L1Cache_State& e) {
  assert(e < L1Cache_State_NUM);
  return e = L1Cache_State(e+1);
}
