#include "HoistLoads.h"

uint32_t makeCacheAddr(uint32_t addr)
{
    return (addr >> 5) << 5;
}

unsigned processTrace(unsigned ScratchpadSize, int acc_id)
{
    assert(acc_id > 1 && acc_id < 8 && "Invalid ACC_ID");
    cerr << "Processing ACC " << acc_id << " Segment " << SegmentCounter[acc_id] << endl;
    Inst_info *inst = (Inst_info *)malloc(sizeof(Inst_info));    
    bool SegDrain = false;
    unsigned writeCount = 0;
    while(gzread(OrigTrace[acc_id], (void*)inst, sizeof(Inst_info)) > 0 && !SegDrain)
    {
        Inst_info *II = (Inst_info*)malloc(sizeof(Inst_info));
        memcpy((void *)II, (void *)inst, sizeof(Inst_info));

        if(II->acc_heap_load)
        {
            if(LoadInsts.count(makeCacheAddr(II->ld_vaddr1)) == 0)
            {
                LoadInsts.insert(make_pair(makeCacheAddr(II->ld_vaddr1),II));
                CacheBlocks.insert(makeCacheAddr(II->ld_vaddr1));
                DMALoadInsts.insert(make_pair(makeCacheAddr(II->ld_vaddr1),II));
                assert(II->acc_segment_delim == 0 && "LD should not have acc_segment_delim flag");
            }
            else if(LoadInsts.count(makeCacheAddr(II->ld_vaddr2)) == 0)
            {
                LoadInsts.insert(make_pair(makeCacheAddr(II->ld_vaddr2),II));
                CacheBlocks.insert(makeCacheAddr(II->ld_vaddr2));
                DMALoadInsts.insert(make_pair(makeCacheAddr(II->ld_vaddr2),II));
                assert(II->acc_segment_delim == 0 && "LD should not have acc_segment_delim flag");
            }

        }

        if(II->acc_heap_store)
        {
            if(DMAStoreInsts.count(makeCacheAddr(II->st_vaddr)) == 0)
            {
                DMAStoreInsts.insert(make_pair(makeCacheAddr(II->st_vaddr),II));
                CacheBlocks.insert(makeCacheAddr(II->st_vaddr));
                assert(II->acc_segment_delim == 0 && "ST should not have acc_segment_delim flag");
            }
        }

        // Other insts including the load insts themselves
        OtherInsts.push_back(II);

        SegDrain = II->acc_segment_delim;

        // If ScratchpadSize is exceeded or Segment delim seen 
        if(CacheBlocks.size()*32 == ScratchpadSize || SegDrain )
        {
            // Write out DMALoads
            for(auto &dl : DMALoadInsts)
            {
                gzwrite(NewTrace[1], dl.second, sizeof(Inst_info));
            }
            cerr << "DMALoad: " << DMALoadInsts.size() << endl;
            DMALoadInsts.clear();

            // Write window delim
            Inst_info delim;
            memset((void *)&delim, 0, sizeof(Inst_info));
            delim.opcode = TR_NOP;
            delim.acc_window_delim = true;
            gzwrite(NewTrace[1], &delim, sizeof(Inst_info));
            cerr << "Write DMA delim" << endl;

            // Write out DMAStores
            for(auto &dl : DMAStoreInsts)
            {
                gzwrite(NewTrace[1], dl.second, sizeof(Inst_info));
            }
            cerr << "DMAStore: " << DMAStoreInsts.size() << endl;
            DMAStoreInsts.clear();

            // Write out the load instructions
            for(auto &l : LoadInsts)
            {
                gzwrite(NewTrace[acc_id], l.second, sizeof(Inst_info));
                writeCount++;
            }
            LoadInsts.clear();

            // Write out the other instructions 
            for(auto &i : OtherInsts)
            {
                gzwrite(NewTrace[acc_id], i, sizeof(Inst_info));
                writeCount++;
                free(i); // Frees memory for II
            }
            OtherInsts.clear();

            // Add acc_window delim if segment delim not present
            if(!SegDrain)
            {
                Inst_info t;
                memset((void*)&t, 0, sizeof(t));
                t.opcode = TR_NOP;
                t.acc_window_delim = true;
                gzwrite(NewTrace[acc_id], &t, sizeof(t));
            }

            // Reset load size
            CacheBlocks.clear();
        }
    }
    free(inst);

    assert(DMALoadInsts.size() == 0 && "DMALoadInsts not empty");
    assert(DMAStoreInsts.size() == 0 && "DMAStoreInsts not empty");
    assert(LoadInsts.size() == 0 && "LoadInsts not empty");
    assert(OtherInsts.size() == 0 && "OtherInsts not empty");
    assert(CacheBlocks.size() == 0 && "CacheBlocks not empty");

    // Write window delim
    Inst_info delim;
    memset((void *)&delim, 0, sizeof(Inst_info));
    delim.opcode = TR_NOP;
    delim.acc_window_delim = true;
    gzwrite(NewTrace[1], &delim, sizeof(Inst_info));
    cerr << "Write DMA delim" << endl;

    SegmentCounter[acc_id]++;

    return writeCount;
}

void processCPUTrace(unsigned ScratchpadSize)
{
    // Write Good Luck NOPs
    Inst_info delim;
    memset((void *)&delim, 0, sizeof(Inst_info));
    delim.opcode = TR_NOP;
    gzwrite(NewTrace[1], &delim, sizeof(Inst_info));

    Inst_info *inst = (Inst_info *)malloc(sizeof(Inst_info));    
    while(gzread(OrigTrace[0], (void*)inst, sizeof(Inst_info)) > 0)
    {
        if(inst->acc_segment_delim)
            assert(processTrace(ScratchpadSize, inst->acc_id) && "No write");

    }
    free(inst);
}

int main(int argc, char *argv[])
{
    if(argc != 2)    
    {
        std::cerr << "Usage " << argv[0] << "<Scratchpad Size>" << std::endl;
        return 0; 
    }


    for(int t = 0; t < 8; t++)
    {
        if(t != 1) // Don't read a DMA Trace
        {
            string OrigFilename = string("trace_") + to_string(t) + string(".raw");
            OrigTrace[t] = gzopen(OrigFilename.c_str(), "rb");
            if(!OrigTrace[t])
            {
                cerr << "Could not open trace_" << t << ".raw" << endl;
                return 1;
            }
        }

        if(t != 0) // Don't write a new CPU trace
        {
            string NewFilename = string("new.trace_") + to_string(t) + string(".raw");
            NewTrace[t] = gzopen(NewFilename.c_str(),"wb");
            if(!NewTrace[t])
            {
                cerr << "Could not open " << NewTrace[t] << endl;
                return 1;
            }

        }
    }

    unsigned ScratchpadSize = 0;
    istringstream(argv[1]) >> ScratchpadSize;

    assert(ScratchpadSize % 32 == 0 && "ScratchpadSize should be a multiple of 32");

    processCPUTrace(ScratchpadSize);

    // Close files

    for(int t = 0; t < 8; t++)
    {
        if(t != 1)
            gzclose(OrigTrace[t]);
        if(t != 0)
            gzclose(NewTrace[t]);
    }

    // Rename
    for(int t = 0; t < 8; t++)
    {
        if(t != 1 && t != 0)
            system((string("mv ")+string("trace_")+to_string(t)+string(".raw orig.trace_")+to_string(t)+string(".raw")).c_str());
        if(t != 0)
            system((string("mv ")+string("new.trace_")+to_string(t)+string(".raw trace_")+to_string(t)+string(".raw")).c_str());
    }

    return 0;
}
