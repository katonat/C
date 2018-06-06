#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 10

typedef struct contato {
	char nome[20];
	char tel[15];
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
    return pos;
}

int compara(t_contato dado1, t_contato dado2) {
    return strcmp(dado1.nome, dado2.nome);
}


int insereOrdenado(t_lista * lista, t_contato dado, int * id) {
	t_no * novoNo, * p;
	int pos = -1;
	
	pos = getPosicao(*lista, dado);
	
	novoNo = criaNo();
	if(novoNo == NULL)
		return 0; //erro na criação do nó	
	novoNo->dado = dado;
	
	if(pos == 0) {
		novoNo->prox = *lista;
		*lista = novoNo;
		*id++;
		return 1;		
	}
	p = getNo(*lista, pos-1);
	if(p == NULL) 
		return 0; //erro de memória
		
	novoNo->prox = p->prox;
	p->prox = novoNo;
	*id++;
	return 1;
}


int main() {
	
	FILE * fp;
	t_lista m_lista;
	t_contato novoContato;
	char aux[50];
	bool isName = true;
	int id = 0,
		i = 0;
	char c = '\0';
	
	fp = fopen("backupAgenda.txt", "r");
	
	while(!(feof(fp))) {
		
		for(i = 0; i < 50; i++) {
			c = fgetc(fp);
			if(c == ';') {
				aux[i] = '\0';
				(isName) ? (strcpy(novoContato.nome, aux)): (strcpy(novoContato.nome, aux));
				isName = false;
				i = 0;
			}		
			aux[i] = c;	
		}
		
		
	}
	
	return 0;
}
