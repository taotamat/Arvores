#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "arvore23.h"


void ast(){
	printf("-------------------------------------------------------------\n"); }


/* ----------------------------------- ALOCAÇÕES ----------------------------------- */


INFO *alocaINFO(){
	INFO *nova;
	nova = (INFO *) malloc(sizeof(INFO));
	nova->informacao = -1;
	return nova; }

NO *alocaNO(){
	NO *novo;
	novo = (NO *) malloc(sizeof(NO));
	novo->info1 = NULL;
	novo->info2 = NULL;
	novo->esq = NULL;
	novo->cen = NULL;
	novo->dir = NULL;
	novo->nmrINFO = 0;
	novo->nmrFILHOS = 0;
	return novo; }

ARVORE *alocaARV(){
	ARVORE *nova;
	nova = (ARVORE *) malloc(sizeof(ARVORE));
	nova->tam = 0;
	nova->raiz = NULL;
	return nova; }


/* ----------------------------------- FUNÇÕES BÁSICAS ----------------------------------- */

// Função que devolve a quantidade de filhos que o Nó possui;
int qntFILHOS(NO *no){
	
	int qnt = 0;

	if(no->esq != NULL)
		qnt++;

	if(no->cen != NULL)
		qnt++;

	if(no->dir != NULL)
		qnt++;

	return qnt; }

// Função que devolve a quantidade de informações presentes no Nó
int qntINFO(NO *no) {

	int qnt = 0;

	if( no->info1 != NULL )
		qnt++;

	if( no->info2 != NULL )
		qnt++;

	return qnt; }

// Função que ajusta o número de filhos e informações que um Nó possui
NO *ajustaNMRS(NO *no){
	no->nmrINFO = qntINFO(no);
	no->nmrFILHOS = qntFILHOS(no);
	return no; }


/* ----------------------------------- INSERÇÃO ----------------------------------- */

// Função que ler a nova informação;
INFO *ler(){
	INFO *nova;
	nova = alocaINFO();
	printf("Digite a nova informacao: ");
	scanf("%d", &nova->informacao);
	return nova; }

// Função que adiciona um novo Nó.
NO *addNO(NO *raiz, INFO *info, NO *filho){
	
	if( info->informacao > raiz->info1->informacao ){
		
		raiz->info2 = info;
		raiz->dir = filho;
	} else {
		
		raiz->info2 = raiz->info1;
		raiz->dir = raiz->cen;
		raiz->info1 = info;
		raiz->cen = filho; }
	return raiz; }

// Função que quebra o nó em dois.
void quebraNO(NO **raiz, INFO **info, INFO **sobe, NO **maior) {

	if( *maior == NULL )
		*maior = alocaNO();

	if( (*info)->informacao < (*raiz)->info1->informacao ){
		// Info1 da raiz é o valor central.
		*sobe = (*raiz)->info1;
		(*raiz)->info1 = *info;
		(*maior)->info1 = (*raiz)->info2;
	
	} else if( (*info)->informacao < (*raiz)->info2->informacao ) {
		// a nova info é o valor central.
		*sobe = *info;
		(*maior)->info1 = (*raiz)->info2;

	} else {
		// Info2 da raiz é o valor central.
		*sobe = (*raiz)->info2;
		(*maior)->info1 = *info;
		
	}

	info = NULL;
	(*raiz)->info2 = NULL;
	*maior = ajustaNMRS(*maior);
	*raiz = ajustaNMRS(*raiz); }

// Função que insere a informação na raiz FOLHA.
void raizFOLHA(NO **raiz, INFO **info, NO **pai, INFO **sobe, NO **maior, ARVORE **arvore){

	NO *novo;

	if( (*raiz)->nmrINFO == 1 ){
		// Raiz só possui uma única informação.
		*raiz = addNO(*raiz, *info, NULL);
		*raiz = ajustaNMRS(*raiz);
	

	} else {
		// Raiz possui duas informações e terá que ser quebrado.
		quebraNO(raiz, info, sobe, maior);
		if( *pai == NULL ){
			// Raiz não possui um pai.
			novo = alocaNO();

			novo->info1 = *sobe;
			novo->esq = *raiz;
			novo->cen = *maior;
			novo = ajustaNMRS(novo);

			(*arvore)->raiz = novo;
			*sobe = NULL;
		}
	} }


void ajustaSOBE(NO **raiz, INFO **sobe, NO **pai, NO **maior, ARVORE **arvore){

	NO *novo;
	NO *maior2;
	INFO *sobe2;

	novo = NULL;
	maior2 = NULL;
	sobe2 = NULL;

	if( (*raiz)->nmrINFO == 1 ){
		// A raiz possui espaço, então o valor que sobe será adicionado nele.
		*raiz = addNO(*raiz, *sobe, *maior);
		// (*raiz)->dir = *maior;
		*maior = NULL;
		*sobe = NULL;
		*raiz = ajustaNMRS(*raiz);
	
	} else {
		// A raiz não possui mais espaço. Então deverá ser quebrado.
		quebraNO(raiz, sobe, &sobe2, &maior2);

		maior2->esq = (*raiz)->dir;
		maior2->cen = *maior;
		(*raiz)->dir = NULL;

		maior2 = ajustaNMRS(maior2);
		*raiz = ajustaNMRS(*raiz);

		if( *pai == NULL ){	
			// O pai dessa raiz é nula.
			novo = alocaNO();
			novo->info1 = sobe2;
			novo->esq = *raiz;
			novo->cen = maior2;
			*sobe = NULL;
			*maior = NULL;
			sobe2 = NULL;
			maior = NULL;

			novo = ajustaNMRS(novo);

			(*arvore)->raiz = novo;
		
		} else {
			// O pai dessa raiz não é NULA.
			*sobe = sobe2;
			*maior = maior2;
		}

	} }

// Função que insere um valor na árvore.
void inserir(NO **raiz, INFO **info, NO **pai, INFO **sobe, NO **maior, ARVORE **arvore) {

	NO **destino;

	
	if( *raiz == NULL ){
		// Primeiro item a ser inserido na árvore.
		*raiz = alocaNO();
		(*raiz)->info1 = *info;
		*raiz = ajustaNMRS(*raiz);

	} else if ((*raiz)->nmrFILHOS == 0 ){
		// A raiz é folha!
		raizFOLHA(raiz, info, pai, sobe, maior, arvore);

	} else {
		// A raiz não é NULA.
		// A raiz não é folha.
		if( (*info)->informacao < (*raiz)->info1->informacao ){
			inserir(&(*raiz)->esq, info, raiz, sobe, maior, arvore);
		} else if( (*info)->informacao > (*raiz)->info1->informacao && (*raiz)->nmrINFO == 1 ) {
			inserir(&(*raiz)->cen, info, raiz, sobe, maior, arvore);
		} else if( (*info)->informacao < (*raiz)->info2->informacao && (*raiz)->nmrINFO == 2 ) {
			inserir(&(*raiz)->cen, info, raiz, sobe, maior, arvore);
		} else {
			inserir(&(*raiz)->dir, info, raiz, sobe, maior, arvore);
		}


		if( *sobe != NULL )
			ajustaSOBE(raiz, sobe, pai, maior, arvore);
	}
}

void gestaoLER(ARVORE *arvore){
	INFO *info, *sobe;
	NO *pai, *maior;
	sobe = NULL;
	pai = maior = NULL;
	info = ler();
	inserir(&arvore->raiz, &info, &pai, &sobe, &maior, &arvore); }


/* ----------------------------------- APRESENTAÇÃO ----------------------------------- */

// Função que imprime os itens de uma árvore.
void imprimir(NO *raiz){

    if (raiz != NULL){ 
    	if(raiz->info1 != NULL)
        	printf("info1 = %d | ", raiz->info1->informacao);
        else
        	printf("info1 = NULL | ");

        if(raiz->info2 != NULL)
        	printf("info2 = %d  \n", raiz->info2->informacao);
        else
        	printf("info2 = NULL \n");
        imprimir(raiz->esq);
        imprimir(raiz->cen);
        imprimir(raiz->dir);
    } 
}