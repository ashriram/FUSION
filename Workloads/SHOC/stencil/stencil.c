#include "stencil.h"
//The row/col sizes specified in SHOC:
//{512, 1024, 2048, 4096} 


int orig[1156];
int solution[1156];
int filter[9];

void stencil()
{
    int i, j,k1, k2, sidx, didx, fidx;
    int tmp, Si, SI, Di, Ti;

    for (i=0; i<32; i++) {
        for (j=0; j<32; j++) {
            Si = 0;
            SI = 0;
            tmp = 0;
            fidx = 0;
            SI = i * 34;
            sidx = SI + j ;
            didx = sidx;

            Si = filter[fidx] * orig[sidx];
            tmp = tmp + Si;
            sidx ++;
            fidx ++;

            Si = filter[fidx] * orig[sidx];
            tmp = tmp + Si;
            sidx ++;
            fidx ++;

            Si = filter[fidx] * orig[sidx];
            tmp = tmp + Si;
            sidx ++;
            fidx ++;

            sidx += (34 ) - 3;

            Si = filter[fidx] * orig[sidx];
            tmp = tmp + Si;
            sidx ++;
            fidx ++;

            Si = filter[fidx] * orig[sidx];
            tmp = tmp + Si;
            sidx ++;
            fidx ++;

            Si = filter[fidx] * orig[sidx];
            tmp = tmp + Si;
            sidx ++;
            fidx ++;

            sidx = sidx + (34 ) - 3;

            Si = filter[fidx] * orig[sidx];
            tmp = tmp + Si;
            sidx ++;
            fidx ++;

            Si = filter[fidx] * orig[sidx];
            tmp = tmp + Si;
            sidx ++;
            fidx ++;

            Si = filter[fidx] * orig[sidx];
            tmp = tmp + Si;
            sidx ++;
            fidx ++;
            solution[didx] = tmp;
        }
    }
}

int main()
{
    /*int *OrigImg;*/
    /*int *Solution;*/
    /*int *Filter;*/
    int i, j, k;
    int max, min;

    srand(8650341L);
    max = 2147483646;
    min = 0;	
    /*OrigImg = (int *)malloc(sizeof(int) * 34 * 34);*/
    /*Solution = (int *)malloc(sizeof(int) * 34 * 34);*/
    /*Filter = (int *) malloc(sizeof(int) * 3 * 3);*/
    for(i=0;i<34 ;i++)
    {
        for(j=0;j<34 ;j++)
        {
            orig[i * (34 ) + j] = (int)(( rand() * 1.0 * ( max-min) / (RAND_MAX)) + min); 
            solution[i * (34 ) + j] = 0;
            //printf("Orig: %d ", OrigImg[i*(34+2) +j]);
        }
        printf("\n");
    }	

    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            filter[i*3 + j] = (int)(( rand() * 1.0 * (max - min ) / (RAND_MAX)) + min);
            //if (i == 0 && j == 0)
            //  Filter[i*3 + j] = 1;
            //else
            //  Filter[i*3 + j] = 0;
        }
    }

    stencil();

    for(i=0;i<(34);i++)
    {
        for(j=0;j<34;j++)
        {
            printf("%d, %d, %d,%d\n ", i, j, orig[i*(34 ) + j], solution[i * (34) + j]);
        }
        printf("\n");
    }
    printf("Success!!\n");

    return 0;
}
