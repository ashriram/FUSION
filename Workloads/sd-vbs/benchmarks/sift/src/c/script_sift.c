/********************************
Author: Sravanthi Kota Venkata
********************************/

#include <stdio.h>
#include <stdlib.h>
#include "sift.h"
#include "mser.h"
#include  <roi.h>
void normalizeImage(F2D* image)
{
	int i;
	int rows;
	int cols;
    int tempMin = 10000, tempMax = -1;
	rows = image->height;
	cols = image->width;

    for(i=0; i<(rows*cols); i++)
        if(tempMin > asubsref(image,i))
            tempMin = asubsref(image,i);

    for(i=0; i<(rows*cols); i++)
        asubsref(image,i) = asubsref(image,i) - tempMin;

    for(i=0; i<(rows*cols); i++)
        if(tempMax < asubsref(image,i))
            tempMax = asubsref(image,i);

    for(i=0; i<(rows*cols); i++)
        asubsref(image,i) = ( asubsref(image,i) / (tempMax+0.0) );
}

int main(int argc, char* argv[])
{
//--------------------
//
   ///------------------- 
    I2D* im;
    F2D *image;
    int rows, cols, i, j;
    F2D* frames;
    unsigned int  *startTime, *endTime, *elapsed , *elt;    
 

//--------------------------------

    int which_image;
    //int i, j, k;
    int k;
    I2D *idx;
    I2D *I;
    I2D *It;
    int rows_1=196, cols_1=98;
    //int minVal = 1000;
    //int maxVal = -1000;
    //int lev = 10;

    //unsigned int* start, *endC, *elapsed;
    char im1[100], im2[100];
    
    sprintf(im1, "%s/1.bmp", argv[1]);
    //rows_1 = rows;
    //cols_1 = cols;
    I = readImage(im1);
    rows_1 = I->height;
    cols_1 = I->width;

    It = readImage(im1);

    k = 0;
    for(i=0; i<cols_1; i++)
    {
        for(j=0; j<rows_1; j++)
        {
            asubsref(It,k++) = subsref(I,j,i);
        }
    }
    
    startTime = photonStartTiming();
    __app_roi_begin();
    idx = mser(It, 2);
    __app_roi_end();
    endTime = photonEndTiming();
    elapsed = photonReportTiming(startTime, endTime);
    printf("Input size\t\t- (%dx%d)\n", rows_1, cols_1);
    free(startTime);
    free(endTime);


//-------------------

   
    char imSrc[100];   
//--------------------------------------
//
//
//-----------------------------
    if(argc < 2)
    {
        printf("We need input image path\n");
        return -1;
    }

    sprintf(imSrc, "%s/1.bmp", argv[1]);

    //im = readImage(imSrc);
    //im = readImage(idx);
    //image = fiDeepCopy(im);
    rows = idx->height;
    cols = idx->width;

    startTime = photonStartTiming();
    __app_roi_begin();
    /** Normalize the input image to lie between 0-1 **/
	normalizeImage(idx);
    /** Extract sift features for the normalized image **/
    frames = sift(idx);

    __app_roi_end();
    endTime = photonEndTiming();

    printf("Input size\t\t- (%dx%d)\n", rows, cols);
     
    elt = photonReportTiming(startTime, endTime);
    elapsed[0] += elt[0];
    elapsed[1] += elt[1];
    
    free(startTime); 
    free(endTime); 
    free(elt); 
#ifdef CHECK   
    {
        int ret=0;
        float tol = 0.2;
#ifdef GENERATE_OUTPUT
        fWriteMatrix(frames, argv[1]);
#endif
        ret = fSelfCheck(frames, argv[1], tol);
        if (ret == -1)
            printf("Error in SIFT\n");
    }
#endif    

  
    fFreeHandle(frames);
    //free(startTime);
   // free(endTime);
    //free(elapsed);
//----------------
//
//
//
//
////------------------------
//#ifdef CHECK   
//    /** Self checking - use expected.txt from data directory  **/
//    {
//        int tol, ret=0;
//        tol = 1;
//#ifdef GENERATE_OUTPUT
//        writeMatrix(idx, argv[1]);
//#endif
//        ret = selfCheck(idx, argv[1], tol);
//        if (ret == -1)
//            printf("Error in MSER\n");
//    }
//    /** Self checking done **/
//#endif    
    photonPrintTiming(elapsed);
   
    free(elapsed); 
    iFreeHandle(I);
    iFreeHandle(It);
    




//---------------------------------------------    
    return 0;
}

