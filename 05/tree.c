/// Projeto 5

/// UnB - Universidade de Brasília
/// ED1 - Estruturas de Dados 1
/// Turma A - 2019/1
/// Prof. Mateus Mendelson

/// Alunos:
/// Caetano Santos Lucio - 18/0144979
/// Pedro Henrique de Lima Malaquias - 17/0020525

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "tree.h"


typedef struct Node Nodes;

struct Node {
    Nodes *pntEsq, *pntDir;
    int aux;
    int height;
    int element;int parent_dir;
    char nick[11];
};


Tree *loadTreeFromFile(char filename[100]){
  FILE *fp;
  Tree* raiz = (Tree*)(malloc(sizeof(Tree)));
  Tree* old_node, *new_galho;
  int number, place_not_found;
  char space;

  fp = fopen(filename, "r");
  if(fp == NULL){
    printf("Arquivo nao encontrado\n");
  }

  fscanf(fp, "%d%c", &raiz->value, &space);
  raiz->peq = NULL;
  raiz->grande = NULL;
  

  while(!feof(fp)){
    new_galho = (Tree*)(malloc(sizeof(Tree)));
    fscanf(fp, "%d%c", &new_galho->value, &space);
    new_galho->peq = NULL;
    new_galho->grande = NULL;

    old_node = raiz;

    int place_not_found = 1;

    while(place_not_found){
      if(new_galho->value > old_node->value){
        if(old_node->grande == NULL){
          old_node->grande = new_galho;
          place_not_found = 0;
          
        }else{
          old_node = old_node->grande;
        }
      }else{
        if(old_node->peq == NULL){
          old_node->peq = new_galho;
          place_not_found = 0;
          
        }else{
          old_node = old_node->peq;
        }
      }
    }
  }
  return raiz;
}

void retornoo(){
  system("pause");
  printf("\nPrecione qualquer tecla para RETORNAR!\n");
  getchar();
}

Tree *find_min(Tree *t) {
    if (t == NULL) {
        return NULL;
    }
    else if (t->peq == NULL) {
        return t;
    }
    else {
        return find_min(t->peq);
    }
}

Tree *find_max(Tree *t) {
    if (t == NULL) {
        return NULL;
    }
    else if (t->grande == NULL) {
        return t;
    }
    else {
        return find_max(t->grande);
    }
}

Tree *find(int elem, Tree *t) {
    if (t == NULL) {
        return NULL;
    }

    if (elem < t->value) {
        return find(elem, t->peq);
    }
    else if (elem > t->value) {
        return find(elem, t->grande);
    }
    else {
        return t;
    }
}

int gap = 3;

int print_next;

Nodes *constru_arv(Tree *t) {
    Nodes *node;

    if (t == NULL) return NULL;

    node = malloc(sizeof(Nodes));
    node->pntEsq = constru_arv(t->peq);
    node->pntDir = constru_arv(t->grande);

    if (node->pntEsq != NULL) {
        node->pntEsq->parent_dir = -1;
    }

    if (node->pntDir != NULL) {
        node->pntDir->parent_dir = 1;
    }

    sprintf(node->nick, "%d", t->value);
    node->element = strlen(node->nick);

    return node;
}

Nodes *build_ascii_tree(Tree *t) {
    Nodes *node;
    if (t == NULL){
      return NULL;
    }
    node = constru_arv(t);
    node->parent_dir = 0;
    return node;
}

void free_ascii_tree(Nodes *node) {
    if (node == NULL) return;
    free_ascii_tree(node->pntEsq);
    free_ascii_tree(node->pntDir);
    free(node);
}

////////////////////////////////////////////////////

int esqpro[1000];
int dirpro[1000];


int maximum(int x, int y) {
  if(x > y){
    return x;
  }else{
    return y;
  }
}

int minimum(int x, int y) {
  if(x < y){
    return x;
  }else{
    return y;
  }
}

void inicio(Tree *raiz){
  int value;
  menu();
  scanf("%d", &value);
  switch (value){
  	case 1:
      newArv();
    break;

    case 2:
      system("clear");
      printf("\n");
      showTree(raiz);
      retornoo();
      inicio(raiz);
     	break;

    case 3:
      system("clear");
  	  isFull(raiz);
      retornoo();
      inicio(raiz);
      break;

    case 4:
      system("clear");
      int number;
      printf("\nDigite o valor a ser buscado: ");
      scanf("%d", &number);
      printf("\n");
      searchValue(raiz,number);
      retornoo();
      inicio(raiz);
      break;

    case 0:
    	system("clear");
    	exit(-1);
     	break;

    default :
      printf ("Por favor, insira uma opcao valida\n");
      getchar();
      sleep(2);
      inicio(raiz);
      break;
    }
}

void esqpro_process(Nodes *node, int x, int y) {
    int i, esqq;
    if (node == NULL) return;
    esqq = (node->parent_dir == -1);
    esqpro[y] = minimum(esqpro[y], x - ((node->element - esqq) / 2));
    if (node->pntEsq != NULL) {
        for (i = 1; i <= node->aux && y + i < 1000; i++) {
            esqpro[y + i] = minimum(esqpro[y + i], x - i);
        }
    }
    esqpro_process(node->pntEsq, x - node->aux - 1, y + node->aux + 1);
    esqpro_process(node->pntDir, x + node->aux + 1, y + node->aux + 1);
}

void dirpro_process(Nodes *node, int x, int y) {
    int i, notleft;
    if (node == NULL){
      return;
    }
    notleft = (node->parent_dir != -1);
    dirpro[y] = maximum(dirpro[y], x + ((node->element - notleft) / 2));
    if (node->pntDir != NULL) {
        for (i = 1; i <= node->aux && y + i < 1000; i++) {
            dirpro[y + i] = maximum(dirpro[y + i], x + i);
        }
    }
    dirpro_process(node->pntEsq, x - node->aux - 1, y + node->aux + 1);
    dirpro_process(node->pntDir, x + node->aux + 1, y + node->aux + 1);
}

void filledge(Nodes *node) {
    int h, hmin, i, delta;
    if (node == NULL){
      return;
    }
    filledge(node->pntEsq);
    filledge(node->pntDir);

    if (node->pntDir == NULL && node->pntEsq == NULL) {
        node->aux = 0;
    }else {
        if (node->pntEsq != NULL) {
            for (i = 0; i < node->pntEsq->height && i < 1000; i++) {
                dirpro[i] = -(1<<20);
            }
            dirpro_process(node->pntEsq, 0, 0);
            hmin = node->pntEsq->height;
        }else {
            hmin = 0;
        }
        if (node->pntDir != NULL) {
            for (i = 0; i < node->pntDir->height && i < 1000; i++) {
                esqpro[i] = (1<<20);
            }
            esqpro_process(node->pntDir, 0, 0);
        }
        else {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++) {
            delta = maximum(delta, gap + 1 + dirpro[i] - esqpro[i]);
        }
        if (((node->pntEsq != NULL) ||
             (node->pntDir != NULL)) && delta > 4) {
            delta--;
        }
        node->aux = ((delta + 1) / 2) - 1;
    }
    h = 1;
    if (node->pntEsq != NULL) {
        h = maximum(node->pntEsq->height + node->aux + 1, h);
    }
    if (node->pntDir != NULL) {
        h = maximum(node->pntDir->height + node->aux + 1, h);
    }
    node->height = h;
}

void printLevel(Nodes *node, int x, int level) {
    int i, esqq;
    if (node == NULL) return;
    esqq = (node->parent_dir == -1);
    if (level == 0) {
        for (i = 0; i < (x - print_next - ((node->element - esqq) / 2)); i++) {
            printf(" ");
        }
        print_next += i;
        printf("%s", node->nick);
        print_next += node->element;
    }
    else if (node->aux >= level) {
        if (node->pntEsq != NULL) {
            for (i = 0; i < (x - print_next - (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node->pntDir != NULL) {
            for (i = 0; i < (x - print_next + (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    }
    else {
        printLevel(node->pntEsq,
                   x - node->aux - 1,
                   level - node->aux - 1);
        printLevel(node->pntDir,
                   x + node->aux + 1,
                   level - node->aux - 1);
    }
}

void showTree(Tree *t) {
    Nodes *praiz;
    int xmin, i;
    if (t == NULL){
      return;
    }
    praiz = build_ascii_tree(t);
    filledge(praiz);
    for (i = 0;i < 1000; i++) {
        esqpro[i] = (1<<20);
    }
    
    esqpro_process(praiz, 0, 0);
    xmin = 0;
    for (i = 0;i < 1000; i++) {
        xmin = minimum(xmin, esqpro[i]);
    }
    for (i = 0; i < praiz->height; i++) {
        print_next = 0;
        printLevel(praiz, -xmin, i);
        printf("\n");
    }
    free_ascii_tree(praiz);
}

void isFull(Tree* raiz){
  int number_of_elements, height;
  
  number_of_elements = pow(2, height) - 1;

  if (number_of_elements == Eelementos(raiz)) {
    printf("\nSim\n");
  }else{
    printf("\nNao\n");
  }
}

int Eelementos(Tree* galho){
  if(galho == NULL){
    return 0;
  }else if(galho->peq == NULL && (galho->grande)){
    return 1;
  } else {
    return 1 + Eelementos(galho->peq) + Eelementos(galho->grande);
  }
}

void searchValue(Tree* raiz, int value){
  Tree *galho = raiz;
  Tree *pai = NULL, *bro = NULL;
  int not_found = 1;

  while(not_found){
    if(value == galho->value){
      not_found = 0;
      if (pai == NULL) {
        printf("Elemento raiz\n");
      }else{
        printf("Pai: %d\n", pai->value);
        if(pai->peq != NULL && (pai->grande != NULL)){
          printf("Irmao: %d\n", bro->value);
        }
      }

    }else if (value > galho->value) {
      if (galho->grande == NULL) {
        printf("O valor nao esta presente na arvore\n");
        not_found = 0;
      }else{
        pai = galho;
        bro = galho->peq;
        galho = galho->grande;
      }
    }else{
      if(galho->peq == NULL){
        printf("O valor nao esta presente na arvore\n");
        not_found = 0;
      }else{
        pai = galho;
        bro = galho->grande;
        galho = galho->peq;
      }
    }
  }
}


Tree * Back_set(Tree *raiz){
  Tree *grandpa, *pai, *kid;

  while (raiz->peq != NULL) {
    raiz = dir_rot(NULL, raiz, raiz->peq);
  }

  grandpa = raiz;
  pai = raiz->grande;

  while (pai->grande != NULL) {
    grandpa = raiz;
    pai = raiz->grande;

    while ((pai->peq == NULL) && (pai->grande !=NULL)) {
      grandpa = grandpa->grande;
      pai = pai->grande;
    }

    while(pai->peq != NULL) {
      pai = dir_rot(grandpa, pai, pai->peq);
    }
  }
  return raiz;
}

Tree* dir_rot(Tree *grandpa, Tree *pai, Tree *kid){

  if (grandpa != NULL) {
    grandpa->grande = kid;
  }

  pai->peq = kid->grande;
  kid->grande = pai;

  return kid;
}


Tree* esq_rot(Tree *grandpa, Tree *pai, Tree *kid, Tree *raiz){
  kid->peq = pai;
  pai->grande = NULL;

  if (grandpa != NULL) {
    if (grandpa->peq == pai) {
      grandpa->peq = kid;
    }else{
      grandpa->grande = kid;
    }
  }

  if (pai == raiz) {
    raiz = kid;
  }
  return raiz;
}

void menu() {
  system("clear");
  printf("\n---------ARVORES BINARIAS--------\n");
  printf("1 - Carregar do arquivo\n");
  printf("2 - Mostrar arvore\n");
  printf("3 - Mostrar se esta cheia ou nao\n");
  printf("4 - Buscar valor\n");
  printf("0 - Sair\n");
  printf("---------------------------------\n");
}

void newArv(){
  Tree *new_tree;
  int X;
  system("clear");
  printf("Selecione o ARQUIVO\n\n");
  printf("Escolha de 1 a 6: ");
  scanf("%d", &X);
  switch (X) {
    case 1:
      new_tree = loadTreeFromFile("BSTs/bst1.txt");
      inicio(new_tree);
      break;
    case 2:
      new_tree = loadTreeFromFile("BSTs/bst2.txt");
      inicio(new_tree);
      break;
    case 3:
      new_tree = loadTreeFromFile("BSTs/bst3.txt");
      inicio(new_tree);
      break;
    case 4:
      new_tree = loadTreeFromFile("BSTs/bst4.txt");
      inicio(new_tree);
      break;
    case 5:
      new_tree = loadTreeFromFile("BSTs/bst5.txt");
      inicio(new_tree);
      break;
    case 6:
      new_tree = loadTreeFromFile("BSTs/bst6.txt");
      inicio(new_tree);
      break;
    default :
      printf ("\nPor favor, insira uma opcao valida\n");
      getchar();
      sleep(2);
      newArv();
      break;
  }
}