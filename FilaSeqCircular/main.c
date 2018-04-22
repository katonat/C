#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef struct elemento {
	char nome[20];
} t_elemento;

typedef struct fila {
	t_elemento vet[MAX];
	int ini;
	int fim;
	int qntd_elementos;
} t_fila;

t_fila criar() {
	t_fila fila;

	fila.ini = 0;
	fila.fim = -1;
	fila.qntd_elementos = 0;
	return fila;
}

int isVazia(t_fila * fila) {
	return (fila->qntd_elementos == 0); //retorna 1 caso q fila esteja vazia
}

int ischeia(t_fila * fila) {
	return(fila->qntd_elementos == MAX); //retorna 1 caso a fila esteja cheia
}

int inserir(t_fila * fila, t_elemento dado) {
	if(ischeia(fila))
		return 0; // erro ao inserir, fila cheia

    (fila->qntd_elementos)++;
	fila->fim = (fila->fim + 1) % MAX;
	fila->vet[fila->fim] = dado;
	return 1;
}

t_elemento remover(t_fila * fila) {
	t_elemento valor = {""};

	if(isVazia(fila))
		return valor; // erro, fila vazia

	valor = fila->vet[fila->ini];
	fila->ini = (fila->ini + 1) % MAX;
	fila->qntd_elementos--;
	return valor;
}

void exibir(t_fila * fila) {
	int i = 0,
        j = 0;

	if(isVazia(fila)) {
		printf("Fila Vazia\n");
		return;
	}
    printf("Exibindo fila:    ");
    for(i = fila->ini, j = 0; j < fila->qntd_elementos; i = (i+1) % MAX, j++)
        printf("%s  ", fila->vet[i].nome);
    printf("\n");
}

t_elemento recebeNome() {
    t_elemento novo;
    printf("Entrou na fila: ");
    scanf("%s", novo.nome);

    return novo;
}



int main() {

	t_fila m_fila;
	t_elemento aux;
	int i = 0;

	m_fila = criar(); //a)

	//b) entram 4 pessoas e a cada entrada mostrar as pessoas da fila na ordem "da primeira até a última"
	for(i = 0; i < 4; i++) {
        inserir(&m_fila, recebeNome());
        exibir(&m_fila);
        printf("\n");
	}

	//c) saem 3 pessoas e a cada saída mostrar as pessoas da fila na ordem "da primeira até a última"
	for(i = 0; i < 3; i++) {
        aux = remover(&m_fila);
        printf("\nSaindo %s ...\n", aux.nome);
        exibir(&m_fila);
	}

	//d) entram mais 4 pessoas e a cada entrada mostrar as pessoas da fila na ordem "da primeira até a última"
	for(i = 0; i < 4; i++) {
        inserir(&m_fila, recebeNome());
        exibir(&m_fila);
	}



	return 0;
}
