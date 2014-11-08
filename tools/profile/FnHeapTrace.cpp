#include "pin.H"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <zlib.h>
#include <cstdio>
#include <map>

/* ================================================================== */
// Functions to Instrument
/* ================================================================== */

static string fnNames[] = {
    "main","rec_rot","iter_rot","read_ppm","write_ppm"
};

/* ================================================================== */
// Global variables
/* ================================================================== */
ofstream OutFile;
FILE *currentFile=NULL;
FILE *log1 = NULL;
FILE *log2 = NULL;
FILE *log3 = NULL;
FILE *log4 = NULL;
int fnID = 0;
std::map<UINT32, string> fnIdName;
std::ostream * out = &cerr;
bool flag=false;
unsigned long long address[100000000];
UINT32 writer[100000000];
UINT32 reader[100000000];
UINT32 p[100];
UINT32 c[100];
UINT32 count2[100];
UINT32 current=0;//current function ID
int i=1;//number of writes
int ii=1;
int icount[100];
int stack[100000];
int stack_counter=0;
int from[100];
int to[100];
int n=1;
UINT32 executed[100000];
int m=1;
int fun=0;//number of total invocations

/* ===================================================================== */
// Command line switches
/* ===================================================================== */



/* ===================================================================== */
// Utilities
/* ===================================================================== */

/*!
 *  Print out help message.
 */
INT32 Usage()
{
    cerr << " " << endl <<
        " " << endl << endl;

    return -1;
}

/* ===================================================================== */
// Analysis routines
/* ===================================================================== */
static bool main_entry_seen = false;
bool main_rtn_instrumented = false;
/* ===================================================================== */
// Instrumentati[on callbacks
/* ===================================================================== */

VOID EnterRTN(UINT32 fnID)
{
    if(main_entry_seen){

        stack_counter++;
        stack[stack_counter]=fnID;
        //cerr<< "function : "<<fnIdName[fnID] << endl;

        if(current!=0)
        {
            bool flag6=false;
            for(int q=1;q<n;q++)
                if(from[q]==stack[stack_counter-1] && to[q]==stack[stack_counter])
                    flag6=true;
            if(!flag6){
                OutFile<<fnIdName[stack[stack_counter-1]]<<" ----> "<<fnIdName[stack[stack_counter]]<<endl;
                from[n]=stack[stack_counter-1];
                to[n]=stack[stack_counter];
                n++;
            }
        }

        fun++;
        current=fnID; 
        //cerr<<"current = "<< current<<endl;
    }
}


VOID ExitRTN(UINT32 fnID)
{
    if(main_entry_seen){

        //cerr<<"Exit Function: " << fnIdName[fnID]<<endl;

        stack_counter--;
        //cerr<< "exit--- current is: "<< current<<endl;
        executed[m]=current;
        m++;

    }
}

VOID MemRead(VOID *ip, VOID *addr, UINT32 size)
{
    bool flag7=false;
    for(int pp=1;pp<m;pp++)
        if(executed[pp]==current)
            flag7=true;
    if(main_entry_seen ){

        for(int j=1;j<i;j++){
            if(address[j]==reinterpret_cast<unsigned long long>(addr)){
                bool flag2=false;
                if(reader[j]==current){

                }
                else{

                    for(int f=1;f<ii;f++){
                        if(p[f]==writer[j] && c[f]==current){
                            count2[f]=count2[f]+size;
                            reader[j]=current;
                            flag2=true;

                        }
                    }
                    if(!flag2){
                        p[ii]=writer[j];
                        c[ii]=current;
                        reader[j]=current;
                        count2[ii]=size;
                        ii++;

                    }
                }//else
            }
        }
    }
}


VOID MemWrite(VOID *ip, VOID *addr,UINT32 size)
{
    bool flag8=false;
    for(int pp=1;pp<m;pp++)
        if(executed[pp]==current)
            flag8=true;
    if(main_entry_seen ){

        bool flag3=false;
        for(int j=1;j<i;j++){
            if(address[j]==reinterpret_cast<unsigned long long>(addr)){

                writer[j]=current;
                reader[j]=0;

                flag3=true;
            }
        }
        if(!flag3){
            address[i]=reinterpret_cast<unsigned long long>(addr);
            writer[i]=current;
            reader[i]=0;
            i++;
        }//else
    }
}

static void
enterMainImage(ADDRINT ip, ADDRINT target, ADDRINT sp) {
    main_entry_seen = true;
    OutFile.open("log2.txt");
}

static void
exitMainImage(ADDRINT ip, ADDRINT target, ADDRINT sp) {
    main_entry_seen = false;
    OutFile.close();
}
void count(){
    bool flag7=false;
    for(int pp=1;pp<m;pp++)
        if(executed[pp]== current)
            flag7=true;
    if(main_entry_seen && !flag7)
        icount[current]++;
}

VOID ImageLoad(IMG img,  VOID *v)
{
    for( SEC sec= IMG_SecHead(img); SEC_Valid(sec); sec = SEC_Next(sec) )
    {
        for( RTN rtn= SEC_RtnHead(sec); RTN_Valid(rtn); rtn = RTN_Next(rtn) )
        {
            string rtnName =  PIN_UndecorateSymbolName(RTN_Name(rtn), UNDECORATION_NAME_ONLY);
            if(rtnName==std::string("main") ){
                main_rtn_instrumented = true;
                RTN_Open(rtn);
                RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR)enterMainImage,
                        IARG_INST_PTR, IARG_ADDRINT, RTN_Address(rtn),
                        IARG_REG_VALUE, REG_STACK_PTR, IARG_END);
                RTN_Close(rtn);
            }
            if(rtnName==std::string("main") ){
                main_rtn_instrumented = true;
                RTN_Open(rtn);
                RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR)exitMainImage,
                        IARG_INST_PTR, IARG_ADDRINT, RTN_Address(rtn),
                        IARG_REG_VALUE, REG_STACK_PTR, IARG_END);
                RTN_Close(rtn);
            }
            bool flag4=false;
            RTN_Open(rtn);
            for(UINT32 i = 0; i < sizeof(fnNames)/sizeof(*fnNames); i++)
            {
                if( rtnName==fnNames[i] )
                {
                    //cerr<< " welcome! "<<rtnName<<endl;
                    flag4=true;
                    fnID++;
                    fnIdName.insert(std::make_pair(fnID, rtnName));
                    // //       fnID++;
                    RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR)EnterRTN , IARG_UINT32, fnID, IARG_END);
                }
            }

            for (INS ins = RTN_InsHead(rtn); INS_Valid(ins); ins = INS_Next(ins))
            {
                if(!rtnName.find("_") == 0 && !INS_IsMemoryRead(ins) && !INS_IsMemoryWrite(ins) && !INS_IsBranchOrCall(ins) && !INS_IsIndirectBranchOrCall(ins) )

                    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)count, IARG_END);

                UINT32 memoryOperands = INS_MemoryOperandCount(ins);

                for (UINT32 memOp = 0; memOp < memoryOperands; memOp++)
                {
                    // Note that if the operand is both read and written we log it once
                    // for each.


                    if( !rtnName.find("_") == 0 && !rtnName.find(".") == 0 && !rtnName.find("std") == 0)

                    {
                        if (INS_MemoryOperandIsRead(ins, memOp))
                        {

                            INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR)MemRead,
                                    IARG_INST_PTR,
                                    IARG_MEMORYOP_EA, memOp,
                                    IARG_MEMORYREAD_SIZE,
                                    IARG_END);
                        }

                        if (INS_MemoryOperandIsWritten(ins, memOp))
                        {
                            INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR)MemWrite,
                                    IARG_INST_PTR,
                                    IARG_MEMORYOP_EA, memOp,
                                    IARG_MEMORYWRITE_SIZE,
                                    IARG_END);
                        }
                    }
                }
            }
            if(flag4)
                RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR)ExitRTN,IARG_UINT32, fnID, IARG_END);
            RTN_Close(rtn);

        }
    }
}


/*!
 * Print out analysis results.
 * This function is called when the application exits.
 * @param[in]   code            exit code of the application
 * @param[in]   v               value specified by the tool in the
 *                              PIN_AddFiniFunction function call
 */
VOID Fini(INT32 code, VOID *v)
{
    OutFile.open("log1.txt");
    OutFile << "Function Name:  " << endl;


    *out <<  "===============================================" << endl;
    *out <<  "===============================================" << endl;

    //cerr <<  "                      results                  " << endl;
    //cerr <<  "===============================================" << endl;
    //cerr <<  "producer          consumer           count     " << endl;
    for(int iii=1; iii<ii;iii++){
        //cerr<< fnIdName[p[iii]]<<"        "<<fnIdName[c[iii]]<<"          "<<count2[iii]/4<<endl;
    }
    //cerr <<  "===============================================" << endl;
    for(int iii=1; iii<=fnID;iii++){
        //cerr<< fnIdName[iii]<<" icount= "<<icount[iii]<<endl;
        if(icount[iii]>0)
        {
            OutFile << fnIdName[iii] << endl;

        }
    }
    OutFile.close();
    OutFile.open("log3.txt");
    OutFile << "Instruction count for each function:  " << endl;
    OutFile << "NOTE: just aritnmethic instructions. Not memory instructions, not control flow instructions.  " << endl ;
    for(int iii=1; iii<=fnID;iii++){
        if(icount[iii]>0)
            OutFile <<fnIdName[iii]<<" icount= "<<icount[iii]<<endl;
    }
    OutFile.close();
    OutFile.open("log4.txt");
    OutFile << "Amount of data (in byte) transfered into each function invocation, broken down by source fuction invocation."<<endl<<endl;
    for(int jj=1;jj<=fnID;jj++){
        bool flag5=false;
        if(icount[jj]>0){
            OutFile <<"Function : "<< fnIdName[jj]<<" : "<<endl;
            for(int iii=1; iii<ii;iii++){

                if(c[iii]==unsigned (jj)){
                    OutFile <<fnIdName[ p[iii]] << "     " << count2[iii]/4<<endl;
                    flag5=true;
                }

            }
            if(!flag5)
                OutFile <<" No data transfered into this function"<<endl;
            OutFile <<endl;
        }
    }
    OutFile.close();
}
/*!
 * The main procedure of the tool.
 * This function is called when the application image is loaded but not yet started.
 * @param[in]   argc            total number of elements in the argv array
 * @param[in]   argv            array of command line arguments,
 *                              including pin -t <toolname> -- ...
 */
int main(int argc, char *argv[])
{
    // Initialize PIN library. Print help message if -h(elp) is specified
    // in the command line or the command line is invalid
    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }

    PIN_InitSymbols();
    IMG_AddInstrumentFunction ( &ImageLoad, NULL );
    PIN_AddFiniFunction( &Fini, NULL );

    cerr <<  "===============================================" << endl;
    cerr <<  "This application is instrumented by FnHeapTrace" << endl;
    cerr <<  "===============================================" << endl;

    // Start the program, never returns
    PIN_StartProgram();

    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */

