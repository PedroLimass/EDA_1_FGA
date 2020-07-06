#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define ARQUI "contatos.txt";

typedef struct Contato{
  char nome[101];
  char telefone[11];
  char endereco[101];
  unsigned int cep;
  char data[11];
  struct Contato *proximo;
  struct Contato *anterior;
}contato;

//Criancao da cria_lista
contato *cria_lista();
//ler e add os elementos do arquivo na memoria
contato *arquivo(contato *ponto);
///->funcao linkada a arquivo
contato *add_arquivo(contato *ponto, FILE *p);
//Printar contatos
void show(contato *ponto);
//Menu
void menu();
//Add NOVO CONTATO
contato *add_Contato(contato *);
//Procurar um contato
void procurar_contato(contato *ponto);
//Apagar contato
void apagar_contato(contato *ponto);
//novo arquivo/EXIT
//void novo_arq(contato *ponto);

//// MODULARIZADO DAQUI PRA CIMA ///
//Criaçao da lista
contato *cria_lista(){
    contato* li=(contato*)malloc(sizeof(contato));
    if(li!=NULL){
      li=NULL;
    }
    return li;
}


//Leitura de todo o arquivo.txt
contato *arquivo(contato *ponto){
  FILE *p;
  p=fopen("contatos.txt","a+");

    while(!feof(p)){
        ponto=add_arquivo(ponto,p);
    }
    return ponto;
}

//Leitura do arquivo e inserçao na memoria
contato *add_arquivo(contato *ponto,FILE *p){
    contato *novo=(contato*)malloc(sizeof(contato));
    fscanf(p,"%[^\n]",novo->nome);
    fgetc(p);
    fscanf(p,"%[^\n]",novo->telefone);
    fgetc(p);
    fscanf(p,"%[^\n]",novo->endereco);
    fgetc(p);
    fscanf(p,"%d",&novo->cep);
    fgetc(p);
    fscanf(p,"%[^\n]",novo->data);
    fgetc(p);

    if(ponto!= NULL){
      novo->proximo=ponto;
      novo->anterior=NULL;
      ponto->anterior=novo;
    }
    fgetc(p);
    fgetc(p);
  return novo;
}

//Mostra os contatos na lista
void show(contato *ponto){
  system("cls");
  contato *prov;

  for(prov=ponto;prov!=NULL;prov=prov->proximo){
      printf("Nome: %s\n", prov->nome);
      printf("Telefone: %s\n",prov->telefone);
      printf("Endereço: %s\n",prov->endereco);
      printf("CEP: %d\n",prov->cep);
      printf("Nascimendo: %s\n\n",prov->data);
  }
  system("pause");
}

//Menu
void menu(){
    system("cls");
    printf("\t============ AGENDA ============\n");
    printf("\t1)Inserir novo contato\n");
    printf("\t2)Remover contato\n");
    printf("\t3)Visualizar contato\n");
    printf("\t4)Visualizar todos os contato\n");
    printf("\t5)Sair\n");
    printf("\t================================\n");
}

//Add contato novo
contato *add_Contato(contato *ponto){
	contato *novo=(contato*)malloc(sizeof(contato));
	system("cls");
	printf("========= NOVO CONTATO =========\n\n");
	getchar();
	printf("Informe o Nome: ");
	scanf("%[^\n]", novo->nome);
	getchar();
	printf("Telefone (XXXXX-XXXX): ");
	scanf("%[^\n]", novo->telefone);
	getchar();
	printf("Endereço: ");
	scanf("%[^\n]", novo->endereco);
	getchar();
	printf("Digite o CEP (Max 5 digitos): ");
	scanf("%d", &novo->cep);
	getchar();
	printf("Digite o nascimento: ");
	scanf("%[^\n]", novo->data);
	getchar();
	if (ponto != NULL) {
		novo->proximo = ponto;
		novo->anterior = NULL;
		ponto->anterior = novo;
	}

	FILE *fp;
	fp=fopen("contatos.txt","a+");

		fprintf(fp, "%s\n",novo->nome);
		fprintf(fp, "%s\n",novo->telefone);
		fprintf(fp, "%s\n",novo->endereco);
		fprintf(fp, "%d\n",novo->cep);
		fprintf(fp, "%s\n",novo->data);
		fprintf(fp, "$\n");
	fclose(fp);

	printf("\nContato Adicionado com Sucesso!\n\n");
	system("pause");
}

//Procurar um Contato
void procurar_contato(contato *ponto){
	char nome[101];
	contato *procurado=ponto;
	system("cls");
	printf("========= PROCURAR CONTATO =========\n\n");
	printf("Nome: \n");
	getchar();
		scanf("%[^\n]",nome);
    system("cls");

	while(procurado!=NULL){
		if(!strcmp(procurado->nome,nome)){
			getchar();
			printf("Nome: %s\n",procurado->nome);
			printf("Telefone: %s\n",procurado->telefone);
			printf("Endereco: %s\n",procurado->endereco);
			printf("CEP: %d\n",procurado->cep);
			printf("Aniversario: %s\n",procurado->data);
			break;
		}else{
			procurado=procurado->proximo;
		}
	}
	printf("\n");
	system("pause");
}

void apagar_contato(contato *ponto){
	
	system("cls");

	char nome[101];
	contato *apagar=ponto,*vizinhos;

	printf("========= APAGAR CONTATO =========\n\n");
	printf("Nome: ");
	getchar();
		scanf("%[^\n]",nome);
    system("cls");

	while(apagar!=NULL){
		if(!strcmp(apagar->nome,nome)){
			getchar();
			strcpy(apagar->nome,"");
			strcpy(apagar->telefone,"");
			strcpy(apagar->endereco,"");
			strcpy(apagar->data,"");


			if(apagar->anterior!=NULL){
				vizinhos=apagar->anterior;
				vizinhos->proximo=apagar->proximo;
			}else if(apagar->anterior==NULL){
				ponto=apagar->proximo;
				ponto->anterior=NULL;
			}

				if(apagar->proximo!=NULL){
					vizinhos=apagar->proximo;
					vizinhos->anterior=apagar->anterior;
				}

			free(apagar);
			break;
		}else{
			apagar=apagar->proximo;
		}
		//FALTA REESCREVER O ARQUIVO SEM O INDIVIDO
	}
	//novo_arq(ponto);
	printf("\n");
	system("pause");
}

