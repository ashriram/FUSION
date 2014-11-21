/*
Copyright (c) 2014, the President and Fellows of Harvard College.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of Harvard University nor the names of its contributors may 
  be used to endorse or promote products derived from this software without
  specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "needwun.h"
void needwun(char SEQA[N], char SEQB[M], char allignedA[sum_size], char allignedB[sum_size], 
             int A[dyn_size], char ptr[dyn_size]){

    int mismatch, i,j,max;

    int score, match, gap,
        choice1, choice2, choice3, 
        Mul1, Mul2;//, Mul3;


    mismatch    = -1;

    init_row : for(i = 0; i < N1; i++){
        A[i]   = i * mismatch;
    }

    init_col : for(i = 0; i <M1; i++){
        A[i * N1] = i * mismatch;
    }
    gap         = -1;
    match  = 1;
    mismatch    = -1;
    //matrix Filling Loop
    fill_out : for(i = 1; i < M1; i++){
        fill_in : for(j = 1; j < N1; j++){
            if(SEQA[j - 1] == SEQB[i - 1]){
                score = match;
            }
            else{
                score = mismatch;
            }
                  }
            Mul1 = (i-1) * N1;
            Mul2 = (i*N1);

            choice1 = A[Mul1 + (j - 1)] + score;
            choice2 = A[Mul1 + (j)]     + gap;
            choice3 = A[Mul2 + (j-1)]   + gap;

            if(choice1 > choice2){
                max = choice1;
            }
            else{
                max = choice2;
            }
            if(choice3 > max){
                max = choice3;
            }

            A[Mul2 + j] = max;
            if(max == choice1){
                ptr[Mul2 + j] = 0;
            }
            else if(max == choice2){
                ptr[Mul2 + j] = 1;
            }
            else{
                ptr[Mul2 + j] = -1;
            }
        }
    }

void needwun_2(char SEQA[N], char SEQB[M], char allignedA[sum_size], char allignedB[sum_size], 
    int A[dyn_size],char ptr[dyn_size]){
    //ptr   SEQA  SEQB allignedA allignedB  
    int  i, j, i_t, j_t;
    //TraceBack
    i = M;
    j = N;
    i_t = 0;
    j_t = 0;
    int Mul3;
    int mismatch = -1;
 
    init_row : for(i = 0; i < N1; i++){
        A[i]   = i * mismatch;
    }

    init_col : for(i = 0; i <M1; i++){
        A[i * N1] = i * mismatch;
    }





    trace : while(i > 0 || j > 0){
        Mul3 = j*M;
        if (ptr[i + Mul3] == 0){
            allignedA[i_t] = SEQA[i];
            allignedB[j_t] = SEQB[j];
            j_t++;
            i_t++;
            i--;
            j--;
        }
        else if(ptr[i + Mul3] == 1){
            allignedA[i_t] = SEQA[i];
            allignedB[j_t] = 'X';
            j_t++;
            i_t++;
            i--;
        }
        else{
            allignedA[i_t] = 'X';
            allignedB[j_t] = SEQB[j];
            j_t++;
            i_t++;
            j--;
        }
    }
}







struct timespec localStart, localStop, globalStart, globalStop, fullTime;
unsigned long long startCycle = 0, stopCycle = 0;

#define CYCLECOUNT

#if defined(__i386__)

static __inline__ unsigned long long rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

#elif defined(__x86_64__)

static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

#endif

struct timespec timeDiff(struct timespec start, struct timespec end)
{
    struct timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) 
    {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}

double tsFloat(struct timespec time)
{
    return ((double) time.tv_sec + (time.tv_nsec / 1000000000.0));
}

void startLocalTimer()
{
#ifndef CYCLECOUNT
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &localStart);
#else
    startCycle = rdtsc();
    /*printf("[Cycle] Start: %llu ",startCycle);*/
#endif
}


void stopLocalTimer()
{
#ifndef CYCLECOUNT
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &localStop);
    fullTime = timeDiff(localStart,localStop);
    printf("[Timer] Local: %f\n", tsFloat(fullTime));
#else
    stopCycle = rdtsc();
    printf("[Cycle] Diff: %llu\n", stopCycle - startCycle);
    startCycle = 0;
    stopCycle = 0;
#endif
}

