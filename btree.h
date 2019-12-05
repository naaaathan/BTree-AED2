typedef struct ArvB *ArvB;

ArvB cria_ArvB() ;
int busca_ArvB(ArvB raiz, int valor);
int totalNO_ArvB(ArvB raiz);
int ehVazia_ArvB(ArvB raiz) ;
void insere_ArvB(ArvB raiz, int valor);
ArvB insere_ArvB_aux(ArvB b, int valor, int *meio);
int imprime_nos(ArvB no) ;
int libera_ArvB(ArvB raiz);

