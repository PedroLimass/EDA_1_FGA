#include <stdlib.h>
#include <stdio.h>
#include <time.h>
/////////// FUN��O PARA GERA OS ENRE�OES EM UM ARQUIVO/////
/////////// ESSA FUN��O E CHAMADA NO INDEX ////////////////
void ALEATORIOS(void){

  FILE *asfanT;
  FILE *asfanV;
  FILE *gramaT;
  FILE *gramaV;

  asfanT = fopen("asfanT.txt","w");
  asfanV = fopen("asfanV.txt","w");
  gramaT = fopen("gramaT.txt","w");
  gramaV = fopen("gramaV.txt","w");

  int A[25],B[25],X[50];
  int i,j,H;
  int x,y,aux,W;




    srand((unsigned) time(NULL));

for(W=1;W<=2;W++){

         for(i=0;i<50;i++){
            do{
                X[i]=(rand()%50)+1;
                H=0;

                for(j=0;j<i;j++){
                    if(X[i]==X[j]){
                        H=1;
                        break;
                    }
                }
            }while(H);
         }


            for(j=0;j<25;j++){
                A[j]=X[j];
            }

            int k=25;
            for(j=0;j<25;j++){
                    if(k==50){
                        break;
                    }else{
                        B[j]=X[k];
                    }
            k++;
            }
             ///////////////////////////////////////////////////////

             if(W==1){
                    for(i=0;i<25;i++){
                        if(A[i]<10){
                             fprintf(asfanT,"DataSet\\\\asphalt\\\\asphalt_0%d.txt\n",A[i]);
                        }else{
                            fprintf(asfanT,"DataSet\\\\asphalt\\\\asphalt_%d.txt\n",A[i]);
                        }
                    }
                    for(i=0;i<25;i++){
                        if(B[i]<10){
                            fprintf(asfanV,"DataSet\\\\asphalt\\\\asphalt_0%d.txt\n",B[i]);
                        }else{
                            fprintf(asfanV,"DataSet\\\\asphalt\\\\asphalt_%d.txt\n",B[i]);
                        }
                    }
                    fclose(asfanT);
                    fclose(asfanV);
            //////////////////////////////////// GRAMA /////////////
             }else if(W==2){
                    for(i=0;i<25;i++){
                        if(A[i]<10){
                            fprintf(gramaT,"DataSet\\\\grass\\\\grass_0%d.txt\n",A[i]);
                        }else{
                            fprintf(gramaT,"DataSet\\\\grass\\\\grass_%d.txt\n",A[i]);
                        }
                    }

                    for(i=0;i<25;i++){
                         if(B[i]<10){
                            fprintf(gramaV,"DataSet\\\\grass\\\\grass_0%d.txt\n",B[i]);
                         }else{
                            fprintf(gramaV,"DataSet\\\\grass\\\\grass_%d.txt\n",B[i]);
                         }
                    }
                    fclose(gramaT);
                    fclose(gramaV);
             }

    }

    return;
}
