#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "arvore_rubro_negra.h"
#include "ajusta_cor.h"

#define RED 1
#define BLACK 0


void ast(){

	printf("-------------------------------------------------------------\n"); }


/*-------Alocações---------*/

NO *alocaNO(){
	NO *novo;
	novo = (NO *) malloc(sizeof(NO));
	novo->esq = NULL;
	novo->dir = NULL;
	novo->cor = RED;
	return novo; }

ARVORE *alocaARV(){
	ARVORE *nova;
	nova = (ARVORE *) malloc(sizeof(ARVORE));
	nova->tam = 0;
	nova->raiz = NULL;
	return nova; }


/*-------Gestão básica das CORES---------*/

int cor(NO *H){
	int resultado;
    if(H == NULL)
        resultado = BLACK;
    else
        resultado = H->cor; 
    return resultado; }

void trocaCor(NO *H){
    H->cor = !H->cor;
    if(H->esq != NULL)
        H->esq->cor = !H->esq->cor;
    if(H->dir != NULL)
        H->dir->cor = !H->dir->cor; }

void apresentaCOR(int cor){
	if(cor == RED)
		printf("- \tVERMELHO     |\n");
	else
		printf("- \tPRETO        |\n"); }

/*-------Apresentações---------*/

// Função que apresenta todos os NOs da árvore em Pré-Ordem
void preordem(NO *aux) {
	// Raiz, esquerda, direita;
	if(aux != NULL){
		printf("%d ", aux->info);
		apresentaCOR(aux->cor);
		preordem(aux->esq);
		preordem(aux->dir);
	} }

// Função que apresenta todos os NOs da árvore em IN-Ordem
void inordem(NO *aux) {
	// esquerda, Raiz, direita;
	if(aux != NULL){
		inordem(aux->esq);
		printf("%d ", aux->info);
		apresentaCOR(aux->cor);
		inordem(aux->dir);
	} }

// Função que apresenta todos os NOs da árvore em Pós-Ordem
void posordem(NO *aux) {
	// esquerda, direita, raiz;
	if(aux != NULL){
		posordem(aux->esq);
		posordem(aux->dir);
		printf("%d ", aux->info);
		apresentaCOR(aux->cor);
	} }

/*----------Inserções---------*/

// Função recursiva que insere o novo NO na árvore.
void inserir(ARVORE *arvore, NO **aux, NO *novo) {

	if( *aux == NULL ){
		// arvore não possue uma raiz, então o novo é a nova raiz.
		*aux = novo;
		arvore->tam = arvore->tam + 1;
	} else if( novo->info < (*aux)->info && (*aux)->esq != NULL ) {
		// Se o dado de novo NO for menor e o filho esquerdo do NO aux NÃO FOR NULL, 
		// Então o novo NO vai ser comparado ao filho esquerdo do NO aux.
		inserir(arvore, &((*aux)->esq), novo);
	} else if( novo->info < (*aux)->info && (*aux)->esq == NULL ) {
		// Se o dado de novo NO for menor e o filho esquerdo do NO aux FOR NULL, 
		// Então o novo NO será o novo filho esquerdo do NO aux.
		(*aux)->esq = novo;
		arvore->tam = arvore->tam + 1;
	} else if( novo->info > (*aux)->info && (*aux)->dir != NULL ) {
		// Se o dado de novo NO for maior e o filho direito do NO aux NÃO FOR NULL, 
		// Então o novo NO vai ser comparado ao filho direito do NO aux.
		inserir(arvore, &((*aux)->dir), novo);
	} else if( novo->info > (*aux)->info && (*aux)->dir == NULL ) {
		// Se o dado de novo NO for maior e o filho direito do NO aux FOR NULL, 
		// Então o novo NO será o novo filho direito do NO aux.
		(*aux)->dir = novo;
		arvore->tam = arvore->tam + 1;
	} 

	gestaoBALANCEAMENTO(arvore, aux); }

// Função que ler os dados do novo NO;
void ler(NO *no){
	printf("Digite um numero para o novo NO: ");
	scanf("%d", &(no->info)); }

// Função que aloca espaço para um novo NO e chama a função de leitura.
void gestaoLER(ARVORE *arvore) {
	NO *novo;
	novo = alocaNO();
	ler(novo);
	inserir(arvore, &(arvore->raiz), novo); }


/*---------- - Remoções - ---------*/


// Função que retorna a quantidade de filhos que o NO possui.
int qnt_filhos(NO *aux) {
	// retorna a quantidade de filhos que o NO aux possui;
	int qnt;
	if( aux->esq != NULL && aux->dir != NULL )
		qnt = 2;
	else if( aux->esq == NULL && aux->dir == NULL  )
		qnt = 0;
	else
		qnt = 1;
	return qnt; }

// Remover um NO que possui 1 filho.
	// Ele realiza a troca dos valores
	// E em seguida remove a folha;
NO *remove_pai_um(NO *raiz){
	
	NO *aux;
	int copia;

	if( raiz->esq != NULL )
		aux = raiz->esq;
	else
		aux = raiz->dir;

	copia = raiz->info;
	raiz->info = aux->info;
	aux->info = copia;

	raiz->esq = aux->esq;
	raiz->dir = aux->dir;

	free(aux);
	aux = NULL;

	return raiz; }


// Função que retorna o NO que possui o maior valor que se encontra na esquerda do NO aux;
NO *maior_da_esquerda(NO *aux){
	
	NO *resultado;
	resultado = NULL;

	if( aux != NULL ){
		// printf("aux->dado = %d \n", aux->dado);
		if( aux->dir == NULL )
			resultado = aux;
		else
			resultado = maior_da_esquerda(aux->dir); }

	return resultado; }


// Função que remove um NO que possui dois filhos;
void remove_com_dois_filhos(NO **raiz){
	
	NO *no;
	int info;
	
	no = maior_da_esquerda( (*raiz)->esq );

	if( no != NULL ) {

		/* Troca dos dados */
		info = (*raiz)->info;
		(*raiz)->info = no->info;
		no->info = info;

		(*raiz)->esq = no->esq;
		no->esq = NULL;

		free(no);
	} }


// Função que chama as funções de remover
void remover(ARVORE *arvore, NO **raiz, int valor){
	
	NO *aux;
	int qnt;
	int resultado = 0;

	if( *raiz == NULL ){
		// raiz é nula. o valor não foi encontrado.
		printf("Valor não foi encontrado! \n");
		// aux = NULL;
	} else if( (*raiz)->info == valor ){
		// é o mesmo valor!
		qnt = qnt_filhos(*raiz);

		if(qnt == 0){
			free(*raiz);
			*raiz = NULL;
		} else if(qnt == 1)
			*raiz = remove_pai_um(*raiz);
		else
			remove_com_dois_filhos(raiz);
		
		arvore->tam = arvore->tam - 1;
		printf("Removido! \n");

	} else if( valor < (*raiz)->info ) {
		remover(arvore, &(*raiz)->esq, valor);
	} else if( valor > (*raiz)->info ) {
		remover(arvore, &(*raiz)->dir, valor); } 

	gestaoBALANCEAMENTO(arvore, raiz); }


// Função que chama ler o valor a ser removido e chama a remoção
void gestaoREMOVER(ARVORE *arvore){

	int valor;
	printf("Digite o valor que deseja ser removido: ");
	scanf("%d", &valor);
	remover(arvore, &arvore->raiz, valor); }
