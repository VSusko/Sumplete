#include "auxiliares.h"
#include "jogo.h"


//Função que aloca dinamicamente uma matriz

    void criaMatriz(int ***matriz, int nlines) 
    {
        *matriz = malloc(nlines * sizeof(int *));

        for (int i = 0; i < nlines; i++) 
        {
            (*matriz)[i] = malloc(nlines * sizeof(int));
        }
    }

    //Função que libera a memoria de uma matriz

    void liberaMatriz(int** matriz, int nlines)
    {
      for(int i = 0; i < nlines; i++)
          free(matriz[i]);
      free(matriz);
    }

    //Função que libera a memoria dos dados de um tabuleiro

    void liberaTabuleiro(Tabuleiro_t tabuleiro)
    {
        liberaMatriz(tabuleiro.matriz, tabuleiro.tamanho);
        free(tabuleiro.somaColunas);
        free(tabuleiro.somaLinhas);
    }

    int **iniciaMatrizBackEnding(Tabuleiro_t tabuleiro, int** BackEnding, int** gabarito, int *conta1)
    {
        for(int i = 0; i < tabuleiro.tamanho; i++) //inicializando a matriz com o valor 1
            for(int j = 0; j < tabuleiro.tamanho; j++)
            {
                BackEnding[i][j] = 1;
                if(gabarito[i][j] == 1)
                    (*conta1)++;
            }
        
        return BackEnding;
    }

    void trocaJogadores(Jogadores *a, Jogadores *b)
    {
        Jogadores aux = *a;
        *a = *b;
        *b = aux;	
    }