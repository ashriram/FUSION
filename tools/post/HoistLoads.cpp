#include "HoistLoads.h"

void processTrace(unsigned ScratchpadSize)
{
    unsigned loadSize = 0;
    Inst_info *inst = (Inst_info *)malloc(sizeof(Inst_info));    
    while(gzread(OrigTrace, (void*)inst, sizeof(Inst_info)) > 0)
    {
        Inst_info *II = (Inst_info*)malloc(sizeof(Inst_info));
        memcpy((void *)II, (void *)inst, sizeof(Inst_info));

        if(II->acc_heap_load)
        {
            if(LoadInsts.count(II->ld_vaddr1) == 0)
            {
                LoadInsts.insert(make_pair(II->ld_vaddr1,II));
                loadSize += II->mem_read_size; 
            }
        }
        // Other insts including the load insts themselves
        OtherInsts.push_back(II);

        // If ScratchpadSize is exceeded, then drain
        if(loadSize > ScratchpadSize)
        {
            // Write out the load instructions
            for(auto &l : LoadInsts)
            {
                gzwrite(NewTrace, l.second, sizeof(Inst_info));
            }
            LoadInsts.clear();

            // Write out the other instructions 
            for(auto &i : OtherInsts)
            {
                gzwrite(NewTrace, i, sizeof(Inst_info));
                free(i);
            }
            OtherInsts.clear();

            // Add acc_window delim
            Inst_info t;
            t.opcode = TR_NOP;
            t.acc_window_delim = true;
            gzwrite(NewTrace, &t, sizeof(t));

            // Reset load size
            loadSize = 0; 
        }
    }
    free(inst);

    // Drain Remaining insts
    for(auto &l : LoadInsts)
    {
        gzwrite(NewTrace, l.second, sizeof(Inst_info));
    }
    LoadInsts.clear();

    // Write out the other instructions 
    for(auto &i : OtherInsts)
    {
        gzwrite(NewTrace, i, sizeof(Inst_info));
        free(i);
    }
    OtherInsts.clear();

}

int main(int argc, char *argv[])
{
    if(argc != 3)    
    {
        std::cerr << "Usage " << argv[0] << " <Acc Trace File Name> <Scratchpad Size>" << std::endl;
        return 0; 
    }

    OrigTrace = gzopen(argv[1], "rb");
    NewTrace = gzopen((string("seg.")+string(argv[1])).c_str(),"wb");

    if(!OrigTrace || !NewTrace)
    {
        cerr << "Could not open trace files" << endl;
        return 0;
    }

    unsigned ScratchpadSize = 0;
    istringstream(argv[2]) >> ScratchpadSize;

    processTrace(ScratchpadSize);

    gzclose(OrigTrace);
    gzclose(NewTrace);

    return 0;
}
