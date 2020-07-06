#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct aeronave {
	char codigo_de_voo[7];
	char AorD;
	int combustivel;
	int prioridade;
	struct aeronave *prox;
}aviao;

typedef struct Fila {
	struct aeronave *ini;
	struct aeronave *fim;
}fila;

void cria_arquivo_codigos_voo();

void NAproximacoes_NDecolagens(int *aprox, int *dec);
int NVoos(int naprox, int ndec);
char *ordem_AandD(int nvoos, int naprox, int ndec, char *lista_voos);

void inicia(fila *stack);
void adiciona(fila *stack, FILE *p, char c);
void remove_fila(fila *stack);

int reduz_combustivel(fila *stack, FILE *p);

void ordena_por_prioridade(fila *stack);