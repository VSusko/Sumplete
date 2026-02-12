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
void liberaTabuleiro(Tabuleiro_t *tabuleiro)
{
    liberaMatriz(tabuleiro->gabarito, tabuleiro->tamanho);
    liberaMatriz(tabuleiro->tabela_numeros, tabuleiro->tamanho);
    liberaMatriz(tabuleiro->tabela_usuario, tabuleiro->tamanho);
    free(tabuleiro->somaColunas);
    free(tabuleiro->somaLinhas);
}

void trocaJogadores(Jogador_t *a, Jogador_t *b)
{
    Jogador_t aux = *a;
    *a = *b;
    *b = aux;	
}