#include "triad.h"

int a[NUM], b[NUM], c[NUM];

void triad(int s){
    int i;
    for(i=0;i<NUM;i++)
        c[i] = a[i] + s*b[i];
}

int main(){
    int i;
    srand(time(NULL));
    for(i=0; i<NUM; i++){
        c[i] = 0;
        a[i] = rand();
        b[i] = rand();
    }

    triad(3);
    FILE *output;
    output = fopen("output.data", "w");
    for(i=0; i<NUM; i++)
        fprintf(output, "%d,", c[i]);
    fprintf(output, "\n");
    fclose(output);
    return a[0];
}
