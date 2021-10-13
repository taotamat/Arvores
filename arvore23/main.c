#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "arvore23.h"


//----------------------------------------------------------//
// Menu Principal:

int menu(){

	// FUNÇÃO QUE APRESENTA UM MENU.

	int op;
	printf("\n\n");
	
	ast();
	printf("\t\t\tMENU PRINCIPAL:\n");
	ast();
	
	printf("[1] - Inserir uma nova informação\n");
	printf("[2] - Apresentar itens da arvore \n");
	printf("[3] - Opcao 3\n");
	printf("[4] - Opcao 4\n");
	printf("[5] - Opcao 5\n");
	printf("[6] - Opcao 6\n");
	printf("[0] - Sair\n");

	ast();
	printf("SELECIONE A OPCAO DE DESEJADA: ");
	scanf("%d", &op);
	ast();

	printf("\n\n");

	return op; }

//----------------------------------------------------------//
// FUNÇÃO MAIN:

int main(){

	int op;
	ARVORE *arvore;
	NO *no;
	INFO *info, *sobe;
	NO *pai, *maior;
	
	arvore = alocaARV();

	int valores[10] = {100, 300, 200, 50, 400, 500, 800, 1000, 20, 700};
	int i;


	for(i=0; i<10; i++){

		ast();
		printf("Insercao do %d \n", valores[i]);

		sobe = NULL;
		pai = maior = NULL;

		info = alocaINFO();
		info->informacao = valores[i];

		inserir(&arvore->raiz, &info, &pai, &sobe, &maior, &arvore);

		printf("\n\n");
		imprimir(arvore->raiz);
		printf("\n\n");

	}





	printf("SUCESSO! \n");

	do{

		op = menu();

		switch(op){

			case 0:
				// ENCERRAR O PROGRAMA;
				ast();
				printf("\t\tPrograma encerrado!\n");
				ast();
				break;

			case 1:
				// FUNÇÃO TAL
				gestaoLER(arvore);
				break;

			case 2:
				// FUNÇÃO TAL
				imprimir(arvore->raiz);
				break;

			case 3:
				// FUNÇÃO TAL
				break;

			case 4:
				// FUNÇÃO TAL
				break;

			case 5:
				// FUNÇÃO TAL
				break;

			case 6:
				// FUNÇÃO TAL
				break;

			default:
				// MENSAGEM DE ERRO
				ast();
				printf("Valor inválido, digite novamente:\n");
				ast();
				break;

		}

	} while(op != 0);




	return 0; }


/*

Adicionais:	

	Compilar e executar:
		gcc nomedoprograma.c -o nomedoprograma -lm && ./nomedoprograma
	
	Ler uma string que contenha espaços e limpeza de buffer:
		scanf(" %[^\n]s", (*carro).chassi);
		setbuf(stdin, NULL);

*/