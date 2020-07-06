/// Projeto 5

/// UnB - Universidade de Brasília
/// ED1 - Estruturas de Dados 1
/// Turma A - 2019/1
/// Prof. Mateus Mendelson

/// Alunos:
/// Caetano Santos Lucio - 18/0144979
/// Pedro Henrique de Lima Malaquias - 17/0020525

#ifndef _TREE_H_
#define _TREE_H_

typedef struct tree {
  int value;
  int height;
  struct tree* peq;
  struct tree* grande;
} Tree;

int getLevel(Tree*, int);

void newArv();

Tree *loadTreeFromFile(char[100]);

Tree* Back_set(Tree *);

void showTree(Tree*);

void isFull(Tree*);

void retornoo();

void inicio(Tree *raiz);

void searchValue(Tree*, int);

Tree * removeValue(Tree*, int);

int Eelementos(Tree*);

Tree* dir_rot(Tree *, Tree *, Tree *);
Tree* esq_rot(Tree *, Tree *, Tree *, Tree*);


void menu();

#endif
