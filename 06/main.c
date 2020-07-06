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

#define qtd_ent  535
#define qtd_prox 535

int main(int argc, char *argv[ ]){

    ALEATORIOS();

    FILE *TESTE1;
    FILE *TESTE2;
    FILE *TREAL01;
    FILE *TREAL02;

    float VETesteAs2[536]={};
    float VETesteGr2[536]={};
    int *T1,*T2;
    int W=536;
    int Q=24;
    ////////////////////// ENDERE�OS ///////////////////////
    int *edA=(int*) calloc(W,sizeof(int));//////////////////
    int *edG=(int*) calloc(W,sizeof(int));//////////////////
    int *metricasA=(int*) calloc(Q,sizeof(int));////////////
    int *metricasG=(int*) calloc(Q,sizeof(int));////////////
    /////////// ALOCANDO OS VETORES DE TREINAMENTO //////////

    int refe[536];// Vai virar ponteiro
    char MTA[25][100];
    char MTG[25][100];
    char enderecoTXT[100];
    int i,j;
    ///////////// PEGANDO O ENDERE�O DOS TXT ///////////
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Desenvolvimento da parte NEURAL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct neuronio 
{    
    float entrada[qtd_ent];    
    float peso;                
    float valor;               
    int layers;                
    int posicao;               
    struct neuronio *prox[qtd_prox]; 
}NEO[535];

typedef struct neuronio Neuronio;

int qtd_neu_entrada = 535;
int qtd_neu_layers_Oc = 1;      
int qtd_layers_Oc   = 1;    
int qtd_neu_saida   = 1; 
int qtd_neu_total = (qtd_neu_entrada+qtd_neu_saida+(qtd_layers_Oc*qtd_neu_layers_Oc)); 
int neu_penult_layers = qtd_neu_entrada + ((qtd_layers_Oc - 1)* qtd_neu_layers_Oc); 
   

float randon() 
{          
     float a = 0;
     a = rand()%100+1; 
     a = a/100; //Teste! Mudar depois
     return (a);      
}    

void Inicializa(int qtd_neu_layers_Oc) 
{
     for(int x=0; x<qtd_neu_total; x++)  
     {
          NEO[x].peso = randon();
          NEO[x].valor = 0;
          NEO[x].posicao = x;           
          for (int y=0;y<qtd_ent;y++)   
               NEO[x].entrada[y] = 0;
          for (int z=0;z<qtd_prox;z++)  
               NEO[x].prox[z] = 0;
               
     }

     
     
     
     int a, b; 
     for(a=0;a<qtd_neu_total;a++) 
     {
          for(b=0;b<(qtd_layers_Oc+2);b++) 
          {
               if(a<(qtd_neu_entrada+(b*qtd_neu_layers_Oc))) 
               {
                    NEO[a].layers = b;   
                    b=(qtd_layers_Oc+2); 
               }
          }      
     }
}

void Conect ()
{
          int i, j, cont_layers; 
          
          for(i=0; i<(qtd_neu_total-qtd_neu_saida); i++) 
          {
               cont_layers = NEO[i].layers;  
               if(i<qtd_neu_entrada) 
                   j=qtd_neu_entrada;
               else if (i<neu_penult_layers) 
                        j = qtd_neu_entrada + (cont_layers*qtd_neu_layers_Oc); 
                    else 
                        j = qtd_neu_total-qtd_neu_saida;
               int k=-1;  
               do
               {      
                    k++;   
                    NEO[i].prox[k] = &NEO[j]; 
                    j++;
               }while (NEO[i].prox[k]->layers == NEO[j].layers);
          }       
} 

void Gera_resultado(int r)
{
     int cont = 0;
     float soma = 0;
     float media = 0;     
     for (int g=0; ((g<qtd_ent)&&(NEO[r].entrada[g]!=0)); g++) 
     {
         soma = soma + (NEO[r].entrada[g] * log(NEO[r].entrada[g]) * NEO[r].peso); 
         cont = cont + 1;
     }
     media = soma/cont;
     NEO[r].valor = media;
}

void Atribue_entrada(int w)
{
     int pos = 0; 
     for (int k=0; ((k<qtd_prox)&&(NEO[w].prox[k]!=NULL)); k++)  
     {
         if(w<qtd_neu_entrada) 
             pos=w;
         else     
             pos =  NEO[w].posicao - ((NEO[w].layers-1)*qtd_neu_layers_Oc + qtd_neu_entrada);
         NEO[w].prox[k]->entrada[pos] = NEO[w].valor;
     }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


  
  ///// DAQUI PRA BAIXO É A REDE NEURAL ////
    srand(time(NULL)); 
      char *valor = argv[1];
      int input = atoi(valor);

    Inicializa(input);
    Conect();       

    return 0;
}
