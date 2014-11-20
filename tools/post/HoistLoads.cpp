#include "HoistLoads.h"

uint32_t makeCacheAddr(uint32_t addr)
{
    return (addr >> 5) << 5;
}

void processTrace(unsigned ScratchpadSize)
{
    Inst_info *inst = (Inst_info *)malloc(sizeof(Inst_info));    
    while(gzread(OrigTrace, (void*)inst, sizeof(Inst_info)) > 0)
    {
        Inst_info *II = (Inst_info*)malloc(sizeof(Inst_info));
        memcpy((void *)II, (void *)inst, sizeof(Inst_info));

        if(!(II->ld_vaddr1 || II->ld_vaddr2 || II->st_vaddr))
        {
            if(II->is_fp)
                FPIns++;
            else
                INTIns++;
        }
        else
        {
            if(II->is_fp)
                FPMEMIns++;
            else
                INTMEMIns++;
        }

        if(II->acc_heap_load)
        {
            if(LoadInsts.count(makeCacheAddr(II->ld_vaddr1)) == 0)
            {
                LoadInsts.insert(make_pair(makeCacheAddr(II->ld_vaddr1),II));
                CacheBlocks.insert(makeCacheAddr(II->ld_vaddr1));
                DMALoadInsts.insert(make_pair(makeCacheAddr(II->ld_vaddr1),II));
            }
        }

        if(II->acc_heap_store)
        {
            if(DMAStoreInsts.count(makeCacheAddr(II->st_vaddr)) == 0)
            {
                DMAStoreInsts.insert(make_pair(makeCacheAddr(II->st_vaddr),II));
            }
        }

        // Other insts including the load insts themselves
        OtherInsts.push_back(II);

        // If ScratchpadSize is exceeded, then drain
        if(CacheBlocks.size()*32 == ScratchpadSize)
        {
            //cerr << "Load Size: " << loadSize << "\n";
            //cerr << "Cache Size: " << CacheBlocks.size()*32 << "\n";

            // Write out DMALoads
            for(auto &dl : DMALoadInsts)
            {
                gzwrite(DMATrace, dl.second, sizeof(Inst_info));
            }
            cerr << "DMALoad: " << DMALoadInsts.size() << endl;
            DMALoadInsts.clear();

            // Write window delim
            Inst_info delim;
            memset((void *)&delim, 0, sizeof(Inst_info));
            delim.opcode = TR_NOP;
            delim.acc_window_delim = true;
            gzwrite(DMATrace, &delim, sizeof(Inst_info));

            // Write out DMAStores
            for(auto &dl : DMAStoreInsts)
            {
                gzwrite(DMATrace, dl.second, sizeof(Inst_info));
            }
            cerr << "DMAStore: " << DMAStoreInsts.size() << endl;
            DMAStoreInsts.clear();

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
            memset((void*)&t, 0, sizeof(t));
            t.opcode = TR_NOP;
            t.acc_window_delim = true;
            gzwrite(NewTrace, &t, sizeof(t));

            numWindows++;

            // Reset load size
            CacheBlocks.clear();
        }
    }
    free(inst);


    // Write out DMALoads
    for(auto &dl : DMALoadInsts)
    {
        gzwrite(DMATrace, dl.second, sizeof(Inst_info));
    }
    cerr << "DMALoad: " << DMALoadInsts.size() << endl;
    DMALoadInsts.clear();

    // Write window delim
    Inst_info delim;
    memset((void *)&delim, 0, sizeof(Inst_info));
    delim.opcode = TR_NOP;
    delim.acc_window_delim = true;
    gzwrite(DMATrace, &delim, sizeof(Inst_info));

    // Write out DMAStores
    for(auto &dl : DMAStoreInsts)
    {
        gzwrite(DMATrace, dl.second, sizeof(Inst_info));
    }
    cerr << "DMAStore: " << DMAStoreInsts.size() << endl;
    DMAStoreInsts.clear();

    // Write window delim
    memset((void *)&delim, 0, sizeof(Inst_info));
    delim.opcode = TR_NOP;
    delim.acc_window_delim = true;
    gzwrite(DMATrace, &delim, sizeof(Inst_info));

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

    // Segment delimiter should already be present in the OrigTrace
    // as it is added by EndAcc in Pintool.
    
    CacheBlocks.clear();
}

int main(int argc, char *argv[])
{
    if(argc != 2)    
    {
        std::cerr << "Usage " << argv[0] << "<Scratchpad Size>" << std::endl;
        return 0; 
    }

    // Open trace.txt to find out the number of traces

    ifstream traceTxt("trace.txt",ios::in);
    if(!traceTxt.is_open())
    {
        cerr << "Could not open trace.txt\n";
        return 0;
    }

    int numTraces = 0;
    traceTxt >> numTraces;
    traceTxt.close();

    assert(numTraces > 2 && numTraces <= 8 && "Need 1 DMA trace and 6 or less ACC traces");

    //cerr << "numTraces: " << numTraces << "\n";

    DMATrace = gzopen("trace_1.raw","wb");
    if(!DMATrace)
    {
        cerr << "Could not open trace file (trace_1.raw) for DMA Trace\n";
        return 0;
    }

    for(int i = 2; i < numTraces; i++)
    {
        string OrigFilename = string("trace_") + to_string(i) + string(".raw");
        OrigTrace = gzopen(OrigFilename.c_str(), "rb");
        string NewFilename = string("new.trace_") + to_string(i) + string(".raw");
        NewTrace = gzopen(NewFilename.c_str(),"wb");

        if(!OrigTrace || !NewTrace)
        {
            cerr << "Could not open trace files" << endl;
            return 0;
        }

        unsigned ScratchpadSize = 0;
        istringstream(argv[1]) >> ScratchpadSize;

        assert(ScratchpadSize % 32 == 0 && "ScratchpadSize should be a multiple of 32");

        cerr << " Core " << i << endl;

        processTrace(ScratchpadSize);

        cerr << "Core " << i << " W: " << numWindows+1 << " INT: " << INTIns << " FP: " << FPIns  << " FPMEM: " << FPMEMIns << " INTMEM: " << INTMEMIns << endl;

        INTIns = 0;
        FPIns = 0;
        FPMEMIns = 0;
        INTMEMIns = 0;
        numWindows = 0;

        gzclose(OrigTrace);
        gzclose(NewTrace);

        string OldFilename = string("orig.") + OrigFilename;
        system((string("mv ")+OrigFilename+string(" ")+OldFilename).c_str());
        system((string("mv ")+NewFilename+string(" ")+OrigFilename).c_str());
    }

    gzclose(DMATrace);
    return 0;
}
