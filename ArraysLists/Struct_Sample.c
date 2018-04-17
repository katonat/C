#include <stdio.h>
#define MAX 5

typedef struct comodo {
	float largura;
	float comprimento;
	float area;
	char ambiente[20];
} t_comodo;

typedef struct lista {
	t_comodo comodos[MAX];
} t_lista;


int main(){

	t_lista listaComodos;
	int i = 0;
	float areaTotal = 0;

	for(i = 0; i < MAX; i++){
		printf("\nInforme o nome do ambiente: ");
		scanf("%s", &listaComodos.comodos[i].ambiente);
		printf("Informe a largura desse ambiente: ");
		scanf("%f", &listaComodos.comodos[i].largura);
		printf("Informe o comprimento desse ambiente: ");
		scanf("%f", &listaComodos.comodos[i].comprimento);
		listaComodos.comodos[i].area = listaComodos.comodos[i].largura*listaComodos.comodos[i].comprimento;
	}

	for(i = 0; i < MAX; i++){
		areaTotal += listaComodos.comodos[i].area;
	}
	printf("\n");
	for(i = 0; i < MAX; i++){
		printf("\tAmbiente: %s\nArea: [%.2f] metros quadrados\n\n", listaComodos.comodos[i].ambiente, listaComodos.comodos[i].area);
	}
	printf("Area total: %.2f metros quadrados\n", areaTotal);

	return 0;
}
