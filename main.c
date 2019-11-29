#include<stdio.h>
#include<math.h>
#include"btree.h"
#define M 4

typedef struct ArvB {
        int    qtd;
        int  chaves[M - 1];
        struct ArvB *p[M];
} *ArvB;


int main()
{
      ArvB a;

      a = cria_ArvB();

      libera_ArvB(&a);

      ehVazia_ArvB(&a);

      insere_ArvB(&a,12);

      imprime_nos(&a);

      libera_ArvB(&a);

      imprime_nos(&a);

      ehVazia_ArvB(&a);

      busca_ArvB(&a,12);

      printf("O numero total de nos eh de %i",totalNO_ArvB(&a));


    return 0;
}
