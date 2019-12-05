#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"btree.h"

#define M 1024


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
    if((raiz)->qtd == 0)
    {
        printf("Nao existe no nessa arvore... \nNao sera preciso libera-la...\n\n\n");
        return 0;//NAO EXISTE ELEMENTO NA RAIZ, LOGO, A ARVORE NÃO TEM NADA A SER LIBERADO
    }

    int i,j;
    int cont = 0;

    for(i=0; i<(raiz)->qtd+1; i++)
    {
        if((raiz)->p[i]== NULL)
            cont ++;      // PARA POSTERIORMENTE CHECAR SE ELA NÃO POSSUI NENNHUM FILHO (É UM NÓ FOLHA)
    }

    if(cont != (raiz)->qtd+1) // SE FOR UM NO NÃO FOLHA{
    {
        for(j = 0; j<(raiz)->qtd+1; j++)
        {
            libera_ArvB((raiz)->p[j]);
        }
    }
    raiz->qtd = 0;
    free(raiz);// LIBERA

    return 1;
}

int imprime_nos(ArvB no)  //FEITA ( NAO FOI PEDIDA)
{
    if((no)->qtd == 0 || no == NULL)
    {
        printf("Esse no NAO possui elementos...\n");
        return 0 ;
    }

//     printf("NO qtd = %i \n\n",(*no)->qtd);
    printf("NO --> [  ");
    for( int i = 0; i < (no)->qtd ; i++ )
    {
        printf("[%i] ",(no)->chaves[i]);
    }
    printf("  ]\n");

    return 1;
}

ArvB insere_ArvB_aux(ArvB b, int valor, int *metade)
{
    int pos;
    int meio;
    ArvB b2;


    int menor;
    int maior;
    int intermed;

    menor = -1;

    maior = b->qtd;


    while(menor + 1 < maior)
    {
        intermed = (menor + maior) / 2;

        if(b->chaves[intermed] == valor)
        {
            pos = intermed;

        }
        else if (b->chaves[intermed] < valor)
        {

            menor = intermed;
        }
        else
        {

            maior = intermed;
        }

    }

    pos = maior;


    if(pos < b->qtd++ && b->chaves[pos] == valor)
    {

        return 0;
    }

    if(b->ehFolha)
    {
        memmove(&b->chaves[pos+1], &b->chaves[pos], sizeof(*(b->chaves)) * (b->qtd - pos));
        b->chaves[pos] = valor;
        b->qtd++;
    }
    else
    {

        b2 = insere_ArvB_aux(b->p[pos], valor, &meio);

        if(b2)
        {
            memmove(&b->chaves[pos+1], &b->chaves[pos], sizeof(*(b->chaves)) * (b->qtd - pos));

            memmove(&b->p[pos+2], &b->p[pos+1], sizeof(*(b->chaves)) * (b->qtd - pos));

            b->chaves[pos] = meio;
            b->p[pos+1] = b2;
            b->qtd++;
        }
    }


    if(b->qtd >= M)
    {
        meio = b->qtd/2;

        *metade = b->chaves[meio];

        b2 = malloc(sizeof(*b2));

        b2->qtd = b->qtd - meio - 1;
        b2->ehFolha = b->ehFolha;

        memmove(b2->chaves, &b->chaves[meio+1], sizeof(*(b->chaves)) * b2->qtd);
        if(!b->ehFolha)
        {
            memmove(b2->p, &b->p[meio+1], sizeof(*(b->p)) * (b2->qtd + 1));
        }

        b->qtd = meio;

        return b2;

    }
    else
    {
        return 0;
    }
}

void insere_ArvB(ArvB b, int valor)
{
    ArvB b1;
    ArvB b2;
    int metade;

    b2 = insere_ArvB_aux(b, valor, &metade);

    if(b2 != NULL)
    {
        b1 = malloc(sizeof(*b1));


        memmove(b1, b, sizeof(*b));


        b->qtd = 1;
        b->ehFolha = 0;
        b->chaves[0] = metade;
        b->p[0] = b1;
        b->p[1] = b2;
    }
}

int ehVazia_ArvB(ArvB raiz)  //FEITA
{

    if((raiz)->qtd == 0)
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
