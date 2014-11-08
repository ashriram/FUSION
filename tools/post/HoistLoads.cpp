#include "HoistLoads.h"

void processTrace(int ScratchpadSize)
{
    unsigned loadSize = 0;
    while(gzread(OrigTrace, (void*)&inst, sizeof(Inst_info)) > 0)
    {
        Inst_info *II = new Inst_info;
        memcpy((void *)II, (void *)&inst, sizeof(Inst_info));

        if(II->acc_heap_load)
        {
            loadSize += II->mem_read_size; 
            if(LoadInsts.count(II->ld_vaddr1))
                LoadInsts.insert(make_pair(II->ld_vaddr1,II));
        }
        else
        {
            OtherInsts.push_back(II);
        }

        // If ScratchpadSize is exceeded, then drain
        if(loadSize > ScratchpadSize)
        {
            // Write out the load instructions
            for(auto l : LoadInsts)
            {
                gzwrite(NewTrace, l.second, sizeof(Inst_info));
                delete l.second;
            }
            LoadInsts.clear();

            // Write out the other instructions 
            for(auto i : OtherInsts)
            {
                gzwrite(NewTrace, i, sizeof(Inst_info));
                delete i;
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

    // Drain Remaining insts
    // Write out the load instructions
    for(auto l : LoadInsts)
    {
        gzwrite(NewTrace, l.second, sizeof(Inst_info));
        delete l.second;
    }
    LoadInsts.clear();

    // Write out the other instructions 
    for(auto i : OtherInsts)
    {
        gzwrite(NewTrace, i, sizeof(Inst_info));
        delete i;
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
    NewTrace = gzopen((string(argv[1])+string(".new")).c_str(),"wb");

    if(!OrigTrace || !NewTrace)
    {
        cerr << "Could not open trace files" << endl;
        return 0;
    }

    gzclose(OrigTrace);
    gzclose(NewTrace);

    return 0;
}
