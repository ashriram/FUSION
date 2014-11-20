#include <iostream>
#include <zlib.h>
#include <string>
#include <cstdlib>
#include "xed-category-enum.h"
#include <cstring>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <cassert>
#include <set>

#define MAX_SRC_NUM 9
#define MAX_DST_NUM 6

using namespace std;

gzFile OrigTraces[8];
gzFile NewTrace[8];

struct Inst_info {
    uint8_t num_read_regs;      // 3-bits
    uint8_t num_dest_regs;      // 3-bits
    uint8_t src[MAX_SRC_NUM]; // 6-bits * 4
    uint8_t dst[MAX_DST_NUM]; // 6-bits * 4
    uint8_t cf_type;  // 4 bits
    bool has_immediate;  // 1bits
    uint8_t opcode; // 6 bits
    bool  has_st;  // 1 bit
    bool is_fp;    // 1bit
    bool write_flg;   // 1bit
    uint8_t num_ld;  // 2bit
    uint8_t size; // 5 bit
    // **** dynamic ****
    uint32_t ld_vaddr1; // 4 bytes
    uint32_t ld_vaddr2; // 4 bytes
    uint32_t st_vaddr;   // 4 bytes
    uint32_t instruction_addr; // 4 bytes
    uint32_t branch_target; // not the dynamic info. static info  // 4 bytes
    uint8_t mem_read_size; // 8 bit
    uint8_t mem_write_size;  // 8 bit
    bool rep_dir;  // 1 bit
    bool actually_taken; // 1 bit
    /** ds-acc specific start **/
#include "common-trace-fields.cpp"
    /** ds-acc specific end **/
} Inst;

map<uint32_t, Inst_info*> LoadInsts;
vector<Inst_info *> OtherInsts;
set<uint32_t> CacheBlocks;

map<uint32_t, Inst_info*> DMALoadInsts;
map<uint32_t, Inst_info*> DMAStoreInsts;

unsigned long long INTIns = 0;
unsigned long long FPIns = 0;
unsigned long long FPMEMIns = 0;
unsigned long long INTMEMIns = 0;
unsigned long long numWindows = 0;
unsigned long long numSegments = 0;
unsigned long long DMAdelim = 0;

enum TR_OPCODE_enum {
  TR_MUL = XED_CATEGORY_LAST ,
  TR_DIV,
  TR_FMUL,
  TR_FDIV,
  TR_NOP,
  PREFETCH_NTA,
  PREFETCH_T0,
  PREFETCH_T1,
  PREFETCH_T2,
}TR_OPCODE;

