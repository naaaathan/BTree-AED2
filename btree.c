#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"btree.h"

#define M 4


struct ArvB   //FEITA
{
    int   qtd;
    int  chaves[M];
    bool ehFolha;
    struct ArvB *p[M+1];
};

ArvB cria_ArvB()  //FEITA
{

    ArvB p;
    p =  (ArvB) malloc(sizeof(struct ArvB));
    p->qtd = 0;
    p->ehFolha = true;

    return p;
}

int libera_ArvB(ArvB raiz)  //FAZENDO==============================>(NAO ESTA DANDO CERTO )
{
    if(raiz->qtd == 0)
    {
        printf("Nao existe no nessa arvore... \nNao sera preciso libera-la...\n\n\n");
        return 0;
        //NAO EXISTE ELEMENTO NA RAIZ, LOGO, A ARVORE NÃO TEM NADA A SER LIBERADO
    }

    int j;


    if(!raiz->ehFolha) // SE FOR UM NO NÃO FOLHA{
    {
        for(j = 0; j < raiz->qtd; j++)
        {
            libera_ArvB(raiz->p[j]);
        }
    }

    raiz->qtd = 0;

    free(raiz);// LIBERA

    return 1;
}


int retornaValor(int n, int *vet, int valor)
{

    int min;
    int max;
    int meio;

    min = -1;
    max = n;

    while(min + 1 < max) {
        meio = (min+max)/2;
        if(vet[meio] == valor) {
            return meio;
        } else if(vet[meio] < valor) {
            min = meio;
        } else {
            max = meio;
        }
    }

    return max;
}



ArvB insere_ArvB_aux(ArvB b, int valor, int *mediano)
{
    int pos;
    int meio;
    ArvB b2;

    pos = retornaValor(b->qtd, b->chaves, valor);

    if(pos < b->qtd && b->chaves[pos] == valor) {

        return 0;
    }

    if(b->ehFolha) {

        memcpy(&b->chaves[pos+1], &b->chaves[pos], sizeof(*(b->chaves)) * (b->qtd - pos));
        b->chaves[pos] = valor;
        b->qtd++;

    } else {

        b2 = insere_ArvB_aux(b->p[pos], valor, &meio);

        if(b2) {

            memcpy(&b->chaves[pos+1], &b->chaves[pos], sizeof(*(b->chaves)) * (b->qtd - pos));

            memcpy(&b->p[pos+2], &b->p[pos+1], sizeof(*(b->chaves)) * (b->qtd - pos));

            b->chaves[pos] = meio;
            b->p[pos+1] = b2;
            b->qtd++;
        }
    }


    if(b->qtd >= M) {
        meio = b->qtd/2;

        *mediano = b->chaves[meio];

        b2 = malloc(sizeof(*b2));

        b2->qtd = b->qtd - meio - 1;
        b2->ehFolha = b->ehFolha;

        memcpy(b2->chaves, &b->chaves[meio+1], sizeof(*(b->chaves)) * b2->qtd);
        if(!b->ehFolha) {
            memcpy(b2->p, &b->p[meio+1], sizeof(*(b->p)) * (b2->qtd + 1));
        }

        b->qtd = meio;

        return b2;

    } else {

        return 0;

    }
}

void insere_ArvB(ArvB b, int valor)
{
    ArvB b1;
    ArvB b2;
    int mediano;

    b2 = insere_ArvB_aux(b, valor, &mediano);

    b1 = malloc(sizeof(*b1));

    memcpy(b1, b, sizeof(*b));

    b->qtd = 1;
    b->ehFolha = false;
    b->chaves[0] = mediano;
    b->p[0] = b1;
    b->p[1] = b2;

}

int ehVazia_ArvB(ArvB raiz)  //FEITA
{

    if(raiz->qtd == 0)
    {
        printf("A arvore esta vazia...\n\n");
        return 1;
    }

    else
    {
        printf("Esta arvore nao esta vazia...\n\n");
        return 0;
    }


}

int totalNO_ArvB(ArvB raiz) // FAZENDO
{

    int cont ;


    if(ehVazia_ArvB(raiz) == 1 || raiz == NULL)
        return 0;



    int contador = (raiz)->qtd ;
    int i;
    for(i=0; i<(raiz)->qtd+1; i++)
    {
        if((raiz)->p[i]== NULL)
            cont ++;      // PARA POSTERIORMENTE CHECAR SE ELA NÃO POSSUI NENNHUM FILHO (É UM NÓ FOLHA)
    }

    if(cont == (raiz)->qtd+1 )
    {
        return contador;// CASO O NO RAIZ FOR UM NO FOLHA(Nao possui filhos) Retorne a quantidade de elements no nó
    }

    ArvB aux = raiz;


    for(i=0; i<aux->qtd+1; i++)
    {
        printf("Contador antes de somar --> %i \n",contador);
        contador = contador + totalNO_ArvB((raiz)->p[i]); //UTILIZA DA RECURSAO PARA SOMAR A QUANTIDADE DE CADA NO NO CONTADOR
        printf("Contador depois de somar --> %i \n",contador);
    }
    return contador;
}

int busca_ArvB(ArvB raiz, int valor)  //FEITA
{

    if((raiz)->qtd == 0 || raiz == NULL)
        return 0;// ELEMENTO NÃO ENCONTRADO POIS A LISTA ESTÁ VAZIA

    int i;

    for(i=0; i<(raiz)->qtd; i++)
    {
        if(valor == (raiz)->chaves[i])
        {
            printf("Elemento achado...\n");
            return 1;// ACHAMOS O ELEMENTO
        }
        else
        {
            if((raiz)->p[i] != NULL)
                busca_ArvB((raiz)->p[i],valor);
        }
    }

    printf("Nao foi achado o elemento...\n Retornando 0...\n");
    return 0;


}
