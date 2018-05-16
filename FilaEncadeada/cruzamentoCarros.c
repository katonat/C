#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct elemento {
    char placa[9];
} t_elemento;

typedef struct no {
    t_elemento dado;
    struct no * prox;
} t_no;

typedef struct fila {
    t_no * ini;
    t_no * fim;
    int qntd;
} t_fila;


t_fila * criar() {
    t_fila * fila = (t_fila *)malloc(sizeof(t_fila));
    if(fila) {
        fila->fim = fila->ini = NULL;
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
    return(fila->qntd == 0); //retorna 1 se a fila estiver vazia
}

int inserir(t_fila * fila, t_elemento dado) {
    t_no * novo = criarNo();
    if(novo == NULL)
        return 0; //erro ao alocar memória

    novo->dado = dado;
    if(isVazia(fila))
        fila->ini = novo;
    else
        fila->fim->prox = novo;
    fila->fim = novo;
    fila->qntd++;
    return 1;
}

int remover(t_fila * fila) {
    t_no * p;

    if(isVazia(fila)) {
        printf("\tSinal aberto sem carros\n");
        return 0;
    }

    if(fila->ini == fila->fim)
        fila->fim = NULL;
    p = fila->ini;
    fila->ini = p->prox;
    fila->qntd--;
    free(p);
    return 1;
}


void statusTransito(char sinalAberto, t_fila * filaA, t_fila * filaB) {
    printf("\n** STATUS DO TRANSITO **\n\n");
    printf("Sinal aberto: %c\n", toupper(sinalAberto));
    (sinalAberto == 'a') ? (printf("Sinal fechado: B\n")) : printf("Sinal fechado: A\n");

    printf("Numero de carros no sinal A: %d\n", filaA->qntd);
    printf("Numero de carros no sinal B: %d\n", filaB->qntd);
    printf("\n\n");
}



int main() {

    int op = -1;
    int cont = 0;
    char sinalAberto = 'a';
    t_fila * a;
    t_fila * b;
    t_elemento novoCarro = {""};
    time_t t;
    srand((unsigned) time(&t));

    printf("ALUNO: NATHALIE NICIE KATO\nDISCIPLINA: ESTRUTURA DE DADOS I\nPROFESSOR: WALACE BONFIM\n");

    a = criar();
    b = criar();

    while(1) {
        cont++;
        op = rand() % 3;
        switch(op) {
        case 0:
            printf("\n\tEntrou um carro no sinal A.\n");
            inserir(a, novoCarro);
            break;
        case 1:
            printf("\n\tEntrou um carro no sinal B.\n");
            inserir(b, novoCarro);
            break;
        case 2:
            printf("\n\tNenhum carro entrou.\n");
            break;
        }

        if(cont == 10) {
            (sinalAberto == 'a') ? (sinalAberto = 'b') : (sinalAberto = 'a');
            cont = 0;
        }

        if(sinalAberto == 'a') {
            if(remover(a))
                printf("\n\tSaiu um carro do sinal A.\n");
        } else {
            if(remover(b))
                printf("\n\tSaiu um carro do sinal B.\n");
        }

        statusTransito(sinalAberto, a, b);
        system("pause");
        system("cls");
    }

    return 0;
}
