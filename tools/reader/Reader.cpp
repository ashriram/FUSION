#include "Reader.h"

void processTrace()
{
    Inst_info *t_info = (Inst_info *)malloc(sizeof(Inst_info));    
    while(gzread(OrigTrace, (void*)t_info, sizeof(Inst_info)) > 0)
    {
        (cerr) << "*** begin of the data strcture *** " <<endl;
        (cerr) << "t_info->uop_opcode " <<tr_opcode_names[(uint32_t) t_info->opcode]  << endl;
        (cerr) << "t_info->num_read_regs: " << hex <<  (uint32_t) t_info->num_read_regs << endl;
        (cerr) << "t_info->num_dest_regs: " << hex << (uint32_t) t_info->num_dest_regs << endl;
        //for (UINT32 ii = 0; ii < 4; ++ii) {
            //if (t_info->src[ii] != 0) {
                //(cerr) << "t_info->src" << ii << ": " << LEVEL_BASE::REG_StringShort(static_cast<LEVEL_BASE::REG>(t_info->src[ii])) << endl;
            //}
        //}
        //for (UINT32 ii = 0; ii < 4; ++ii) {
            //if (t_info->dst[ii] != 0) {
                //(cerr) << "t_info->dst" << ii << ": " << hex << LEVEL_BASE::REG_StringShort(static_cast<LEVEL_BASE::REG>(t_info->dst[ii])) << endl;
            //}
        //}
        //(cerr) << "t_info->cf_type: " << hex << tr_cf_names[(uint32_t) t_info->cf_type] << endl;
        (cerr) << "t_info->has_immediate: " << hex << (uint32_t) t_info->has_immediate << endl;
        (cerr) << "t_info->r_dir:" << (uint32_t) t_info->rep_dir << endl;
        (cerr) << "t_info->has_st: " << hex << (uint32_t) t_info->has_st << endl;
        (cerr) << "t_info->num_ld: " << hex << (uint32_t) t_info->num_ld << endl;
        (cerr) << "t_info->mem_read_size: " << hex << (uint32_t) t_info->mem_read_size << endl;
        (cerr) << "t_info->mem_write_size: " << hex << (uint32_t) t_info->mem_write_size << endl;
        (cerr) << "t_info->is_fp: " << (uint32_t) t_info->is_fp << endl;
        (cerr) << "t_info->ld_vaddr1: " << hex << (uint32_t) t_info->ld_vaddr1 << endl;
        (cerr) << "t_info->ld_vaddr2: " << hex << (uint32_t) t_info->ld_vaddr2 << endl;
        (cerr) << "t_info->st_vaddr: " << hex << (uint32_t) t_info->st_vaddr << endl;
        (cerr) << "t_info->instruction_addr: " << hex << (uint32_t) t_info->instruction_addr << endl;
        (cerr) << "t_info->branch_target: " << hex << (uint32_t) t_info->branch_target << endl;
        (cerr) << "t_info->actually_taken: " << hex << (uint32_t) t_info->actually_taken << endl;
        (cerr) << "t_info->write_flg: " << hex << (uint32_t) t_info->write_flg << endl;
        (cerr) << "t_info->acc_id: " << hex << (int32_t) t_info->acc_id << endl;
        (cerr) << "t_info->acc_segment_delim: " << t_info->acc_segment_delim << endl;
        (cerr) << "t_info->acc_heap_load: " << t_info->acc_heap_load << endl;
        (cerr) << "t_info->acc_heap_store: " << t_info->acc_heap_store << endl;
        (cerr) << "t_info->acc_window_delim: " << t_info->acc_window_delim << endl;
        (cerr) << "*** end of the data strcture *** " << endl << endl;

    }

    free(t_info);
}

int main(int argc, char *argv[])
{
    if(argc != 2)    
    {
        std::cerr << "Usage " << argv[0] << " <TraceFileName>" << std::endl;
        return 0; 
    }

    OrigTrace = gzopen(argv[1], "rb");

    if(!OrigTrace)
    {
        cerr << "Could not open trace files" << endl;
        return 0;
    }

    processTrace();

    gzclose(OrigTrace);
    return 0;
}
