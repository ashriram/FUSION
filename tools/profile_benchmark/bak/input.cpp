#include "HoistLoads.h"

uint32_t makeCacheAddr(uint32_t addr)
{
    return (addr >> 5) << 5;
}

void processTrace()
{
    unsigned loadSize = 0;
    unsigned storeSize = 0;
    Inst_info *inst = (Inst_info *)malloc(sizeof(Inst_info));    
    while(gzread(OrigTrace, (void*)inst, sizeof(Inst_info)) > 0)
    {
        Inst_info *II = (Inst_info*)malloc(sizeof(Inst_info));
        memcpy((void *)II, (void *)inst, sizeof(Inst_info));

        if(II->acc_heap_load)
        {
            if(LoadInsts.count(II->ld_vaddr1) == 0)
            {
                // Assuming Byte  addresable memory. Hence EA used for matching is [4:0]  
                LoadInsts.insert(make_pair(II->ld_vaddr1%32,II));
                loadSize += II->mem_read_size; 
            }
        }

        if(II->acc_heap_store)
        {
             if(StoreInsts.count(II->st_vaddr) == 0)
            {
                // Assuming Byte  addresable memory. Hence EA used for matching is [4:0]  
                StoreInsts.insert(make_pair(II->st_vaddr%32,II));
                storeSize += II->mem_write_size; 
            }
        }

    }
    free(inst);

}



void storeTrace( int i )
{
    string LdMemTraceFilename = string("ld_trace_") + to_string(i) + string(".out");
    MemLoadFilename = gzopen(LdMemTraceFilename.c_str(), "wb");    

    for(auto &dl : LoadInsts)
            {
                gzwrite(MemLoadFilename, dl.second, sizeof(Inst_info));
            }
    
    LoadInsts.clear();
    gzclose(MemLoadFilename);


    string StMemTraceFilename = string("st_trace_") + to_string(i) + string(".out");
    MemStoreFilename = gzopen(StMemTraceFilename.c_str(), "wb");    

    for(auto &dl : StoreInsts)
            {
                gzwrite(MemStoreFilename, dl.second, sizeof(Inst_info));
            }
    
    StoreInsts.clear();
    gzclose(MemStoreFilename);


}

int main()
{
       // Open trace.txt to find out the number of traces

    ifstream traceTxt("trace.txt",ios::in);
    if(!traceTxt.is_open())
    {
        cerr << "Could not open trace.txt\n";
        return 0;
    }

    int numTraces = 0;
    traceTxt >> numTraces;
    cout<<"num of traces "<<numTraces<<"\n";
    traceTxt.close();

    assert(numTraces > 2 && numTraces < 8 && "Need 1 DMA trace and 6 or less ACC traces");

    //cerr << "numTraces: " << numTraces << "\n";

    for(int i = 2; i < numTraces + 1; i++)
    {
        string OrigFilename = string("trace_") + to_string(i) + string(".raw");
        OrigTrace = gzopen(OrigFilename.c_str(), "rb");
        

        if(!OrigTrace )
        {
            cerr << "Could not open trace files" << endl;
            return 0;
        }

        processTrace();
        storeTrace(i);


        gzclose(OrigTrace);
//
//        string OldFilename = string("orig.") + OrigFilename;
//        system((string("mv ")+OrigFilename+string(" ")+OldFilename).c_str());
//        system((string("mv ")+NewFilename+string(" ")+OrigFilename).c_str());
    }

    return 0;
}
