#include "HoistLoads.h"
#include <fstream>

uint32_t makeCacheAddr(uint32_t addr)
{
    return (addr >> 5) << 5;
}

unsigned long long  processTrace()
{
    unsigned long long  loadSize = 0;
    unsigned long long  storeSize = 0;
    Inst_info *inst = (Inst_info *)malloc(sizeof(Inst_info));    
    while(gzread(OrigTrace, (void*)inst, sizeof(Inst_info)) > 0)
    {
        Inst_info *II = (Inst_info*)malloc(sizeof(Inst_info));
        memcpy((void *)II, (void *)inst, sizeof(Inst_info));

        
            if(II->acc_heap_load && LoadInsts.count(makeCacheAddr(II->ld_vaddr1)) == 0)
            {
                LoadInsts.insert(make_pair(makeCacheAddr(II->ld_vaddr1),II));
                loadSize += II->mem_read_size; 
                LoadOrder.push_back(II->ld_vaddr1);
            }
 
        
            if(II->acc_heap_load && LoadInsts.count(makeCacheAddr(II->ld_vaddr2)) == 0)
            {
                LoadInsts.insert(make_pair(makeCacheAddr(II->ld_vaddr2),II));
                loadSize += II->mem_read_size; 
                LoadOrder.push_back(II->ld_vaddr2);
            }
         
            if(II->acc_heap_store && LoadInsts.count(makeCacheAddr(II->st_vaddr)) == 0)
            {
                StoreInsts.insert(make_pair(II->st_vaddr,II));
                storeSize += II->mem_write_size;
            }


    }
    free(inst);
    return loadSize;
}


//----------------------------
void storeTrace( int i )
{

    string LdMemTraceFilename = string("Ld_mem_trace_") + to_string(i) + string(".out");
    ofstream myfile;
    myfile.open (LdMemTraceFilename);
    for(auto &dl : LoadOrder)
    {
        uint32_t  x = dl;
        myfile <<hex<<x<<dec<<endl;
    }
    
    myfile.close();
    LoadInsts.clear();
    LoadOrder.clear();



    string StMemTraceFilename = string("St_mem_trace_") + to_string(i) + string(".out");
    ofstream myfile_st;
    myfile_st.open (StMemTraceFilename);

    for(auto &dl : StoreInsts)
    {
        uint32_t  x = dl.first;
        myfile_st <<hex<<x<<dec<<endl;
    }
    myfile_st.close(); 
    StoreInsts.clear();

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

    assert(numTraces > 2 && numTraces < 9 && "Need 1 DMA trace and 6 or less ACC traces");

    //cerr << "numTraces: " << numTraces << "\n";

    for(int i = 2; i < numTraces  ; i++)
    {
        string OrigFilename = string("trace_") + to_string(i) + string(".raw");
        OrigTrace = gzopen(OrigFilename.c_str(), "rb");
        

        if(!OrigTrace )
        {
            cerr << "Could not open trace files  " <<OrigFilename <<endl;
            return 0;
        }
        //unsigned long long  total_load_size =0;
        //cout<< "Total load + Store size for i=" <<i<<" is "<<processTrace()<<endl;
        storeTrace(i);

        gzclose(OrigTrace);

    }
    return 0;
}
