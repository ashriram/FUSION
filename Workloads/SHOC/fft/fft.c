#include "fft.h"
//////BEGIN TWIDDLES ////////

void step1(TYPE work_x[], TYPE work_y[], TYPE DATA_x[], 
        TYPE DATA_y[], TYPE data_x[], TYPE data_y[ ], TYPE smem[],
        int reversed[],
        float sin_64[448],
        float cos_64[448],
        float sin_512[448],
        float cos_512[448]
        )
{
    int tid, hi, lo, i, j, stride;
    stride = THREADS;
    //Do it all at once...
    for(tid = 0; tid < THREADS; tid++){
        //GLOBAL_LOAD...
        for(i = 0; i<8;i++){
            data_x[i] = work_x[i*stride+tid];
            data_y[i] = work_y[i*stride+tid];
        }
        FFT8(data_x, data_y);

        //First Twiddle
        //twiddles8_512(data_x, data_y, tid, 512);
        for(j = 1; j < 8; j++){
            TYPE A_x, A_y, tmp;
            A_x = cos_512[tid*7+j-1];
            A_y = sin_512[tid*7+j-1];
            tmp = data_x[j];
            data_x[j] = cmplx_MUL_x(data_x[j], data_y[j], A_x, A_y);
            data_y[j] = cmplx_MUL_y(tmp, data_y[j], A_x, A_y);
        }

        //save for fence
        for(i = 0; i < 8; i ++){
            DATA_x[tid*8 + i] = data_x[i];
            DATA_y[tid*8 + i] = data_y[i];
        }
    }

    for(tid = 0; tid < 64; tid++){
        for(i = 0; i < 8; i ++){
            data_x[i] = DATA_x[tid*8 + i];
            //data_y[i] = DATA_y[tid*8 + i];
        }
        hi = tid>>3;
        lo = tid&7;
        store8(data_x, smem, hi*8+lo, 66, reversed);
    }

}
void step3(TYPE work_x[], TYPE work_y[], TYPE DATA_x[], 
        TYPE DATA_y[], TYPE data_x[], TYPE data_y[ ], TYPE smem[],
        int reversed[],
        float sin_64[448],
        float cos_64[448],
        float sin_512[448],
        float cos_512[448]
        )
{
    int tid, hi, lo, i, j, stride;
    stride = THREADS;
    for(tid = 0; tid < 64; tid++){
        for(i = 0; i < 8; i ++){
            data_x[i] = DATA_x[tid*8 + i];
            //data_y[i] = DATA_y[tid*8 + i];
        }
        hi = tid>>3;
        lo = tid&7;
        load8(data_x, smem, lo*66+hi, 8);
        for(i = 0; i < 8; i ++){
            DATA_x[tid*8 + i] = data_x[i];
            //DATA_y[tid*8 + i] = data_y[i];
        }
    }
    for(tid = 0; tid < 64; tid++){
        for(i = 0; i < 8; i ++){
            //data_x[i] = DATA_x[tid*8 + i];
            data_y[i] = DATA_y[tid*8 + i];
        }
        hi = tid>>3;
        lo = tid&7;
        store8(data_y, smem, hi*8+lo, 66, reversed);
    }
}
void step5(TYPE work_x[], TYPE work_y[], TYPE DATA_x[], 
        TYPE DATA_y[], TYPE data_x[], TYPE data_y[ ], TYPE smem[],
        int reversed[],
        float sin_64[448],
        float cos_64[448],
        float sin_512[448],
        float cos_512[448]
        )
{

    int tid, hi, lo, i, j, stride;
    stride = THREADS;
    for(tid = 0; tid < 64; tid++){
        for(i = 0; i < 8; i ++){
            //data_x[i] = DATA_x[tid*8 + i];
            data_y[i] = DATA_y[tid*8 + i];
        }
        hi = tid>>3;
        lo = tid&7;
        load8(data_y, smem, lo*66+hi, 8);
        for(i = 0; i < 8; i ++){
            //DATA_x[tid*8 + i] = data_x[i];
            DATA_y[tid*8 + i] = data_y[i];
        }
    }
    for(tid = 0; tid < 64; tid++){
        //Reload data post-transpose...
        for(i = 0; i < 8; i ++){
            data_x[i] = DATA_x[tid*8 + i];
            data_y[i] = DATA_y[tid*8 + i];
        }

        //Second FFT8...
        FFT8(data_x, data_y);

        //Calculate hi for second twiddle calculation...
        hi = tid>>3;

        //Second twiddles calc, use hi and 64 stride version as defined in G80/SHOC...
        //twiddles8_64(data_x, data_y, hi, 64);
loop: for(j = 1; j < 8; j++){
          TYPE A_x, A_y, tmp;
          A_x = cos_64[hi*7+j-1];
          A_y = sin_64[hi*7+j-1];
          tmp = data_x[j];
          data_x[j] = cmplx_M_x(data_x[j], data_y[j], A_x, A_y);
          data_y[j] = cmplx_M_y(tmp, data_y[j], A_x, A_y);
      }

      //Save for final transpose...
      for(i = 0; i < 8; i ++){
          DATA_x[tid*8 + i] = data_x[i];
          DATA_y[tid*8 + i] = data_y[i];
      }
    }

}
void step7(TYPE work_x[], TYPE work_y[], TYPE DATA_x[], 
        TYPE DATA_y[], TYPE data_x[], TYPE data_y[ ], TYPE smem[],
        int reversed[],
        float sin_64[448],
        float cos_64[448],
        float sin_512[448],
        float cos_512[448]
        )
{
    int tid, hi, lo, i, j, stride;
    stride = THREADS;
    //Transpose..
    for(tid = 0; tid < 64; tid++){
        for(i = 0; i < 8; i ++){
            data_x[i] = DATA_x[tid*8 + i];
            //data_y[i] = DATA_y[tid*8 + i];
        }
        hi = tid>>3;
        lo = tid&7;
        store8(data_x, smem, hi*8+lo, 72, reversed);
    }
    for(tid = 0; tid < 64; tid++){
        for(i = 0; i < 8; i ++){
            data_x[i] = DATA_x[tid*8 + i];
            //data_y[i] = DATA_y[tid*8 + i];
        }
        hi = tid>>3;
        lo = tid&7;
        load8(data_x, smem, hi*72+lo, 8);
        for(i = 0; i < 8; i ++){
            DATA_x[tid*8 + i] = data_x[i];
            //DATA_y[tid*8 + i] = data_y[i];
        }
    }

}
void step9(TYPE work_x[], TYPE work_y[], TYPE DATA_x[], 
        TYPE DATA_y[], TYPE data_x[], TYPE data_y[ ], TYPE smem[],
        int reversed[],
        float sin_64[448],
        float cos_64[448],
        float sin_512[448],
        float cos_512[448]
        )
{

    int tid, hi, lo, i, j, stride;
    stride = THREADS;
    for(tid = 0; tid < 64; tid++){
        for(i = 0; i < 8; i ++){
            //data_x[i] = DATA_x[tid*8 + i];
            data_y[i] = DATA_y[tid*8 + i];
        }
        hi = tid>>3;
        lo = tid&7;
        store8(data_y, smem, hi*8+lo, 72, reversed);
    }
    for(tid = 0; tid < 64; tid++){
        for(i = 0; i < 8; i ++){
            //data_x[i] = DATA_x[tid*8 + i];
            data_y[i] = DATA_y[tid*8 + i];
        }
        hi = tid>>3;
        lo = tid&7;
        load8(data_y, smem, hi*72+lo, 8);
        for(i = 0; i < 8; i ++){
            //DATA_x[tid*8 + i] = data_x[i];
            DATA_y[tid*8 + i] = data_y[i];
        }
    }

}
void step11(TYPE work_x[], TYPE work_y[], TYPE DATA_x[], 
        TYPE DATA_y[], TYPE data_x[], TYPE data_y[ ], TYPE smem[], 
        int reversed[],
        float sin_64[448],
        float cos_64[448],
        float sin_512[448],
        float cos_512[448]
        )
{

    int tid, hi, lo, i, j, stride;
    stride = THREADS;
    for(tid = 0; tid < 64; tid++){
        //Load post-trans
        for(i = 0; i < 8; i ++){
            data_x[i] = DATA_x[tid*8 + i];
            data_y[i] = DATA_y[tid*8 + i];
        }

        //Final 8pt FFT...
        FFT8(data_x, data_y);

        //Global store
        for(i=0; i<8;i++){
            //work[i*stride+tid] = data[i];
            work_x[i*stride+tid] = data_x[reversed[i]];
            work_y[i*stride+tid] = data_y[reversed[i]];
        }
    }
}
void fft1D_512(TYPE work_x[512], TYPE work_y[512], 
        TYPE DATA_x[THREADS*8],
        TYPE DATA_y[THREADS*8],
        TYPE data_x[ 8 ],
        TYPE data_y[ 8 ],
        TYPE smem[8*8*9],
        int reversed[8],
        float sin_64[448],
        float cos_64[448],
        float sin_512[448],
        float cos_512[448]
        )
{
    int tid, hi, lo, i, j, stride;
    stride = THREADS;


    step1(work_x, work_y, DATA_x, DATA_y, data_x, data_y, smem, reversed, sin_64, cos_64, sin_512, cos_512);
    /*step2(work_x, work_y, DATA_x, DATA_y, data_x, data_y, smem, reversed, sin_64, cos_64, sin_512, cos_512);*/
    step3(work_x, work_y, DATA_x, DATA_y, data_x, data_y, smem, reversed, sin_64, cos_64, sin_512, cos_512);
    /*step4(work_x, work_y, DATA_x, DATA_y, data_x, data_y, smem, reversed, sin_64, cos_64, sin_512, cos_512);*/
    step5(work_x, work_y, DATA_x, DATA_y, data_x, data_y, smem, reversed, sin_64, cos_64, sin_512, cos_512);
    /*step6(work_x, work_y, DATA_x, DATA_y, data_x, data_y, smem, reversed, sin_64, cos_64, sin_512, cos_512);*/
    step7(work_x, work_y, DATA_x, DATA_y, data_x, data_y, smem, reversed, sin_64, cos_64, sin_512, cos_512);
    /*step8(work_x, work_y, DATA_x, DATA_y, data_x, data_y, smem, reversed, sin_64, cos_64, sin_512, cos_512);*/
    step9(work_x, work_y, DATA_x, DATA_y, data_x, data_y, smem, reversed, sin_64, cos_64, sin_512, cos_512);
    /*step10(work_x, work_y, DATA_x, DATA_y, data_x, data_y, smem, reversed, sin_64, cos_64, sin_512, cos_512);*/
    step11(work_x, work_y, DATA_x, DATA_y, data_x, data_y, smem, reversed, sin_64, cos_64, sin_512, cos_512);
}
int main(){
    /*TYPE a_x[512];*/
    /*TYPE a_y[512];*/
    int i,k;



#include "sincos.cpp"

    TYPE DATA_x[THREADS*8*NUM_ITERS];
    TYPE DATA_y[THREADS*8*NUM_ITERS];
    TYPE data_x[ 8*NUM_ITERS ];
    TYPE data_y[ 8*NUM_ITERS ];
    TYPE smem[8*8*9];
    int reversed[8] = {0,4,2,6,1,5,3,7};

    float *sin_64_h = (float *)malloc(448*sizeof(float));
    float *sin_512_h = (float *)malloc(448*sizeof(float));
    float *cos_64_h = (float *)malloc(448*sizeof(float));
    float *cos_512_h = (float *)malloc(448*sizeof(float));

    memcpy(sin_64_h, sin_64, 448*sizeof(float));
    memcpy(sin_512_h, sin_512, 448*sizeof(float));
    memcpy(cos_64_h, cos_64, 448*sizeof(float));
    memcpy(cos_512_h, cos_512, 448*sizeof(float));

    TYPE *a_x = (TYPE *)malloc(512*(sizeof(TYPE))*NUM_ITERS);
    TYPE *a_y = (TYPE *)malloc(512*(sizeof(TYPE))*NUM_ITERS);

    for( i = 0; i < 512*NUM_ITERS; i++){
        a_x[i] = ((float)(random()%1000))/100;
        a_y[i] = ((float)(random()%1000))/100;
    }
    // loop
    for(k = 0; k < NUM_ITERS; k++)
    {
        __app_roi_begin();
        fft1D_512(a_x+(k*512), a_y+(k*512), DATA_x + (k*THREADS*8), DATA_y+(k*THREADS*8), data_x+(k*8), data_y+(k*8), smem, reversed, sin_64_h, sin_512_h, cos_64_h, cos_512_h);
        __app_roi_end();

        for( i = 0; i < 2; i++){
            printf("x = %i y = %i \n", a_x[i+k*512], a_y[i+k*512]);
        }


    }
    free(a_x);
    free(a_y);
    // endloop
    free(sin_64_h);
    free(sin_512_h);
    free(cos_64_h);
    free(cos_512_h);

    return 0;
}
