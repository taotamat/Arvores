// arvore23.h
// Structs:
typedef struct INFO {
	int informacao;
} INFO;

typedef struct NO {

	INFO *info1;
	INFO *info2;

	struct NO *esq;
	struct NO *cen;
	struct NO *dir;

	int nmrINFO; // Número informações cadastradas.
	int nmrFILHOS; // Numero de filhos que o Nó possui.

} NO;


typedef struct ARVORE {
	NO *raiz;
	int tam; // Qnt de Nó cadastrados na árvore;
} ARVORE;
//
//
//
//
void ast();
INFO *alocaINFO();
NO *alocaNO();
ARVORE *alocaARV();
int qntFILHOS(NO *no);
int qntINFO(NO *no);
NO *ajustaNMRS(NO *no);
INFO *ler();
NO *addNO(NO *raiz, INFO *info, NO *filho);
void quebraNO(NO **raiz, INFO **info, INFO **sobe, NO **maior); 
void raizFOLHA(NO **raiz, INFO **info, NO **pai, INFO **sobe, NO **maior, ARVORE **arvore);
NO *verDESTINO(NO *raiz, INFO *info);
void ajustaSOBE(NO **raiz, INFO **sobe, NO **pai, NO **maior, ARVORE **arvore);
void inserir(NO **raiz, INFO **info, NO **pai, INFO **sobe, NO **maior, ARVORE **arvore);
void gestaoLER(ARVORE *arvore);
void imprimir(NO *raiz);