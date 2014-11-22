/* testc - Test adpcm coder */

#include "adpcm.h"
#include <stdio.h>
#include <stdlib.h>
#include <roi.h>

struct adpcm_state state;

#define NSAMPLES 11264 
#define BREAK 3
/*char	abuf[NSAMPLES/2];*/
/*short	sbuf[NSAMPLES];*/

// 66KB of data read in at a time-- iterate 4 times

main() {
    int n,i,b=0;
    short * sbuf = (short* )malloc(NSAMPLES * sizeof(short));
    char * abuf = (char* )malloc(NSAMPLES/2 * sizeof(char));

    while(1) {
        n = read(0, sbuf, NSAMPLES*2);
        if ( n < 0 ) {
            perror("input file");
            exit(1);
        }
        if ( n == 0 ) break;
        __app_roi_begin();
        adpcm_coder(sbuf, abuf, n/2, &state);
        // Do something to the value in the CPU
        for(i = 0; i < NSAMPLES/2; i++)
        {
            abuf[i] &= (char)~3;
        }
        adpcm_decoder(abuf, sbuf, n/2, &state);
        __app_roi_end();
        if (b++ == BREAK) break;
        /*write(1, abuf, n/4);*/
    }
    fprintf(stderr, "Final valprev=%d, index=%d\n",
            state.valprev, state.index);
    exit(0);
}
