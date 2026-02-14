#include "auxiliares.h"
#include "jogo.h"


//Função que aloca dinamicamente uma matriz
void criaMatrizInt(int ***matriz, int numero_linhas) 
{
    *matriz = malloc(numero_linhas * sizeof(int *));

    for (int i = 0; i < numero_linhas; i++) 
    {
        (*matriz)[i] = malloc(numero_linhas * sizeof(int));
    }
    
    return;
}

void criaMatrizBool(bool ***matriz, int numero_linhas) 
{
    *matriz = malloc(numero_linhas * sizeof(bool *));

    for (int i = 0; i < numero_linhas; i++) 
    {
        (*matriz)[i] = calloc(numero_linhas,  sizeof(bool));
    }

    return;
}

//Função que libera a memoria de uma matriz
void liberaMatriz(void* matriz, int num_linhas)
{
    void** m = (void**) matriz;

    for(int i = 0; i < num_linhas; i++)
        free(m[i]);

    free(m);

    return;
}


//Função que libera a memoria dos dados de um tabuleiro
void liberaTabuleiro(Tabuleiro_t *tabuleiro)
{
    liberaMatriz(tabuleiro->gabarito, tabuleiro->tamanho);
    liberaMatriz(tabuleiro->tabela_numeros, tabuleiro->tamanho);
    liberaMatriz(tabuleiro->tabela_usuario, tabuleiro->tamanho);
    free(tabuleiro->somaColunasTabela);
    free(tabuleiro->somaLinhasTabela);
    free(tabuleiro->somaColunasUsuario);
    free(tabuleiro->somaLinhasUsuario);

    return;
}

void trocaJogadores(Jogador_t *a, Jogador_t *b)
{
    Jogador_t aux = *a;
    *a = *b;
    *b = aux;	

    return;
}


void limpabuffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    return;
}