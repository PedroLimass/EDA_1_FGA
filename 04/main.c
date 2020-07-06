#include "func.h"

int main() {
	int Naprox, Ndec, Nvoos;
	char *lista_voos;
	fila stack;

	cria_arquivo_codigos_voo();

	srand(time(NULL));

	inicia(&stack);

	NAproximacoes_NDecolagens(&Naprox, &Ndec);
	Nvoos = NVoos(Naprox, Ndec);
	lista_voos = ordem_AandD(Nvoos, Naprox, Ndec, lista_voos);

	FILE *p = fopen("sequencia_de_voo.txt", "r");
	int conta_prioridade = 0;
	for (int i = 0; i < Nvoos; i++) {
		adiciona(&stack, p, lista_voos[i]);
		if (stack.fim->AorD == 'A') {
			stack.fim->combustivel = rand() % 13;
			stack.fim->prioridade = 0;
			if (stack.fim->combustivel == 0) {
				stack.fim->prioridade = 1;
				conta_prioridade++;
			}
		}
		else {
			stack.fim->combustivel = 100;
		}
	}
	fclose(p);

	int pistas[3] = {0 , 0, 0};

	p = fopen("funcionamento_aeroporto.txt", "w");
	int hora = rand() % 24, min = rand() % 60, UnTempo = 10;
	fprintf(p,  "---------------------------------------------------------------------------------\n");
	fprintf(p, "“Aeroporto Internacional de Brasília”\n");
	fprintf(p, "HoraInicial: %.2d:%.2d\n", hora, min);
	if (conta_prioridade >= 3) { 
		fprintf(p, "ALERTA GERAL DESVIO DE AERONAVE\n");
		ordena_por_prioridade(&stack);
	}
	else if (conta_prioridade > 0) ordena_por_prioridade(&stack);
	fprintf(p, "Fila de Pedidos:[");
	for (aviao *aux = stack.ini; aux != NULL; aux = aux->prox) {
		if (aux->prox != NULL) {
			fprintf(p, "\"%s\"", aux->codigo_de_voo);
			if (aux->AorD == 'A')
				fprintf(p, " - P - ");
			else
				fprintf(p, " - D - ");
			fprintf(p, "%d, ", aux->prioridade);
		}
		else {
			fprintf(p, "\"%s\"\n", aux->codigo_de_voo);
			if (aux->AorD == 'A')
				fprintf(p, " - P - ");
			else
				fprintf(p, " - D - ");
			fprintf(p, "%d]\n", aux->prioridade);
		}
	}
	fprintf(p, "NVoos: %d\n", Nvoos);
	fprintf(p, "Naproximações: %d\n", Naprox);
	fprintf(p, "NDecolagens: %d\n", Ndec);
	fprintf(p, "---------------------------------------------------------------------------------\n");
	fprintf(p, "Listagem de eventos:\n");
	while (1) {
		if (stack.ini == NULL) break;

		if (pistas[0] == 0) {
			fprintf(p, "Código do voo: %s\n", stack.ini->codigo_de_voo);
			if (stack.ini->AorD == 'A') {
				fprintf(p, "Status: aeronave pousou\n");
				pistas[0] = 4;
				fprintf(p, "Combustível na hora do pouso: %d\n", stack.ini->combustivel);
			}
			else {
				fprintf(p, "Status: aeronave decolou\n");
				pistas[0] = 2;
			}
			fprintf(p, "Horário do início do procedimento: %.2d:%.2d\n", hora, min);
			fprintf(p, "Número da pista: 1\n");
			// remove
			remove_fila(&stack);
		}
		if (stack.ini == NULL) break;
		if (pistas[1] == 0) {
			fprintf(p, "Código do voo: %s\n", stack.ini->codigo_de_voo);
			if (stack.ini->AorD == 'A') {
				fprintf(p, "Status: aeronave pousou\n");
				pistas[1] = 4;
				fprintf(p, "Combustível na hora do pouso: %d\n", stack.ini->combustivel);
			}
			else {
				fprintf(p, "Status: aeronave decolou\n");
				pistas[1] = 2;
			}
			fprintf(p, "Horário do início do procedimento: %.2d:%.2d\n", hora, min);
			fprintf(p, "Número da pista: 2\n");
			// remove
			remove_fila(&stack);
		}
		if (stack.ini == NULL) break;
		if ((pistas[2] == 0 && stack.ini->AorD == 'D') || (pistas[2] == 0 && stack.ini->combustivel == 0)) {
			fprintf(p, "Código do voo: %s\n", stack.ini->codigo_de_voo);
			if (stack.ini->AorD == 'A') {
				fprintf(p, "Status: aeronave pousou\n");
				pistas[2] = 4;
				fprintf(p, "Combustível na hora do pouso: %d\n", stack.ini->combustivel);
			}
			else {
				fprintf(p, "Status: aeronave decolou\n");
				pistas[2] = 2;
			}
			fprintf(p, "Horário do início do procedimento: %.2d:%.2d\n", hora, min);
			fprintf(p, "Número da pista: 3\n");
			// remove
			remove_fila(&stack);
		}

		UnTempo--;
		if (pistas[0] > 0) pistas[0]--;
		if (pistas[1] > 0) pistas[1]--;
		if (pistas[2] > 0) pistas[2]--;
		min += 5;
		if (min > 59) {
			min %= 60;
			hora++;
			if (hora > 23) hora %= 24;
		}
		if (UnTempo == 0) {
			UnTempo = 10;
			int aux = reduz_combustivel(&stack, p);
			if (aux >= 3) {
				fprintf(p, "ALERTA GERAL DESVIO DE AERONAVE\n");
				ordena_por_prioridade(&stack);
			}
			else if (aux > 0) ordena_por_prioridade(&stack);
		}
	}

	fclose(p);

	return 0;
}