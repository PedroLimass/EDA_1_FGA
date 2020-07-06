#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void normalizador(float *vetor){

    int N=536;
    float *p=calloc(N,sizeof(float));
    int maior=0,menor=0;
    int i=0,j=0,aux;
    float x;
    float Y;




    for(i=0;i<536;i++){
        if(vetor[i]>vetor[i]){maior=vetor[i];}
        if(vetor[i]<vetor[i]){menor=vetor[i];}
    }


    for(j=0;j<536;j++){
        aux=vetor[j];
        x=((aux-menor)/(maior-menor));
        vetor[j]=x;
        x=0;
    }



    return;
}

void media(float *vetor){

    int i=0,j;
    float au;
    for(i=0;i<532;i++){
        j=vetor[i];
        au=j/25;
        vetor[j]=au;
        au=0;
    }

    return;
}


