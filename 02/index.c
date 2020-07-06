#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "ALEATORIOS.h"
#include "LMATRIZ.h"
#include "normalizador.h"
#include "GLCM.h"
////Nomes/matriculas
////Pedro Henrique de Lima 17/002052
////Caetano Santos Lucio 18/0144979
//// Turma A


int main(){

    ALEATORIOS();

    FILE *TESTE1;
    FILE *TESTE2;
    //////////////////
    FILE *TREAL01;
    FILE *TREAL02;



    float VETesteAs2[536]={};
    float VETesteGr2[536]={};
    int *T1,*T2;
    int W=536;
    int Q=24;
    ////////////////////// ENDEREÇOS ///////////////////////
    int *edA=(int*) calloc(W,sizeof(int));//////////////////
    int *edG=(int*) calloc(W,sizeof(int));//////////////////
    int *metricasA=(int*) calloc(Q,sizeof(int));////////////
    int *metricasG=(int*) calloc(Q,sizeof(int));////////////
    /////////// ALOCANDO OS VETORES DE TREIAMENTO //////////




    int refe[536];// Vai virar ponteiro
    char MTA[25][100];
    char MTG[25][100];
    char enderecoTXT[100];
    int i,j;
    ///////////// PEGANDO O ENDEREÇO DOS TXT ///////////
    TESTE1=fopen("asfanT.txt","r");
    for(i=0;i<25;i++){
        fscanf(TESTE1,"%s",MTA[i]);
    }

    TESTE2=fopen("gramaT.txt","r");
    for(i=0;i<25;i++){
        fscanf(TESTE2,"%s",MTG[i]);
    }
    //////////////////////////////////////////////////

    for(i=0;i<25;i++){////VETOR DE TREINAMENTO DE ASPHALTO
        strcpy(enderecoTXT,MTA[i]);
        ILDPP(enderecoTXT,edA);
            for(j=0;j<512;j++){
                VETesteAs2[j]+=edA[j];
            }

        GLCM(enderecoTXT,metricasA);
            for(j=512;j<536;j++){
                VETesteAs2[j]+=metricasA[j];
            }
    }
    media(VETesteAs2);
    normalizador(VETesteAs2);

     for(i=0;i<25;i++){////VETOR DE TREINAMENTO DE GRAMA
        strcpy(enderecoTXT,MTG[i]);
        ILDPP(enderecoTXT,edG);
            for(j=0;j<512;j++){
                VETesteGr2[j]+=edG[j];
            }
        GLCM(enderecoTXT,metricasA);
            for(j=512;j<536;j++){
                VETesteGr2[j]+=metricasG[j];
            }
    }
    media(VETesteGr2);
    normalizador(VETesteGr2);

    //////// APENAS A PARTE DO TREINAMENTTO//
    //////// INCOMPLETO /////////////////////
    /////////////////////////////////////////

    return 0;
}
