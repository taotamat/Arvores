#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arvore_binaria.h"
#include "balanceamento.h"


//----------------------------------------------------------//
// Menu Principal:

int menu(){

	// FUNÇÃO QUE APRESENTA UM MENU.

	int op;
	printf("\n\n");
	
	setbuf(stdin, NULL);

	ast();
	printf("\t\t\tMENU PRINCIPAL:\n");
	ast();
	
	printf("[1] - LER UM NOVO NO\n");
	printf("[2] - APRESENTAR - MODO PRE-ORDEM   \n");
	printf("[3] - APRESENTAR - MODO IN-ORDEM    \n");
	printf("[4] - APRESENTAR - MODO POS-ORDEM   \n");
	printf("[5] - BUSCAR UM NÚMERO NA ÁRVORE    \n");
	printf("[6] - REMOVER UM NUMERO DA ÁRVORE   \n");
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

	arvore = alocaARV();

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
				// FUNÇÃO QUE LER A RAIZ
				gestaoLER(arvore);
				break;

			case 2:
				// APRESENTA TODOS OS NOS DA ÁRVORE NO MODO PRE-ORDEM
				preordem(arvore->raiz);
				break;

			case 3:
				// APRESENTA TODOS OS NÓS DA ÁRVORE NO MODO IN-ORDEM
				inordem(arvore->raiz);
				break;

			case 4:
				// APRESENTA TODOS OS NÓS DA ÁRVORE NO MODO POS-ORDEM
				posordem(arvore->raiz);
				break;

			case 5:
				// FUNÇÃO TAL
				gestaoBUSCA(arvore->raiz);
				break;

			case 6:
				// FUNÇÃO TAL
				gestaoREMOVE(arvore);
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