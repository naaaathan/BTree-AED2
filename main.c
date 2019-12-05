#include<stdio.h>
#include<math.h>
#include"btree.h"
#include<stdbool.h>

int main()
{
    ArvB a;

    a = cria_ArvB();

    insere_ArvB(a,10);
    insere_ArvB(a,12);
    insere_ArvB(a,15);
    insere_ArvB(a,19);
    insere_ArvB(a,21);

    imprime_nos(a);


    return 0;
}
