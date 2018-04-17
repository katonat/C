#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#define MAX 10
#define TAM 3

typedef struct elemento {
	char nome[50];
} t_elemento;

typedef struct lista {
	t_elemento vetor[MAX];
	int n;
} t_lista;

t_lista criar();
int isVazia(t_lista *lista);
int isCheia(t_lista *lista);
int getTamanho(t_lista *lista);
t_elemento *getElemento(t_lista *lista, int pos);
int inserir (t_lista * lista, int pos, t_elemento dado);
int compara(t_elemento dado1, t_elemento dado2);
int getPosicao(t_lista * lista, t_elemento dado);
int deslocaDireita(t_lista * lista, int pos);
int deslocaEsquerda(t_lista * lista, int pos);
int remover (t_lista *lista, int pos);
void exibe_lista(t_lista *lista);
void cabecalho(t_elemento *elem, char* msg1, char* msg2);

int main() {

	t_lista minhaLista;
	t_elemento meuElemento;
	int i = 0,
		posicao = 0;
	char str[50];
	minhaLista = criar();

	//Guardar tres nomes
	for(i = 0; i < TAM; i++) {
		cabecalho(&meuElemento, "Escreva um nome:\n", "O nome digitado foi: [%s]\n");
		inserir(&minhaLista, i, meuElemento);
	}
	exibe_lista(&minhaLista);

	//Buscar e mostrar um nome
	cabecalho(&meuElemento, "\nEscreva um nome a ser buscado: \n", "\nO nome digitado para a busca foi: [%s]\n");
	for(i = 0; i < TAM; i++)
		posicao = getPosicao(&minhaLista, meuElemento);
	(posicao == -1) ? (printf("\nElemento nao encontrado.\n")) : (printf("\nA posicao do nome digitado e: [%i]\n", posicao));

	//Remover um nome
	cabecalho(&meuElemento, "\nQual o nome a ser removido?\n", "");
	for(i = 0; i < TAM; i++)
		posicao = getPosicao(&minhaLista, meuElemento);
	(posicao == -1) ? (printf("\nNome nao encontrado.\n")) : (remover(&minhaLista, posicao));

	exibe_lista(&minhaLista);

	return 0;
}

//funções de lista sequencial
t_lista criar() {
	t_lista lista;
	lista.n = -1;
	return lista;
}

int isVazia(t_lista *lista) {
	return (lista->n == -1); //retorna 1 se a lista estiver vazia e 0, caso contrario
}

int isCheia(t_lista *lista) {
	return (lista->n == MAX-1); //retorna 1 se a lista estiver cheia e 0, caso contrario
}

int getTamanho(t_lista *lista) {
	return lista->n + 1;
}

t_elemento *getElemento(t_lista *lista, int pos) {
	if((pos > lista->n) || pos < 0)
		return 0; //retorna 0 se a posição for invalida

	return &(lista->vetor[pos]);
}

int inserir (t_lista * lista, int pos, t_elemento dado) {
    if ( isCheia(lista) || (pos > lista->n + 1) || (pos < 0) )
        return 0;

    deslocaDireita(lista, pos);
    lista->vetor[pos] = dado;
    (lista->n)++;
    return 1;
}

int compara(t_elemento dado1, t_elemento dado2) {
    return strcmp(dado1.nome, dado2.nome);
}

int getPosicao(t_lista * lista, t_elemento dado) {
    int i;
    for (i=0; i<=lista->n; i++)
        if (compara(lista->vetor[i], dado)==0)
            return i;

    return -1;
}

int deslocaDireita(t_lista * lista, int pos) {
    int i;

    for (i=lista->n + 1; i>pos; i--)
        lista->vetor[i] = lista->vetor[i-1];

    return 1;
}

int deslocaEsquerda(t_lista * lista, int pos) {
    int i;

    for (i=pos; i<(lista->n); i++)
        lista->vetor[i] = lista->vetor[i+1];

    return 1;
}

int remover (t_lista *lista, int pos) {
    if ( (pos > lista->n) || (pos < 0) )
        return 0;

    deslocaEsquerda(lista, pos);

    (lista->n)--;
    return 1;
}

void exibe_lista(t_lista *lista) {
	int i = 0;
	printf("\nNomes na lista:\n");
	for(i = 0; i <= lista->n; i++)
		printf("[%s]\n", lista->vetor[i].nome);
}

void cabecalho(t_elemento *elem, char* msg1, char* msg2) {
	printf(msg1);
	scanf("%s", &elem->nome);
	printf(msg2, elem->nome);
}
