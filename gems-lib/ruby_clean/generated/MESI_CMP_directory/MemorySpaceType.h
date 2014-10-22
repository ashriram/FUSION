/** \file MemorySpaceType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef MemorySpaceType_H
#define MemorySpaceType_H

#include "Global.h"

/** \enum MemorySpaceType
  * \brief ...
  */
enum MemorySpaceType {
  MemorySpaceType_FIRST,
  MemorySpaceType_GLOBAL = MemorySpaceType_FIRST,  /**< Global memory space */
  MemorySpaceType_LOCAL,  /**< Local memory space */
  MemorySpaceType_NULL,  /**< null space type */
  MemorySpaceType_NUM
};
MemorySpaceType string_to_MemorySpaceType(const string& str);
string MemorySpaceType_to_string(const MemorySpaceType& obj);
MemorySpaceType &operator++( MemorySpaceType &e);
ostream& operator<<(ostream& out, const MemorySpaceType& obj);

#endif // MemorySpaceType_H
