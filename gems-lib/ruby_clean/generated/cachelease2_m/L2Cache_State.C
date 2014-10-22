/** \file L2Cache_State.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "L2Cache_State.h"

ostream& operator<<(ostream& out, const L2Cache_State& obj)
{
  out << L2Cache_State_to_string(obj);
  out << flush;
  return out;
}

string L2Cache_State_to_string(const L2Cache_State& obj)
{
  switch(obj) {
  case L2Cache_State_NP:
    return "NP";
  case L2Cache_State_E:
    return "E";
  case L2Cache_State_S:
    return "S";
  case L2Cache_State_SS:
    return "SS";
  case L2Cache_State_IS:
    return "IS";
  case L2Cache_State_ISS:
    return "ISS";
  case L2Cache_State_IM:
    return "IM";
  case L2Cache_State_IMA:
    return "IMA";
  case L2Cache_State_MI:
    return "MI";
  case L2Cache_State_MI_Ack:
    return "MI_Ack";
  default:
    ERROR_MSG("Invalid range for type L2Cache_State");
    return "";
  }
}

L2Cache_State string_to_L2Cache_State(const string& str)
{
  if (false) {
  } else if (str == "NP") {
    return L2Cache_State_NP;
  } else if (str == "E") {
    return L2Cache_State_E;
  } else if (str == "S") {
    return L2Cache_State_S;
  } else if (str == "SS") {
    return L2Cache_State_SS;
  } else if (str == "IS") {
    return L2Cache_State_IS;
  } else if (str == "ISS") {
    return L2Cache_State_ISS;
  } else if (str == "IM") {
    return L2Cache_State_IM;
  } else if (str == "IMA") {
    return L2Cache_State_IMA;
  } else if (str == "MI") {
    return L2Cache_State_MI;
  } else if (str == "MI_Ack") {
    return L2Cache_State_MI_Ack;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type L2Cache_State");
  }
}

L2Cache_State& operator++( L2Cache_State& e) {
  assert(e < L2Cache_State_NUM);
  return e = L2Cache_State(e+1);
}
