#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 60

/* Historico Escolar */

typedef struct disciplina {
    char disciplina[50];
    float nota;
} t_disciplina;

typedef struct no_disciplina {
    t_disciplina dado;
    struct no_disciplina * prox;
} t_no_disciplina;

typedef struct aluno {
    char matricula[11];
    t_no_disciplina * primeiroNo;
} t_aluno;

typedef struct lista_aluno {
    t_aluno vetor[MAX];
    int n;
} t_lista_aluno;

t_lista_aluno criar_listaAluno();
int isVazia(t_lista_aluno * lista);
int isCheia(t_lista_aluno * lista);
void getMatricula(char * matricula);
t_no_disciplina * criarNo();
void getDisciplina(char * disciplina, float * nota);
int inserirDisciplina(t_no_disciplina ** lista);
int inserirAluno(t_lista_aluno * lista);
void exibeHistoricos(t_lista_aluno *lista);
int FreeNo(t_no_disciplina ** lista_no);
int apagaDisciplinas(t_lista_aluno * lista);
int menu();

int main() {

    t_lista_aluno lista;
    int opcao = 1;

    lista = criar_listaAluno();

    while (opcao != 0) {
        opcao = menu();
        switch(opcao) {
            case 0:
                if((apagaDisciplinas(&lista)) == 1)
                    printf("\n\tMemoria liberada.\n\n");
                break;
            case 1:
                (inserirAluno(&lista)==1)? (printf("\n\tSalvo.\n\n")) : printf("\n\tLista de Alunos Cheia.\n\n");
                system("pause");
                system("cls");
                break;
            case 2:
                exibeHistoricos(&lista);
                system("pause");
                system("cls");
                break;
        }
    }
    return 0;
}


//criar lista seq
t_lista_aluno criar_listaAluno() {
    t_lista_aluno lista;
    lista.n = -1;
    return lista;
}

int isVazia(t_lista_aluno * lista) {
    return (lista->n == -1); //retorna 1 caso a lista esteja vazia
}

int isCheia(t_lista_aluno * lista) {
    return (lista->n == MAX-1); //retorna 1 caso a lista esteja cheia
}
//ler matricula
void getMatricula(char * matricula) {
    printf("\nDigite a matricula: ");
    scanf("%s", matricula);
}
//criar cabeça da lista encadeada
t_no_disciplina * criarNo() {
    t_no_disciplina * no = (t_no_disciplina *)malloc(sizeof(t_no_disciplina));
    if(no)
        no->prox = NULL;
    return no;
}
//ler disciplina + nota final
void getDisciplina(char * disciplina, float * nota) {
    printf("\nDigite a disciplina: ");
    scanf("%s", disciplina);
    printf("\nNota Final: ");
    scanf("%f", nota);
}

t_no_disciplina * salvaDisciplina(char * disciplina, float *nota, t_no_disciplina * novo) {
    getDisciplina(disciplina, nota);
    strcpy(novo->dado.disciplina, disciplina);
    novo->dado.nota = *nota;
    return novo;
}
//armazenar discplina na lista
int inserirDisciplina(t_no_disciplina ** lista) {
    char disciplina[50] = "";
    float notaF = 0;
    int opcao = 1;
    t_no_disciplina * novo = NULL;
    t_no_disciplina * ult = NULL;

    if((novo = criarNo())== NULL)
        return 0; //falha de espaço na memoria

    novo = salvaDisciplina(disciplina, &notaF, novo);
    *lista = novo;
    ult = *lista;

    while(opcao != 0) {
        printf("\n\t(1)Inserir nova disciplina\n\t(0)Cancelar\n\n\t>> ");
        scanf("%d", &opcao);

        if(opcao == 1) {
            if((novo = criarNo())== NULL)
                return 0; //falha de espaço na memoria
            novo = salvaDisciplina(disciplina, &notaF, novo);
            ult->prox = novo;
            ult = novo;

        } else if(opcao > 1 || opcao < 0)
            printf("\n\tOpcao invalida.\n");
    }
    return 1;
}
//inserir na lista seq
int inserirAluno(t_lista_aluno * lista) {
    char matricula[11] = "";
    int opcao = 1;

    while(opcao != 0 && !(isCheia(lista))) {
        getMatricula(matricula);
        strcpy(lista->vetor[lista->n+1].matricula, matricula);
        lista->n++;
        inserirDisciplina(&(lista->vetor[lista->n].primeiroNo));
        printf("\n\n\t(1)Inserir novo aluno\n\t(0)Cancelar\n\n\t>> ");
        scanf("%d", &opcao);
    }
    if(isCheia(lista) == 1)
        return 0; //não foi possivel inserir
    return 1;
}
//exibir historicos
void exibeHistoricos(t_lista_aluno *lista) {
    int i = 0;
    t_no_disciplina * aux = NULL;

    if(isVazia(lista) == 1)
        printf("\n\t Lista de Alunos Vazia \n\n");
    else
        printf("\n MATRICULA\t\tDISCIPLINA\tNOTA FINAL\n\n");

    for(i = 0; i <= lista->n; i++) {
        aux = lista->vetor[i].primeiroNo;
        printf(" [%s]\n", lista->vetor[i].matricula);
        while(aux != NULL) {
            printf("\t\t\t[%s]\t[%.2f]\n", aux->dado.disciplina, aux->dado.nota);
            aux = aux->prox;
        }
        printf("\n  --------------------------------------\n");
    }
    printf("\n");
}
//liberar a memória
int freeNo(t_no_disciplina ** lista) {
    t_no_disciplina * p = NULL;

    while(*lista != NULL) {
        p = *lista;
        *lista = p->prox;
        free(p);
    }
    return (*lista == NULL);
}

int apagaDisciplinas(t_lista_aluno * lista) {
    int i = 0;
    if(isVazia(lista) == 1)
        return 0;

    for(i = 0; i <= lista->n; i++)
        freeNo(&(lista->vetor[i].primeiroNo));

    return 1;
}
//menu
int menu() {
    int opcao = 1;

    while (opcao != 0) {
        printf("\tALUNO: NATHALIE NICIE KATO\n\tDISCIPLINA: ESTRUTURA DE DADOS I\n\tPROFESSOR: WALACE BONFIM\n\n");
        printf("\t\tHISTORICO ESCOLAR\n\n");
        printf("1 - INSERIR MATRICULAS, DISCIPLINAS E NOTAS\n2 - EXIBIR HISTORICOS\n0 - SAIR\n\n\t>> ");
        scanf("%d", &opcao);
        getchar();
        if(opcao > 2 || opcao < 0)
            printf("\n\tOpcao invalida.\n\n\n");
        else
            return opcao;
    }
    return 0; //opcao de SAIR
}

