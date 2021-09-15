#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//----------------------------------------------------------//
// Structs:

typedef struct NO {
	int dado;
	struct NO *esq; // NO esquerdo
	struct NO *dir; // NO direito
} NO;

typedef struct ARVORE{
	int tam; // Quantidade de NO presentes na árvore;
	NO *raiz; // Ponteiro que aponta para a raiz da árvore;
} ARVORE;


//----------------------------------------------------------//
// Apresentação de texto repetidos:

void ast(){

	printf("-------------------------------------------------------------\n"); }

//----------------------------------------------------------//
// Alocações:

// Função que aloca um novo espaço para o NO;
NO *alocaNO(){

	NO *novo;
	novo = (NO *) malloc(sizeof(NO));
	if(novo != NULL) {
		(*novo).esq = NULL;
		(*novo).dir = NULL;
	} else printf("Erro ao alocar o novo NO!\n");
	return novo; }

// Função que aloca um novo espaço para a Árvore
ARVORE *alocaARV(){
	ARVORE *nova;
	nova = (ARVORE *) malloc(sizeof(ARVORE));
	if(nova != NULL) {
		(*nova).tam = 0;
		(*nova).raiz = NULL;
	} else printf("Erro ao alocar a nova ARVORE!\n");
	return nova; }

//----------------------------------------------------------//
// Funções básicas da árvore:

// Função que apresenta todos os NOs da árvore em Pré-Ordem
void preordem(NO *aux) {
	// Raiz, esquerda, direita;
	if(aux != NULL){
		printf("%d ", aux->dado);
		preordem(aux->esq);
		preordem(aux->dir);
	} }

// Função que apresenta todos os NOs da árvore em IN-Ordem
void inordem(NO *aux) {
	// esquerda, Raiz, direita;
	if(aux != NULL){
		inordem(aux->esq);
		printf("%d ", aux->dado);
		inordem(aux->dir);
	} }

// Função que apresenta todos os NOs da árvore em Pós-Ordem
void posordem(NO *aux) {
	// esquerda, direita, raiz;
	if(aux != NULL){
		posordem(aux->esq);
		posordem(aux->dir);
		printf("%d ", aux->dado);
	} }

// Função recursiva que insere o novo NO na árvore.
void inserir(ARVORE *arvore, NO **aux, NO *novo) {

	if( *aux == NULL ){
		// arvore não possue uma raiz, então o novo é a nova raiz.
		*aux = novo;
		arvore->tam = arvore->tam + 1;
	} else if( novo->dado < (*aux)->dado && (*aux)->esq != NULL ) {
		// Se o dado de novo NO for menor e o filho esquerdo do NO aux NÃO FOR NULL, 
		// Então o novo NO vai ser comparado ao filho esquerdo do NO aux.
		inserir(arvore, &((*aux)->esq), novo);
	} else if( novo->dado < (*aux)->dado && (*aux)->esq == NULL ) {
		// Se o dado de novo NO for menor e o filho esquerdo do NO aux FOR NULL, 
		// Então o novo NO será o novo filho esquerdo do NO aux.
		(*aux)->esq = novo;
		arvore->tam = arvore->tam + 1;
	} else if( novo->dado > (*aux)->dado && (*aux)->dir != NULL ) {
		// Se o dado de novo NO for maior e o filho direito do NO aux NÃO FOR NULL, 
		// Então o novo NO vai ser comparado ao filho direito do NO aux.
		inserir(arvore, &((*aux)->dir), novo);
	} else if( novo->dado > (*aux)->dado && (*aux)->dir == NULL ) {
		// Se o dado de novo NO for maior e o filho direito do NO aux FOR NULL, 
		// Então o novo NO será o novo filho direito do NO aux.
		(*aux)->dir = novo;
		arvore->tam = arvore->tam + 1;
	} }

// Função que ler os dados do novo NO;
void ler(NO *no){
	printf("Digite um numero para o novo NO: ");
	scanf("%d", &(no->dado)); }

// Função que aloca espaço para um novo NO e chama a função de leitura.
void gestaoLER(ARVORE *arvore) {
	NO *novo;
	novo = alocaNO();
	ler(novo);
	inserir(arvore, &(arvore->raiz), novo); }

// Função que busca um valor na árvore;
NO *busca(NO *aux, int num, int *count) {

	NO *resultado;
	resultado = NULL;

	if( aux != NULL ) {

		printf("aux->dado = %d \n", aux->dado);
		*count = *count + 1;

		if( aux->dado == num )
			resultado = aux;
		else if( num < aux->dado )
			resultado = busca(aux->esq, num, count);
		else if( num > aux->dado )
			resultado = busca(aux->dir, num, count);
	}

	return resultado; }

// Função que solicita que o usuário digite um valor para ser realizado a busca na árvore;
void gestaoBUSCA(NO *aux) {

	int num;
	int count = 0;
	NO *encontrado;

	printf("Digite o número que você procura: ");
	scanf("%d", &num);

	printf("\n\nBuscando...\n");
	encontrado = busca(aux, num, &count);
	printf("\n");

	if(encontrado != NULL){
		printf("Número encontrado! \n");
		printf("Qnt de passos necessários para encontrar o número: %d \n", count);
	} else printf("O número nao foi encontrado na arvore! \n"); }

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

	copia = raiz->dado;
	raiz->dado = aux->dado;
	aux->dado = copia;

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
		printf("aux->dado = %d \n", aux->dado);

		if( aux->dir == NULL )
			resultado = aux;
		else
			resultado = maior_da_esquerda(aux->dir);
	}

	return resultado; }

// Função que remove um NO que possui dois filhos;
void remove_com_dois_filhos(NO **aux){
	
	NO *maior;
	int aux2; // Tem que ser do tipo do conteudo do NO.

	// Procurar o maior da esquerda:
	maior = maior_da_esquerda((*aux)->esq);

	if(maior != NULL) {
		// Tirar as ligações
		(*aux)->esq = maior->esq;

		// Troca dos dados:
		aux2 = (*aux)->dado;
		(*aux)->dado = maior->dado;
		maior->dado = aux2;
		free(maior);
		maior = NULL;
	} }

// Função que chama as funções de remover
void remover(ARVORE *arvore, NO **raiz, int valor){
	NO *aux;
	int qnt;

	if( *raiz == NULL ){
		// raiz é nula. o valor não foi encontrado.
		aux = NULL;
	} else if( (*raiz)->dado == valor ){
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

	} else if( valor < (*raiz)->dado ) {
		remover(arvore, &(*raiz)->esq, valor);

	} else if( valor > (*raiz)->dado ) {
		remover(arvore, &(*raiz)->dir, valor);
	} }

// Função que solicita que o usuário leia um número que seja removido.
void gestaoREMOVE(ARVORE *arvore) {
	int num;
	int count = 0;
	NO *encontrado;

	printf("Digite o numero que deseja remover: ");
	scanf("%d", &num);

	remover(arvore, &arvore->raiz, num);
	printf("Removido!\n"); }

//----------------------------------------------------------//
// Menu Principal:

int menu(){

	// FUNÇÃO QUE APRESENTA UM MENU.

	int op;
	printf("\n\n");
	
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