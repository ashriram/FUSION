/*
Copyright (c) <2012>, <Georgia Institute of Technology> All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted
provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions
and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or other materials provided
with the distribution.

Neither the name of the <Georgia Institue of Technology> nor the names of its contributors
may be used to endorse or promote products derived from this software without specific prior
written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/


/**********************************************************************************************
 * File         : global_types.h
 * Author       : HPArch
 * Date         : 12/16/2007
 * CVS          : $Id: global_types.h,v 1.1 2008-02-22 22:51:06 hyesoon Exp $:
 * Description  : Global type declarations intended to be included in every source file.
 *********************************************************************************************/

#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include <cstdint>


// Renames
// Try to use these rather than built-in C types in order to preserve portability
typedef unsigned           uns;
typedef unsigned char      uns8;
typedef unsigned short     uns16;
typedef unsigned           uns32;
typedef unsigned long long uns64;
typedef char               int8;
typedef short              int16;
typedef int                int32;
typedef int long long      int64;
typedef int                Generic_Enum;
typedef uns64              Counter;
typedef int64              Quad;
typedef uns64              UQuad;

/* power & hotleakage  */  /* please CHECKME Hyesoon 6-15-2009 */
typedef uns64 tick_t;
typedef uns64 counter_t;

/* Conventions */
typedef uns64 Addr;
typedef uns32 Binary;


///////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Core type (for heterogeneous simulation)
///////////////////////////////////////////////////////////////////////////////////////////////
typedef enum _Unit_Type_enum
    {
        UNIT_SMALL = 0, /**< small core */
        UNIT_MEDIUM, /**< medium core */
        UNIT_LARGE, /**< large core */
        UNIT_ACC  /**< accelerator core */
    } Unit_Type;

// Global types for Data Structure Acceleration

enum Walker_Type
{
    WALK_VEC = 0,
    WALK_HASH,
    WALK_BTREE
};

enum Acc_Msg_Type
{
    PE_IMB_LOAD_REQ = 0,
    IMB_PE_LOAD_DONE,
    PE_IMB_STORE_REQ,
    IMB_PE_STORE_DONE,
    IMB_WALKER_LOAD_REQ,
    IMB_WALKER_STORE_REQ,
    WALKER_IMB_LOAD_DONE,
    WALKER_IMB_STORE_DONE,
    HASH_SEARCH_REQ,
    HASH_SEARCH_DONE,
    BTREE_TRAVERSE_REQ,
    BTREE_TRAVERSE_DONE
};

enum PE_Status
{
    PE_LOAD = 0,
    PE_COMPUTE,
    PE_STORE,
    PE_INACTIVE,
    PE_STALL
};

enum Walker_Status
{
    WALKER_LOADING = 0,
    WALKER_LOAD_WAIT,
    WALKER_STORING,
    WALKER_READY,
    WALKER_HASH_SEARCH,
    WALKER_BTREE_TRAVERSE
};

enum Walker_MSHR_Entry_Status
{
    MSHR_ENTRY_INVALID = 0,
    MSHR_ENTRY_READY,
    MSHR_ENTRY_ISSUED,
    MSHR_ENTRY_DONE
};

static const uint64_t WORK_PRIO_NORMAL=20;

// Used for the hash search
struct md5_value{
    uint32_t _32[4];
};


#endif
