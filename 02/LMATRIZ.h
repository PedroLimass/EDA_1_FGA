#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//////// FUNÇÃO PARA FAZER O ILDP ////////

void ILDPP(char stringg[],int *vetor){



    FILE *LER;

    LER = fopen("stringg","r");
    int *ILDP;
    int **p;
    int i,j,N=1025,D=512;
    int R[3][3]={};
    int BIN[3][3]={};
    int l,c,x,y;
    int mov=0;

    /////////////////////////////////////
    ILDP=(int*) calloc(D , sizeof(int));
    p=(int **) malloc(N * sizeof(int *));

    /////////////////////////////////////

    for(i=0;i<N;i++){
        p[i]=(int*) malloc(N* sizeof(int));
        for(j=0;j<N;j++){

            fscanf(LER," %d ;",&p[i][j]);


        }
      }

    fclose(LER);


    for(i=1;i<N-1;i++){
        for(j=1;j<N-1;j++){
                R[1][1]=p[i][j]; ////<---- PX central!
                ////////////////////
                R[0][0]=p[i-1][j-1];
                R[0][1]=p[i-1][j];
                R[0][2]=p[i-1][j+1];

                R[1][0]=p[i][j-1];
                R[1][2]=p[i][j+1];

                R[2][0]=p[i+1][j-1];
                R[2][1]=p[i+1][j];
                R[2][2]=p[i+1][j+1];

                int SOMA=0;
                float MEDIA=0;

                for(x=0;x<3;x++){
                    for(y=0;y<3;y++){
                        SOMA+=R[x][y];
                    }
                }


                MEDIA+=SOMA/9.0;

                for(l=0;l<3;l++){
                    for(c=0;c<3;c++){
                        if(R[l][c]>=MEDIA){
                            BIN[l][c]=1;
                        }else if(R[l][c]<MEDIA){
                            BIN[l][c]=0;
                        }
                    }
                }


                char V[10]={},Q=0;
                for(x=0;x<3;x++){
                    for(y=0;y<3;y++){
                        V[Q]=BIN[x][y];
                        Q++;
                    }
                }


            int G[9]={},H=0;
            int T=9;
            while(T!=0){
                    unsigned int dc = 0;
                    int u = 0;
                    int s;
                    s = 9;
                    while( s-- ) {
                        if( V[s] == 0 || V[s] == 1 ) {
                            dc = dc + pow(2, u++) * (V[s] -0);
                        }
                    }
                     G[H]=dc;
                    ////printf("\nDec: %u\n", dc); VIZUALIZAR OS DECIMAIS 1 BY 1!


                    //// ROTAÇÃO DOS DECIMAIS ////
                        int aux;
                        aux=V[8];
                        for(x=8;x>0;x--){
                            V[x]=V[x-1];
                        }
                        V[0]=aux;
                    /////////////////////////////


                H++;
                T--;
            }


            //// Bubble Sort para pegar o menor valor dos decimais ////
                int aux=0;
                for(x=0;x<9;x++){
                    for(y=x+1;y<9;y++){
                        if(G[x]>G[y]){
                            aux=G[x];
                            G[x]=G[y];
                            G[y]=aux;

                        }
                    }
                }

                //// TESTE DO VETOR ORDENADO////
                /*for(x=0;x<9;x++){
                    printf("%d ",G[x]);
                }*/
                ////////////////////////////////

             //////// ATRIBUINDO O INCREMENTO NA POSIÇÃO ////////
             int F=0;
             F=G[0];
           ////  printf("\n ildep:%d\n",F);

             ILDP[F]+=1;


             ///////////////////////////////////////////////////



        }
    }

    for(x=0;x<512;x++){
             vetor[x]=ILDP[x];
             }


    // LIBERAR MEMORIA DA MATRIZ //
    for(i=0;i<N;i++){
        free(p[i]);
    }
    free(p);
    free(ILDP);
   ////////////////////////////////

    return;
}
