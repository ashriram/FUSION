/** \file MemorySpaceType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "MemorySpaceType.h"

ostream& operator<<(ostream& out, const MemorySpaceType& obj)
{
  out << MemorySpaceType_to_string(obj);
  out << flush;
  return out;
}

string MemorySpaceType_to_string(const MemorySpaceType& obj)
{
  switch(obj) {
  case MemorySpaceType_GLOBAL:
    return "GLOBAL";
  case MemorySpaceType_LOCAL:
    return "LOCAL";
  case MemorySpaceType_NULL:
    return "NULL";
  default:
    ERROR_MSG("Invalid range for type MemorySpaceType");
    return "";
  }
}

MemorySpaceType string_to_MemorySpaceType(const string& str)
{
  if (false) {
  } else if (str == "GLOBAL") {
    return MemorySpaceType_GLOBAL;
  } else if (str == "LOCAL") {
    return MemorySpaceType_LOCAL;
  } else if (str == "NULL") {
    return MemorySpaceType_NULL;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type MemorySpaceType");
  }
}

MemorySpaceType& operator++( MemorySpaceType& e) {
  assert(e < MemorySpaceType_NUM);
  return e = MemorySpaceType(e+1);
}
