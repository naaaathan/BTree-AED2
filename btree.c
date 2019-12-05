#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"btree.h"

#define M 4


struct ArvB  
{
    int   qtd;
    int  chaves[M];
    bool ehFolha;
    struct ArvB *p[M+1];
};

ArvB cria_ArvB() 
{

    ArvB p;
    p =  (ArvB) malloc(sizeof(struct ArvB));
    p->qtd = 0;
    p->ehFolha = true;

    return p;
}

int libera_ArvB(ArvB raiz)  
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

    free(raiz);

    return 1;
}

void insere_ArvB(ArvB arv, int valor)
{
    ArvB arv1;
    ArvB arv2;
    int mediano;

    arv2 = insere_ArvB_aux(arv, valor, &mediano);

    arv1 = malloc(sizeof(*arv1));

    memcpy(arv1, arv, sizeof(*arv));

    arv->qtd = 1;
    arv->ehFolha = false;
    arv->chaves[0] = mediano;
    arv->p[0] = arv1;
    arv->p[1] = arv2;

}

int ehVazia_ArvB(ArvB raiz) 
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

int totalNO_ArvB(ArvB raiz) 
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

int busca_ArvB(ArvB raiz, int valor)
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

//FUNÇÕES AUXILIARES PARA A INSERE

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


ArvB insere_ArvB_aux(ArvB arv, int valor, int *mediano)
{
    int pos;
    int meio;
    ArvB arv2;

    pos = retornaValor(arv->qtd, arv->chaves, valor);

    if(pos < arv->qtd && arv->chaves[pos] == valor) {

        return 0;
    }

    if(arv->ehFolha) {

        memcpy(&arv->chaves[pos+1], &arv->chaves[pos], sizeof(*(arv->chaves)) * (arv->qtd - pos));
        arv->chaves[pos] = valor;
        arv->qtd++;

    } else {

        arv2 = insere_ArvB_aux(arv->p[pos], valor, &meio);

        if(arv2) {

            memcpy(&arv->chaves[pos+1], &arv->chaves[pos], sizeof(*(arv->chaves)) * (arv->qtd - pos));

            memcpy(&arv->p[pos+2], &arv->p[pos+1], sizeof(*(arv->chaves)) * (arv->qtd - pos));

            arv->chaves[pos] = meio;
            arv->p[pos+1] = arv2;
            arv->qtd++;
        }
    }


    if(arv->qtd >= M) {
        meio = arv->qtd/2;

        *mediano = arv->chaves[meio];

        arv2 = malloc(sizeof(*arv2));

        arv2->qtd = arv->qtd - meio - 1;
        arv2->ehFolha = arv->ehFolha;

        memcpy(arv2->chaves, &arv->chaves[meio+1], sizeof(*(arv->chaves)) * arv2->qtd);
        if(!arv->ehFolha) {
            memcpy(arv2->p, &arv->p[meio+1], sizeof(*(arv->p)) * (arv2->qtd + 1));
        }

        arv->qtd = meio;

        return arv2;

    } else {

        return 0;

    }
}
