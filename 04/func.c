#include "func.h"

void cria_arquivo_codigos_voo() {
	FILE *p = fopen("sequencia_de_voo.txt", "w");

	fprintf(p, "VG3001\nJJ4404\nLN7001\nTG1501\n");
	fprintf(p, "GL7602\nTT1010\nAZ1009\nAZ1008\n");
	fprintf(p, "AZ1010\nTG1506\nVG3002\nJJ4402\n");
	fprintf(p, "GL7603\nRL7880\nAL0012\nTT4544\n");
	fprintf(p, "TG1505\nVG3003\nJJ4403\nJJ4401\n");
	fprintf(p, "LN7002\nAZ1002\nAZ1007\nGL7604\n");
	fprintf(p, "AZ1006\nTG1503\nAZ1003\nJJ4403\n");
	fprintf(p, "AZ1001\nLN7003\nAZ1004\nTG1504\n");
	fprintf(p, "AZ1005\nTG1502\nGL7601\nTT4500\n");
	fprintf(p, "RL7801\nJJ4410\nGL7607\nAL0029\n");
	fprintf(p, "VV3390\nVV3392\nGF4681\nGF4690\n");
	fprintf(p, "AZ1020\nJJ4435\nVG3010\nLF0920\n");
	fprintf(p, "AZ1065\nLF0978\nRL7867\nTT4502\n");
	fprintf(p, "GL7645\nLF0932\nJJ4434\nTG1510\n");
	fprintf(p, "TT1020\nAZ1098\nBA2312\nVG3030\n");
	fprintf(p, "BA2304\nKL5609\nKL5610\nKL5611\n");

	fclose(p);
}

void NAproximacoes_NDecolagens(int *aprox, int *dec) {
	srand(time(NULL));
	*aprox = rand() % 23;
	*aprox += 10;
	*dec = rand() % 23;
	*dec += 10;

}
int NVoos(int naprox, int ndec) {
	return naprox + ndec;
}
char *ordem_AandD(int nvoos, int naprox, int ndec, char *lista_voos) {
	char *lista = (char *)calloc(nvoos, sizeof(char));

	srand(time(NULL));

	int countA = naprox, countD = ndec, i = 0;
	while(countA || countD) {
		int aux = rand() % 2;
		if (aux == 1 && countA > 0) { 
			lista[i] = 'A';
			countA--;
			i++;
		}
		if (aux == 0 && countD > 0) { 
			lista[i] = 'D';
			countD--;
			i++;
		}
	}
	lista[i] = '\0';
	printf("%s\n", lista);

	return lista;
}

void inicia(fila *stack) {
	stack->ini = NULL;
	stack->fim = NULL;
}

void adiciona(fila *stack, FILE *p, char c) {
	aviao *novo = (aviao *)malloc(sizeof(aviao));
	if (novo == NULL) { printf("ERROR 404 Quitting process\n"); exit(1);}

	fscanf(p, "%s\n", novo->codigo_de_voo);
	novo->AorD = c;
	if (stack->ini == NULL) {
		novo->prox = NULL;
		stack->ini = novo;
		stack->fim = novo;
	}
	else {
		stack->fim->prox = novo;
		novo->prox = NULL;
		stack->fim = novo;
	}
}

void remove_fila(fila *stack) {
	aviao *aux = stack->ini;

	stack->ini = stack->ini->prox;
	free(aux);
}

int reduz_combustivel(fila *stack, FILE *p) {
	int cont = 0;
	aviao *pai = stack->ini;
	aviao *aux;
	while (pai->combustivel == 0) {
		aviao *prov = pai;
		pai = pai->prox;
		// remove_por_queda(prov);
		fprintf(p, "ALERTA CRÍTICO AERONAVE IRÁ CAIR\n");
		free(prov);
	}
	pai->combustivel--;
	if (pai->combustivel == 0) cont++;
	stack->ini = pai;
	for (aux = pai->prox; aux != NULL; ) {
		while (aux != NULL && aux->combustivel == 0) {
			aviao *prov = aux;
			aux = aux->prox;
			// remove_por_queda(prov);
			fprintf(p, "ALERTA CRÍTICO AERONAVE IRÁ CAIR\n");
			free(prov);
			pai->prox = aux;
		}
		if (aux == NULL) {
			stack->fim = pai;
			return cont;
		}
		aux->combustivel--;
		if (aux->combustivel == 0) cont++;
		aux = aux->prox;
		pai = pai->prox;
	}
	stack->fim = aux;

	return cont;
}

void ordena_por_prioridade(fila *stack) {
	
	aviao *aux = stack->ini;
	aviao *troca = stack->ini->prox;

	for (; troca != NULL; aux = aux->prox, troca = troca->prox) {
		
		if (troca->prioridade  == 1 && aux->prioridade == 0) {
			if (troca->prioridade == 1 && stack->ini->prioridade == 0) {
				
				aux->prox = troca->prox;
				troca->prox = stack->ini;
				stack->ini = troca;
				troca = aux->prox;
			}
			else if (troca->prioridade == 1) {
				
				aux->prox = troca->prox;
				aviao *prov = stack->ini;
				for (; prov->prox != NULL; prov = prov->prox) {
					if (prov->prox->prioridade == 0) {
						troca->prox = prov->prox;
						prov->prox = troca;
						troca = aux->prox;
						break;
					}
				}
			}
		}
	}
}