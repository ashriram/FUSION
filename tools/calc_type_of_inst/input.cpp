#include "HoistLoads.h"
#include <fstream>

uint32_t makeCacheAddr(uint32_t addr)
{
    return (addr >> 5) << 5;
}

void  processTrace()
{
    unsigned long long  loadSize = 0;
    unsigned long long  storeSize = 0;
    unsigned long long  intSize = 0;
    unsigned long long  floatSize = 0;
    //unsigned storeSize = 0;
    Inst_info *inst = (Inst_info *)malloc(sizeof(Inst_info));    
    while(gzread(OrigTrace, (void*)inst, sizeof(Inst_info)) > 0)
    {
        Inst_info *II = (Inst_info*)malloc(sizeof(Inst_info));
        memcpy((void *)II, (void *)inst, sizeof(Inst_info));

        
        
            if(II->acc_heap_load) 
            {
                loadSize ++; 
            }
            else if (II->acc_heap_store )
            {
                 storeSize ++;
                
            }
            else if (II->is_fp)
            {
                    floatSize++; 
            
            }
            else if (II->ld_vaddr1 != 0 ||  II->ld_vaddr2 != 0  ) 
            {
                loadSize++;
            }
            
            else if (II->st_vaddr != 0 )
            {
                storeSize++;
            }

            else 
            {
                intSize++;
            }


    }
    free(inst);
//    cout<<"load     inst :"<<loadSize<<endl;
//    cout<<"store    inst :"<<storeSize<<endl;
//    cout<<"Int      inst :"<<intSize<<endl;
//    cout<<"Float    inst :"<<floatSize<<endl;
    cout<<intSize<<endl;
    cout<<floatSize<<endl;

    cout<<loadSize<<endl;
    cout<<storeSize<<endl;

}


//----------------------------
void storeTrace( int i )
{

    string LdMemTraceFilename = string("mem_trace_") + to_string(i) + string(".out");
    //MemLoadFilename = gzopen(LdMemTraceFilename.c_str(), "wb");    
    ofstream myfile;
    myfile.open (LdMemTraceFilename);
    for(auto &dl : LoadInsts)
    {
        //gzwrite(MemLoadFilename, dl.second, sizeof(Inst_info));
        uint32_t  x = dl.first;
        myfile <<hex<<x<<dec<<endl;

    }
    
    myfile.close();
    LoadInsts.clear();
    //gzclose(MemLoadFilename);

//
//    string StMemTraceFilename = string("st_trace_") + to_string(i) + string(".out");
//    MemStoreFilename = gzopen(StMemTraceFilename.c_str(), "wb");    
//
//    for(auto &dl : StoreInsts)
//            {
//                gzwrite(MemStoreFilename, dl.second, sizeof(Inst_info));
//            }
//    
//    StoreInsts.clear();
//    gzclose(MemStoreFilename);


}

//----------------------------
void  countDatasharing(int i, int j)
{
    int data_sharing_count= 0;
    unsigned int memSize = 0;
//    Inst_info *inst_i = (Inst_info *)malloc(sizeof(Inst_info));    
//    while(gzread(trace_i, (void*)inst_i, sizeof(Inst_info)) > 0)
//    {
// 
//
//        Inst_info *inst_j = (Inst_info *)malloc(sizeof(Inst_info));    
//        while(gzread(trace_j, (void*)inst_j, sizeof(Inst_info)) > 0)
//        {
//            cout<<inst_i<<"\t"<<inst_j<<endl;
//            if (inst_i==inst_j)    
//                data_sharing_count++; 
//            //memSize += inst_j->mem_read_size; 
//        }
//        free(inst_j);
//    }

    string traceFilename_i = string("mem_trace_") + to_string(i) + string(".out");
    string traceFilename_i_1 = string("mem_trace_") + to_string(j) + string(".out");
    ifstream trace_i (traceFilename_i);
    ifstream trace_j (traceFilename_i_1);
    string line;
    string line2;
    //ifstream myfile (trace_i);
    if (trace_i.is_open() && trace_j.is_open())
    {
            while ( getline (trace_i,line) )
            {

                while(getline (trace_j,line2))
                {
                    if(line==line2) 
                        data_sharing_count++;
                                    
                }
                trace_j.seekg(0);
            }
    }

    trace_i.close();
    trace_j.close();
    
    cout <<"DATA sharing between " <<i <<"and "<<j << "=  "<<data_sharing_count<<"\n"<<endl;

    //free(inst_i);
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
        
        cout<<"Trace No :"<<i<<endl;
        processTrace();
        //storeTrace(i);

        gzclose(OrigTrace);

    }
    return 0;
}
