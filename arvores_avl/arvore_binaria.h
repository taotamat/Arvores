//----------------------------------------------------------//
// Structs:

typedef struct NO {
	int dado;
	int altura;
	struct NO *esq; // NO esquerdo
	struct NO *dir; // NO direito
} NO;

typedef struct ARVORE{
	int tam; // Quantidade de NO presentes na árvore;
	NO *raiz; // Ponteiro que aponta para a raiz da árvore;
} ARVORE;


// Declarações das funções:
void ast();
NO *alocaNO();
ARVORE *alocaARV();
void preordem(NO *aux);
void inordem(NO *aux);
void posordem(NO *aux);
void inserir(ARVORE *arvore, NO **aux, NO *novo);
void ler(NO *no);
void gestaoLER(ARVORE *arvore);
NO *busca(NO *aux, int num, int *count);
void gestaoBUSCA(NO *aux);
int qnt_filhos(NO *aux);
NO *remove_pai_um(NO *raiz);
NO *maior_da_esquerda(NO *aux);
void remove_com_dois_filhos(NO **aux);
void remover(ARVORE *arvore, NO **raiz, int valor);
void gestaoREMOVE(ARVORE *arvore);