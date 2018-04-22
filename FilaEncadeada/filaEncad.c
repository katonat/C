
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elemento {
    char nome[20];
} t_elemento;

typedef struct no {
    t_elemento dado;
    struct no * prox;
} t_no;

typedef struct fila {
    t_no * ini;
    int qntd;
    t_no * fim;
} t_fila;


t_fila * criar() {
    t_fila * fila = (t_fila *)malloc(sizeof(t_fila));
    if(fila) {
        fila->ini = fila->fim = NULL;
        fila->qntd = 0;
    }
    return fila;
}

t_no * criarNo() {
    t_no * no = (t_no *)malloc(sizeof(t_no));
    if(no)
        no->prox = NULL;

    return no;
}

int isVazia(t_fila * fila) {
    return (fila->qntd == 0); //retorna 1 caso a fila esteja vazia
}

int inserir(t_fila * fila, t_elemento valor) {
    t_no * novo = criarNo();
    if(novo == NULL)
        return 0; //erro ao alocar memória para novo nó

    novo->dado = valor;
    if(isVazia(fila))
        fila->ini = novo;
    else
        fila->fim->prox = novo;

    fila->fim = novo;
    fila->qntd++;
    return 1;
}

t_elemento remover(t_fila * fila) {
    t_elemento valor = {""};
    t_no * p; //nó que vai ter memória liberada
    if(isVazia(fila))
        return valor; //impossível remover de fila vazia

    valor = fila->ini->dado;
    if(fila->ini == fila->fim)
        fila->fim = NULL;
    p = fila->ini; //nó que será removido
    fila->ini = fila->ini->prox;
    free(p);
    fila->qntd--;
    return valor;
}

int exibir(t_fila * fila) {
    t_no * aux;
    if(isVazia(fila))
        return 0; //impossível exibir elementos de fila vazia

    aux = fila->ini;
    printf("\n\tMostrando fila...   ");
    while(aux != NULL) {
        printf("%s   ", aux->dado.nome);
        aux = aux->prox;
    }
    printf("\n\n");
    return 1;
}

t_elemento recebeNome() {
    t_elemento novo;
    printf("Entrou na fila: ");
    scanf("%s", novo.nome);
    return novo;
}

int main(){

    t_fila * m_fila;
    int i;

    m_fila = criar(); //a)criar a fila

    for(i = 0; i < 4; i++) { //b) entram 4 pessoas e a cada entrada mostrar as pessoas da fila na ordem crescente
        inserir(m_fila, recebeNome());
        exibir(m_fila);
    }

    return 0;
}
