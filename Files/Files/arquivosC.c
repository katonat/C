#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

typedef struct contato {
	char nome[20];
	char tel[15];
	int id;
} t_contato;

typedef struct no {
	t_contato dado;
	struct no * prox;
} t_no;

typedef t_no * t_lista;

t_no * criaNo() {
    t_no * no = (t_no*) malloc(sizeof(t_no));

    if (no)
        no->prox = NULL;

    return no;
}

int isVazia(t_lista lista) {
	return(lista == NULL);
}

t_no * getNo(t_lista lista, int pos) {
    int n = 0;

    if (pos<0)
        return 0; // erro: posicao invalida

    while (lista != NULL) {
        if (n==pos)
            return lista;
        lista = lista->prox;
        n++;
    }
    return 0; // erro: posicao invalida
}

int compara(t_contato dado1, t_contato dado2) {
    return strcmp(dado1.nome, dado2.nome);
}

int getPosicao(t_lista lista, t_contato dado) {
    int pos = 0;

    if(isVazia(lista))
    	return 0;

    while (lista != NULL) {
        if (compara(lista->dado, dado) > 0)
            return pos;
        lista = lista->prox;
        pos++;
    }
    return pos; // caso nenhum nome na lista seja menor que o que será inserido, a inserção ocorrerá no fim da lista
}


int insereOrdenado(t_lista * lista, t_contato dado, int * id) {
	t_no * novoNo, * p;
	int pos = 0;

	pos = getPosicao(*lista, dado);

	novoNo = criaNo();
	if(novoNo == NULL)
		return 0; //erro na criação do nó
	novoNo->dado = dado;

	if(pos == 0) {
        novoNo->dado.id = ++(*id);
		novoNo->prox = *lista;
		*lista = novoNo;
		return 1;
	}
	p = getNo(*lista, pos-1);
	if(p == NULL)
		return 0; //erro de memória

	novoNo->prox = p->prox;
	p->prox = novoNo;
    novoNo->dado.id = ++(*id);
	return 1;
}

void exibeLista(t_lista lista) {
    t_lista aux;

    if(isVazia(lista)) {
        printf("Lista de contatos vazia.\n");
        return;
    }

    aux = lista;
    printf("Nome\tTelefone\t\tID\n\n");
    while(aux != NULL) {
        printf("%s\t%s\t\t[%d]\n", aux->dado.nome, aux->dado.tel, aux->dado.id);
        aux = aux->prox;
    }
}




void gravaContatosArq(t_lista lista, FILE * fp) {
	t_lista aux;
	
	aux = lista;
	
	while(aux != NULL) {
		fwrite(aux->dado.nome, strlen(aux->dado.nome), 1, fp);	
		fputc(';', fp);
		fwrite(aux->dado.tel, strlen(aux->dado.tel), 1, fp);	
		if(aux->prox != NULL)
			fputc(';', fp);
		aux = aux->prox;		
	}
	
}


int main() {

	FILE * fp, * fp_ordenado;
	t_lista m_lista = NULL;
	t_contato novoContato;
	char aux[30];
	bool isName = true;
	int id = 0,
		i = 0;
	char c = '\0';
	

	fp = fopen("backupAgenda.txt", "r");
	fp_ordenado = fopen("AgendaOrdenada.txt", "w+");


	for(i = 0; c != EOF; i++) {
		c = fgetc(fp);
		if(c == ';' || c == EOF) {
			aux[i] = '\0';
			i = -1;
			if(isName) {
                (strcpy(novoContato.nome, aux));
                isName = false;
			} else {
                (strcpy(novoContato.tel, aux));
                isName = true;
                insereOrdenado(&m_lista, novoContato, &id);
			}
		} else {
            aux[i] = c;
        }
	}
	exibeLista(m_lista);
	
	
	gravaContatosArq(m_lista, fp_ordenado); //grava um novo arquivo com os contatos ordenados

	fclose(fp_ordenado);
	fclose(fp);
	
	fp_ordenado = fopen("AgendaOrdenada.txt", "r");


	printf("\nLendo o novo arquivo:\n\n");
    while (!feof(fp_ordenado)) {
        fread(&c, 1, 1, fp_ordenado);
        printf("%c", c);
        usleep(50000);
    }


	return 0;
}

