#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define TEL 12
#define NOME 30

typedef struct contato {
    char nome[NOME];
    char residencial[TEL];
    char celular[TEL];
} t_contato;

typedef struct agenda { // TIPO LISTA (AGENDA TELEFONICA)
    t_contato lista[MAX];
    int n;
} t_agenda;


//FUNÇÕES
t_agenda criar() {
    t_agenda agenda;
    agenda.n = -1;
    return agenda;
}

int isVazia(t_agenda *agenda) {
    return (agenda->n == -1); // retorna 1 se a agenda estiver vazia e 0 caso contrario
}

int isCheia(t_agenda *agenda) {
    return (agenda->n == MAX-1); // retorna 1 se a agenda estiver cheia e 0 caso contrario
}

int tipoTelefone() {
    int op = 0;
    while(op != 1 && op != 2){
        printf("\n\t(1)Residencial\n\t(2)Celular\n\n\t>> ");
        scanf("%d", &op);
        if(op != 1 && op != 2)
            printf("\tOpcao Invalida. Tente novamente\n");
    }
    return op;
}

int inserirNovo(t_agenda *agenda, t_contato novoContato, char numero[TEL]) {
    int tipo = 0;
    if(isCheia(agenda) == 1)
    	return 0; //se a agenda estiver cheia, não é possível inserir novo contato

    strcpy(agenda->lista[agenda->n+1].nome, novoContato.nome);

    //inicializa o tipo de telefone que não for ocupado
    if((tipo = tipoTelefone()) == 1) {
        strcpy(agenda->lista[agenda->n+1].residencial, numero);
        strcpy(agenda->lista[agenda->n+1].celular, "   ");
    } else{
        strcpy(agenda->lista[agenda->n+1].celular, numero);
        strcpy(agenda->lista[agenda->n+1].residencial, "   ");
    }
    agenda->n++; //acrescenta a posição da lista agenda
    return 1; //retorna 1 caso tenha inserido novo contato com sucesso
}

int comparaNome(t_contato dado1, t_contato dado2) {
    return (strcmp(dado1.nome, dado2.nome)); //retorna 0 caso os nomes sejam iguais
}


int inserirExistente(t_agenda *agenda, t_contato novoContato, char numero[TEL]) {
    int i = 0,
        tipo = 0;
    tipo = tipoTelefone();

    if(isVazia(agenda) == 1)
    	printf("Agenda vazia. Crie um novo contato\n\n"); //não é possível salvar em um ctt ja existente se a agenda estiver vazia

    for(i = 0; i <= agenda->n; i++)
        if(comparaNome(agenda->lista[i], novoContato) == 0){
			if(tipo == 1)
                strcpy(agenda->lista[i].residencial, numero);
            else
                strcpy(agenda->lista[i].celular, numero);
            return 1; //caso tenha salvo o numero com sucesso
        }
    printf("\n\tContato nao encontrado na agenda.\n\n");
    return 0; //caso tenha falhado
}

int menu() {
    int op = 0;
    while(op != 4){
        printf(" *AGENDA TELEFONICA*\n\n(1)Visualizar contatos\n(2)Salvar numero\n(3)Apagar numero\n(4)Sair\n\n\t>> ");
        scanf("%d", &op);
        return op;
    }
    return op;
}

void ordenaContatos(t_agenda *agenda, int inicio, int fim) {
	int i = 0,
		j = 0;
	t_contato aux, meio;

	i = inicio;
	j = fim;
	meio = agenda->lista[(inicio+fim)/2];

	do {
		while(comparaNome(agenda->lista[i], meio) < 0)
			i++;
		while(comparaNome(agenda->lista[j], meio) > 0)
			j--;
		if(i <= j) {
			aux = agenda->lista[i];
			agenda->lista[i] = agenda->lista[j];
			agenda->lista[j] = aux;
			i++;
			j--;
		}
	} while(i <= j);

	if(inicio < j)
		ordenaContatos(agenda, inicio, j);
	if(i < fim)
		ordenaContatos(agenda, i, fim);

}

void visualizarContatos(t_agenda *agenda) {
    int i = 0;
    if(agenda->n == -1) {
        printf("\tAgenda vazia\n\n");
    } else {
        ordenaContatos(agenda, 0, agenda->n);
        printf("\n     > Todos os Contatos <\n\n");
        for(i = 0; i <= agenda->n; i++)
            printf("\tNome\t[ %s ]\n\tResid.\t[ %s ]\n\tCel.\t[ %s ]\n\n", agenda->lista[i].nome, agenda->lista[i].residencial, agenda->lista[i].celular);

        printf("\n");
    }
    system("pause");
    system("cls");
}

int deslocaEsquerda(t_agenda *agenda, int pos) {
    int i = 0;

    for (i=pos; i<(agenda->n); i++)
        agenda->lista[i] = agenda->lista[i+1];

    return 1;
}

t_contato getContato() {
    t_contato dado;
    printf("\nInforme o contato que deseja apagar: \n\n\t>> ");
    scanf("%s", &dado.nome);

    return dado;
}

int apagarContato(t_agenda *agenda) {
    int i = 0;
    int op = 0;
    t_contato dado;
    if(isVazia(agenda) == 1) {
        printf("\tAgenda vazia.\n\n");
        return 0; //retorna 0 caso nao seja possivel apagar nenhum contato    }
    }

    dado = getContato();

    for(i = 0; i <= agenda->n; i++)
        if(comparaNome(agenda->lista[i], dado)==0)
            while(op != 2) {
                printf("\nDeseja apagar [ %s ] ?\n\n\t(1) Sim\n\t(2) Nao\n\n\t>> ", dado.nome);
                scanf("%d", &op);
                if(op == 1) {
                    deslocaEsquerda(agenda, i);
                    agenda->n--;
                    return 1; //retorna 1 caso tenha apagado o contato com sucesso
                } else
                    printf("\n\tOpcao invalida.*");
            }
    printf("\nContato nao encontrado.\n");
    return 0;
}

int salvar(t_agenda *agenda) {
    t_contato novoContato;
    char numero[TEL] = "";
    int op = 0;
    int situacao = 0;

    printf("\nNome do contato a ser salvo: ");
    scanf("%s", novoContato.nome);
    printf("Numero: ");
    scanf("%s", numero);

    while(op != 1 && op != 2){
        printf("\n\t(1)Criar novo contato\n\t(2)Salvar em contato ja existente\n\t(3)Cancelar\n\n\t>> ");
        scanf("%d", &op);
        if(op==1) {
            if((inserirNovo(agenda, novoContato, numero))==1)
                 situacao = 1;
        } else if(op==2) {
            if((inserirExistente(agenda, novoContato, numero))==1)
                situacao = 1;
        } else
            printf("\nOpcao invalida.(1)\n");
    }
    return situacao;
}



int main() {

	t_agenda my_agenda;
	int op = 0;

    my_agenda = criar();

    while(op != 4){
        op = menu();
        switch(op) {
        case 1:
            visualizarContatos(&my_agenda);
            break;
        case 2:
            if(salvar(&my_agenda)==1)
                printf("\n\tContato salvo\n\n");
            else
                printf("\tNao foi possivel salvar o contato.\n\n");
            system("pause");
            system("cls");
            break;
        case 3:
            if((apagarContato(&my_agenda)) == 1)
                printf("\n\tContato Apagado.\n\n");
            else
                printf("\n\tNao foi possivel apagar o contato.\n\n");
            system("pause");
            system("cls");
            break;
        }
    }

    return 0;
}


