#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define M 13

typedef struct obj
{
   int cod;
   char sabor [50];
}OBJETO;


typedef struct tabelaHash
{
    OBJETO pizza [M];
    int qtdeElem;
}TABELA_HASH;


//1) inicialização
void inicializaTabelaHash (TABELA_HASH *tab){

    tab-> qtdeElem = 0;
    
    for (int i = 0; i < M; i++)
    {
       tab->pizza[i].cod = -1;
    }
    
}
//2) verificar se esta vazia
bool estaVazia (TABELA_HASH *tab){

    return tab -> qtdeElem == 0 ;
}




//3) //     se esta cheia

bool estaCheia (TABELA_HASH *tab){

    return tab -> qtdeElem > M ;
}

int funcaoHash (TABELA_HASH* tab, int k){//utilizando metodo da divisoa

    int pos = k%M;
    int aux;

    //tratamento da colisao: sondagem quadratica
    if (tab->pizza [pos].cod == -1)
    {
        return pos;
    }

    for (int  i = 1; i <= (M- 1) / 2; i++)
    {
        //primeiro: +
        
        
        aux = pos + (i * i);

        if (aux >= M)
        {
            aux = aux- M;
        }
        

        for (;;)
        {
            if (aux = aux-M)
            {
               break;
            }
            
        }
        
        if (tab ->pizza [aux].cod ==-1)
        {
            return aux;
        }
        

        //segundo

        aux = pos - (i * i);
    }
    
    
}
//4) insercao de elemento


 void insereElemento (TABELA_HASH *tab, int k, char sabor []){

    if (estaCheia(tab) == true)
    {
        printf ("\n\n Nao foi possivel inserir: Tabela Hash Cheia");
        return;
    }

    int pos = funcaoHash (tab, k);
    
 }
//5) Buscar elemento
//6) remover elemento




int main()
{
    TABELA_HASH tabela;

    inicializaTabelaHash (&tabela);
    
    insereElemento (&tabela, 100, "Frango");
    insereElemento (&tabela, 0, "Mussarela");
    insereElemento (&tabela, 4, "4Queijos");
    insereElemento (&tabela, 48, "Strogonoff");
    insereElemento (&tabela, 40, "Marguerita");
    insereElemento (&tabela, 17, "Portguesa");
    insereElemento (&tabela, 25, "lombo");
    insereElemento (&tabela, 96, "Sensaocao");
    insereElemento (&tabela, 6, "Chocolate");



    return 0;
}
