#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/////// FUNÇÃO PARA FAZER O GLCM ////////////

void GLCM(char stringg[],int *V){



    FILE *LER;

    LER = fopen("stringg","r");
    int *GLCM;
    int **p;
    int i,j,N=1025,D=256;


    ////////////////////////////////////
        int M1[256][256]={};//// DIREITA
        int M2[256][256]={};//// DIAGONAL INFERIOR DIREITA
        int M3[256][256]={};//// BAIXO
        int M4[256][256]={};//// DIAGONAL INFERIOR ESQUERDA
        int M5[256][256]={};//// ESQUERDA
        int M6[256][256]={};//// DIAGONAL SUPERIOR ESQUERDA
        int M7[256][256]={};//// CIMA
        int M8[256][256]={};//// DIAGONAL SUPERIOR DIREITA
    ////////////////////////////////////


    /////////////////////////////////////
    GLCM=(int*) calloc(D , sizeof(int));
    p=(int **) malloc(N * sizeof(int *));

    /////////////////////////////////////



    for(i=0;i<N;i++){
        p[i]=(int*) malloc(N* sizeof(int));
        for(j=0;j<N;j++){

            fscanf(LER," %d ;",&p[i][j]);


        }
      }

    fclose(LER);
    //////////////////////// LEITURA DO ARQUIVO ///////////////////

    int A=0,B=0;
////////////////// DIREITA /////////////////
    for(i=0;i<N-1;i++){
        for(j=0;j<N-1;j++){
            A=p[i][j];
            B=p[i][j+1];
            M1[A][B]++;
            A=0;
            B=0;
        }
    }

    float HOMO=0,AUX;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M1[i][j];
            HOMO+=((AUX)/(1+abs(i-j)));
        }
    }

    AUX=0;
    float ENERGY=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M1[i][j];
            ENERGY+=pow(AUX,2);
        }
    }

    AUX=0;
    float CONTRAS=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M1[i][j];
            CONTRAS+=pow(i-j,2)*AUX;
        }
    }

    V[0]=HOMO;
    V[1]=ENERGY;
    V[2]=CONTRAS;

////////////////////////// END M1 ////////////////////////////////


//////////////// DIAGONAL INFERIOR DIREITA //////////////////////
    for(i=0;i<N-1;i++){
        for(j=0;j<N-1;j++){
            A=p[i][j];
            B=p[i+1][j+1];
            M2[A][B]++;
            A=0;
            B=0;
        }
    }

    HOMO=0,AUX=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M2[i][j];
            HOMO+=((AUX)/(1+abs(i-j)));
        }
    }

    AUX=0;
    ENERGY=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M2[i][j];
            ENERGY+=pow(AUX,2);
        }
    }

    AUX=0;
    CONTRAS=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M2[i][j];
            CONTRAS+=pow(i-j,2)*AUX;
        }
    }

    V[3]=HOMO;
    V[4]=ENERGY;
    V[5]=CONTRAS;

////////////////////////// END M2 ////////////////////////////////

////////////////////////// BAIXO ////////////////////////////////
    for(i=0;i<N-1;i++){
        for(j=0;j<N-1;j++){
            A=p[i][j];
            B=p[i+1][j];
            M3[A][B]++;
            A=0;
            B=0;
        }
    }

    HOMO=0,AUX=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M3[i][j];
            HOMO+=((AUX)/(1+abs(i-j)));
        }
    }

    AUX=0;
    ENERGY=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M3[i][j];
            ENERGY+=pow(AUX,2);
        }
    }

    AUX=0;
    CONTRAS=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M3[i][j];
            CONTRAS+=pow(i-j,2)*AUX;
        }
    }

    V[6]=HOMO;
    V[7]=ENERGY;
    V[8]=CONTRAS;

////////////////////////// END M3 ////////////////////////////////

/////////////// DIAGONAL INFERIOR ESQUERDA //////////////////////
    for(i=1;i<N;i++){
        for(j=1;j<N;j++){
            A=p[i][j];
            B=p[i+1][j-1];
            M4[A][B]++;
            A=0;
            B=0;
        }
    }

    HOMO=0,AUX=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M4[i][j];
            HOMO+=((AUX)/(1+abs(i-j)));
        }
    }

    AUX=0;
    ENERGY=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M4[i][j];
            ENERGY+=pow(AUX,2);
        }
    }

    AUX=0;
    CONTRAS=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M4[i][j];
            CONTRAS+=pow(i-j,2)*AUX;
        }
    }

    V[9]=HOMO;
    V[10]=ENERGY;
    V[11]=CONTRAS;

////////////////////////// END M4 ////////////////////////////////

//////////////////////// ESQUERDA ///////////////////////////////
    for(i=1;i<N;i++){
        for(j=1;j<N;j++){
            A=p[i][j];
            B=p[i][j-1];
            M5[A][B]++;
            A=0;
            B=0;
        }
    }

    HOMO=0,AUX=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M5[i][j];
            HOMO+=((AUX)/(1+abs(i-j)));
        }
    }

    AUX=0;
    ENERGY=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M5[i][j];
            ENERGY+=pow(AUX,2);
        }
    }

    AUX=0;
    CONTRAS=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M5[i][j];
            CONTRAS+=pow(i-j,2)*AUX;
        }
    }

    V[12]=HOMO;
    V[13]=ENERGY;
    V[14]=CONTRAS;

////////////////////////// END M5 ////////////////////////////////

/////////////// DIAGONAL SUPERIOR ESQUERDA////////////////////////
    for(i=1;i<N;i++){
        for(j=1;j<N;j++){
            A=p[i][j];
            B=p[i-1][j-1];
            M6[A][B]++;
            A=0;
            B=0;
        }
    }

    HOMO=0,AUX=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M6[i][j];
            HOMO+=((AUX)/(1+abs(i-j)));
        }
    }

    AUX=0;
    ENERGY=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M6[i][j];
            ENERGY+=pow(AUX,2);
        }
    }

    AUX=0;
    CONTRAS=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M6[i][j];
            CONTRAS+=pow(i-j,2)*AUX;
        }
    }

    V[15]=HOMO;
    V[16]=ENERGY;
    V[17]=CONTRAS;

////////////////////////// END M6 ////////////////////////////////

////////////////////////// CIMA //////////////////////////////////
    for(i=1;i<N;i++){
        for(j=1;j<N;j++){
            A=p[i][j];
            B=p[i-1][j];
            M7[A][B]++;
            A=0;
            B=0;
        }
    }

    HOMO=0,AUX=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M7[i][j];
            HOMO+=((AUX)/(1+abs(i-j)));
        }
    }

    AUX=0;
    ENERGY=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M7[i][j];
            ENERGY+=pow(AUX,2);
        }
    }

    AUX=0;
    CONTRAS=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M7[i][j];
            CONTRAS+=pow(i-j,2)*AUX;
        }
    }

    V[18]=HOMO;
    V[19]=ENERGY;
    V[20]=CONTRAS;

////////////////////////// END M7 ////////////////////////////////

/////////////// DIAGONAL SUPERIOR DIREITA ////////////////////////
    for(i=0;i<N-1;i++){
        for(j=0;j<N-1;j++){
            A=p[i][j];
            B=p[i-1][j+1];
            M8[A][B]++;
            A=0;
            B=0;
        }
    }

    HOMO=0,AUX=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M8[i][j];
            HOMO+=((AUX)/(1+abs(i-j)));
        }
    }

    AUX=0;
    ENERGY=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M8[i][j];
            ENERGY+=pow(AUX,2);
        }
    }

    AUX=0;
    CONTRAS=0;
    for(i=0;i<D;i++){
        for(j=0;j<D;j++){
            AUX=M8[i][j];
            CONTRAS+=pow(i-j,2)*AUX;
        }
    }

    V[21]=HOMO;
    V[22]=ENERGY;
    V[23]=CONTRAS;

////////////////////////// END M8 ////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
    // LIBERAR MEMORIA DA MATRIZ //
    for(i=0;i<N;i++){
        free(p[i]);
    }
    free(p);
   ////////////////////////////////

    return;
}
