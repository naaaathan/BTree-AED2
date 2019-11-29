#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define M 4

typedef struct ArvB   //FEITA
{
    int   qtd;
    int  chaves[M - 1];
    struct ArvB *p[M];
} *ArvB;

ArvB* cria_ArvB()  //FEITA
{

    ArvB p;
    p = (ArvB) malloc(sizeof(struct ArvB));
    p->qtd = 0;

    int i = 0;
    for(; i<M; i++)
    {
        p->p[i] = NULL;
    }

    return p;
}

void libera_ArvB(ArvB *raiz)  //FAZENDO==============================>(NAO ESTA DANDO CERTO )
{
    if((*raiz)->qtd == 0)
    {
        printf("Nao existe no nessa arvore... \nNao sera preciso libera-la...\n\n\n");
        return 0;//NAO EXISTE ELEMENTO NA RAIZ, LOGO, A ARVORE NÃO TEM NADA A SER LIBERADO
    }

    int i,j;
    int cont = 0;

    for(i=0; i<(*raiz)->qtd+1; i++)
    {
        if((*raiz)->p[i]== NULL)
            cont ++;      // PARA POSTERIORMENTE CHECAR SE ELA NÃO POSSUI NENNHUM FILHO (É UM NÓ FOLHA)
    }

    if(cont != (*raiz)->qtd+1) // SE FOR UM NO NÃO FOLHA{
    {
        for(j = 0; j<(*raiz)->qtd+1; j++)
        {
            libera_ArvB((*raiz)->p[j]);
        }
    }
    (*raiz)->qtd == 0;
    free(raiz);// LIBERA
}

int imprime_nos(ArvB *no)  //FEITA ( NAO FOI PEDIDA)
{
    if((*no)->qtd == 0 || no == NULL)
    {
        printf("Esse no NAO possui elementos...\n");
        return 0 ;
    }
    int  i = 0;
//     printf("NO qtd = %i \n\n",(*no)->qtd);
    printf("NO --> [  ");
    for(; i<(*no)->qtd; i++)
    {
        printf("[%i] ",(*no)->chaves[i]);
    }
    printf("  ]\n");
}

int insere_ArvB(ArvB *raiz, int valor) //FAZENDO=====================> (DIFICIL)
{

    if((*raiz)->qtd == 0)
    {
        (*raiz)->qtd++;
        (*raiz)->chaves[0]= valor;
        return 0;

    }
//ArvB aux = raiz;
//   for(i=0;i<aux->qtd)}
}

int ehVazia_ArvB(ArvB *raiz)  //FEITA
{

    if((*raiz)->qtd == 0)
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

int totalNO_ArvB(ArvB *raiz) // FAZENDO
{

    int cont ;


    if(ehVazia_ArvB(raiz) == 1 || raiz == NULL)
        return 0;



    int contador = (*raiz)->qtd ;
    int i;
    for(i=0; i<(*raiz)->qtd+1; i++)
    {
        if((*raiz)->p[i]== NULL)
            cont ++;      // PARA POSTERIORMENTE CHECAR SE ELA NÃO POSSUI NENNHUM FILHO (É UM NÓ FOLHA)
    }

    if(cont == (*raiz)->qtd+1 )
    {
        return contador;// CASO O NO RAIZ FOR UM NO FOLHA(Nao possui filhos) Retorne a quantidade de elements no nó
    }

    ArvB aux = raiz;


    for(i=0; i<aux->qtd+1; i++)
    {
        printf("Contador antes de somar --> %i \n",contador);
        contador = contador + totalNO_ArvB((*raiz)->p[i]); //UTILIZA DA RECURSAO PARA SOMAR A QUANTIDADE DE CADA NO NO CONTADOR
        printf("Contador depois de somar --> %i \n",contador);
    }
    return contador;
}

int busca_ArvB(ArvB *raiz, int valor)  //FEITA
{

    if((*raiz)->qtd == 0 || raiz == NULL)
        return 0;// ELEMENTO NÃO ENCONTRADO POIS A LISTA ESTÁ VAZIA

    ArvB aux = raiz;

    int i,j;

    for(i=0; i<(*raiz)->qtd; i++)
    {
        if(valor == (*raiz)->chaves[i])
        {
            printf("Elemento achado...\n");
            return 1;// ACHAMOS O ELEMENTO
        }
        else
        {
            if((*raiz)->p[i] != NULL)
                busca_ArvB((*raiz)->p[i],valor);
        }
    }

    printf("Nao foi achado o elemento...\n Retornando 0...\n");
    return 0;


}
