#include <stdlib.h>
#include <stdio.h>
#include "func.h"
#include <string.h>
#include <unistd.h>

//Nomes Pedro Henrique de Limaa Malaquias -- 17/0020525
//Nome Caetano Santos Lucio -- 180144979



int main(void){
  int opcao;
  //Ponteriro  para a struct
  contato *GO;
  //criacao do primeiro elementeo da lista
  GO=cria_lista();
  GO=arquivo(GO);


  while(1){
        menu();
        scanf("%d",&opcao);
        if(opcao==5){
             printf("SAI!!!\n");
            break;
        }else if(opcao>5 || opcao<0){
            printf("\nOpcao invalida!!!\n");
            system("cls");
        }else{
                switch(opcao){
                case 1:
                //Inserir novo contato
                printf("1\n");
                add_Contato(GO);
                break;

                case 2:
                //Remover contato
                apagar_contato(GO);
                GO=arquivo(GO);
                break;

                case 3:
                //Visualizar contato
                procurar_contato(GO);
                printf("3\n");
                break;

                case 4:
                //Visualizar todos os contato
                GO=arquivo(GO);
                show(GO);
                break;

                default:
                printf("Insira opcao validas\n");
                break;
            }
        }

    }

    return 0;
}
