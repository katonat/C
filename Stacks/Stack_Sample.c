#include <stdio.h>
#include <stdlib.h>
#define MAX 3

/**
*
* @author Nathalie Kato
* Você está na entrada de um beco comprido, estreito e sem saída,
* no qual carros entram e saem em fila única, pois não há espaço lateral para dois carros.
* Neste beco cabem três carros.
*
*/

typedef struct carro {
    char placa[8];
} t_carro;

typedef struct pilha {
    t_carro vetor[MAX];
    int topo;
} t_pilha;

t_pilha criar();
int isVazia(t_pilha * pilha);
int isCheia(t_pilha * pilha);
t_carro getCarroTopo(t_pilha * pilha) ;
t_carro pop(t_pilha * pilha);
void removeUmAUm(t_pilha * pilha);
int push(t_pilha * pilha, t_carro novo);
void mostraPlacas(t_pilha * pilha);
t_carro recebePlaca();
void guardaPlacas(t_pilha * pilha);
char * mostraUmaPlaca(t_pilha * pilha, int pos);
void situacoes(t_pilha * pilha);

int main(){

    t_pilha pilhaCarros;

    pilhaCarros = criar();

    situacoes(&pilhaCarros);

    return 0;
}

t_pilha criar() {
    t_pilha pilha;

    pilha.topo = -1;
    return pilha;
}

int isVazia(t_pilha * pilha) {
    return (pilha->topo == -1); //retorna 1 caso a pilha esteja vazia e 0 caso contrario
}

int isCheia(t_pilha * pilha) {
    return (pilha->topo == MAX-1); //retorna 1 caso pilha esteja cheia e 0 caso contrario
}

t_carro getCarroTopo(t_pilha * pilha) {
    t_carro vazio = {""};

    if(isVazia(pilha))
        return vazio;

    return pilha->vetor[pilha->topo]; // retorna o ultimo carro que entrou no beco
}

t_carro pop(t_pilha * pilha) {
    t_carro vazio = {""};

    if(isVazia(pilha))
        return vazio;

    return pilha->vetor[pilha->topo--]; //decrementa o topo após a retorno do elemento removido
}

void removeUmAUm(t_pilha * pilha) {
    t_carro ultimo;

    if(!isVazia(pilha)) {
        ultimo = pop(pilha);
        printf("Saiu o carro de placa: [ %s ]\n", ultimo.placa);
        removeUmAUm(pilha);
    }
}

int push(t_pilha * pilha, t_carro novo) {
    if(isCheia(pilha))
        return 0; //erro

    pilha->vetor[++pilha->topo] = novo;
    return 1; //sucesso
}

void mostraPlacas(t_pilha * pilha) {
    int i = 0;
    printf("\n");
    for(i = 0; i <= pilha->topo; i++)
        printf("[ %s ]\n", pilha->vetor[i].placa);
}

t_carro recebePlaca() {
    t_carro novo;

    printf("Numero da placa: ");
    scanf("%s", novo.placa);

    return novo;
}

void guardaPlacas(t_pilha * pilha) {
    int i = 0;
    for(i = 0; i < MAX; i++)
     if(push(pilha, recebePlaca()) == -1)
        printf("Nao foi possivel inserir\n");

    mostraPlacas(pilha);
}

char * mostraUmaPlaca(t_pilha * pilha, int pos) {
    return pilha->vetor[pos-1].placa;
}

void situacoes(t_pilha * pilha) {
    int op = -1;

    while(op != 0) {
        printf("\n\nEscolha o numero da situacao escolhida:\n");
        printf("1) tres carros entram no beco. Registre as placas desses carros\n");
        printf("2) mostra a placa do terceiro carro que entrou\n");
        printf("3) tres carros saem do beco. mostre a placa de cada carro que saiu\n");
        printf("4) mostra quantos carros ficaram no beco\n");
        printf("0) Sair\n\n>> ");
        scanf("%d", &op);

        if(op != 0) {
            switch(op) {
            case 1:
                guardaPlacas(pilha);
                break;
            case 2:
                printf("Placa do terceiro carro que entrou: [ %s ]\n", mostraUmaPlaca(pilha, 3));
                break;
            case 3:
                removeUmAUm(pilha);
                break;
            case 4:
                printf("Carros que ficaram no beco: %d\n", pilha->topo+1);
                break;
            default:
                printf("Opcao invalida.\n");
            }
        }
    }
}
