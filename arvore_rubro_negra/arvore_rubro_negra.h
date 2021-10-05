typedef struct NO {
    int info;
    struct NO *esq;
    struct NO *dir;
    int cor;
} NO;

typedef struct ARVORE {
	NO *raiz;
	int tam;
} ARVORE;

// funcoes da arvore_rubro_negra_minha.h
void ast();
NO *alocaNO();
ARVORE *alocaARV();
int cor(NO *H);
void trocaCor(NO *H);
void apresentaCOR(int cor);
void preordem(NO *aux);
void inordem(NO *aux);
void posordem(NO *aux);
void inserir(ARVORE *arvore, NO **aux, NO *novo);
void ler(NO *no);
void gestaoLER(ARVORE *arvore);
int qnt_filhos(NO *aux);
NO *remove_pai_um(NO *raiz);
NO *maior_da_esquerda(NO *aux);
void remove_com_dois_filhos(NO **raiz);
void remover(ARVORE *arvore, NO **raiz, int valor);
void gestaoREMOVER(ARVORE *arvore);