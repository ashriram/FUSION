/** \file CoherenceRequestType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "CoherenceRequestType.h"

ostream& operator<<(ostream& out, const CoherenceRequestType& obj)
{
  out << CoherenceRequestType_to_string(obj);
  out << flush;
  return out;
}

string CoherenceRequestType_to_string(const CoherenceRequestType& obj)
{
  switch(obj) {
  case CoherenceRequestType_GETS:
    return "GETS";
  case CoherenceRequestType_GET_INSTR:
    return "GET_INSTR";
  case CoherenceRequestType_DATA_UPGRADE:
    return "DATA_UPGRADE";
  case CoherenceRequestType_DATA:
    return "DATA";
  case CoherenceRequestType_DATA_ATOMIC:
    return "DATA_ATOMIC";
  case CoherenceRequestType_MEMORY_DATA:
    return "MEMORY_DATA";
  case CoherenceRequestType_MEMORY_READ:
    return "MEMORY_READ";
  case CoherenceRequestType_MEMORY_WB:
    return "MEMORY_WB";
  case CoherenceRequestType_GETX:
    return "GETX";
  case CoherenceRequestType_UPGRADE:
    return "UPGRADE";
  case CoherenceRequestType_INV:
    return "INV";
  case CoherenceRequestType_PUTX:
    return "PUTX";
  case CoherenceRequestType_PUTX_ACC:
    return "PUTX_ACC";
  default:
    ERROR_MSG("Invalid range for type CoherenceRequestType");
    return "";
  }
}

CoherenceRequestType string_to_CoherenceRequestType(const string& str)
{
  if (false) {
  } else if (str == "GETS") {
    return CoherenceRequestType_GETS;
  } else if (str == "GET_INSTR") {
    return CoherenceRequestType_GET_INSTR;
  } else if (str == "DATA_UPGRADE") {
    return CoherenceRequestType_DATA_UPGRADE;
  } else if (str == "DATA") {
    return CoherenceRequestType_DATA;
  } else if (str == "DATA_ATOMIC") {
    return CoherenceRequestType_DATA_ATOMIC;
  } else if (str == "MEMORY_DATA") {
    return CoherenceRequestType_MEMORY_DATA;
  } else if (str == "MEMORY_READ") {
    return CoherenceRequestType_MEMORY_READ;
  } else if (str == "MEMORY_WB") {
    return CoherenceRequestType_MEMORY_WB;
  } else if (str == "GETX") {
    return CoherenceRequestType_GETX;
  } else if (str == "UPGRADE") {
    return CoherenceRequestType_UPGRADE;
  } else if (str == "INV") {
    return CoherenceRequestType_INV;
  } else if (str == "PUTX") {
    return CoherenceRequestType_PUTX;
  } else if (str == "PUTX_ACC") {
    return CoherenceRequestType_PUTX_ACC;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type CoherenceRequestType");
  }
}

CoherenceRequestType& operator++( CoherenceRequestType& e) {
  assert(e < CoherenceRequestType_NUM);
  return e = CoherenceRequestType(e+1);
}
