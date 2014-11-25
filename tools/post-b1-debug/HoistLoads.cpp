#include "HoistLoads.h"

bool processTrace(int acc_id)
{
    //cerr << "Processing ACC " << acc_id << " Segment " << SegmentCounter[acc_id] << endl;
    Inst_info *inst = (Inst_info *)malloc(sizeof(Inst_info));    
    unsigned Count = 0;
    while(gzread(OrigTrace[acc_id], (void*)inst, sizeof(Inst_info)) > 0)
    {
        Count++;
        if(inst->acc_window_delim)
        {
            cerr << Count <<" ACC" << acc_id << " -> DMA"  << endl;
            return false;
        }
        if(inst->acc_segment_delim)    
        {
            cerr << Count <<" ACC" << acc_id << " -> DMA"  << endl;
            break;
        }
    }
    free(inst);
    SegmentCounter[acc_id]++;
    return true;
}

void processDMATrace(int acc_id)
{
    Inst_info *inst = (Inst_info *)malloc(sizeof(Inst_info));    
    unsigned Count = 0;
    bool BreakNext = false;
    while(gzread(OrigTrace[1], (void*)inst, sizeof(Inst_info)) > 0)
    {
        DMACount++;
        Count++;
        if(inst->acc_window_delim)
        {
            if(BreakNext)
            {
                cerr << Count << " DMA -> CPU0 after ACC" << acc_id << endl;
                break;
            }
            cerr << Count << " DMA -> ACC" << acc_id << endl;

            if(processTrace(acc_id))
                BreakNext = true;
            else
                Count = 0;
        }

    }
    free(inst);
}

void processCPUTrace()
{
    Inst_info *inst = (Inst_info *)malloc(sizeof(Inst_info));    
    while(gzread(OrigTrace[0], (void*)inst, sizeof(Inst_info)) > 0)
    {
        if(inst->acc_window_delim)    
            assert(0 && "Found Window Delim in CPU Trace");

        if(inst->acc_segment_delim)
        {
            cerr << "CPU0 -> DMA" << endl;
            processDMATrace(inst->acc_id);
        }
    }
    free(inst);
}

int main(int argc, char *argv[])
{
    for(int t = 0; t < 8; t++)
    {
        string OrigFilename = string("trace_") + to_string(t) + string(".raw");
        OrigTrace[t] = gzopen(OrigFilename.c_str(), "rb");
        if(!OrigTrace[t])
        {
            cerr << "Could not open trace_" << t << ".raw" << endl;
            return 1;
        }
    }

    processCPUTrace();

    // Close files

    for(int t = 0; t < 8; t++)
    {
        gzclose(OrigTrace[t]);
    }
    cerr << "DMA Count : " << DMACount << endl;

    return 0;
}
