#include "auxiliares.h"
#include "novojogo.h"


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

void liberaMatriz(void* matriz, int numero_linhas)
{
    void** m = (void**) matriz;

    for(int i = 0; i < numero_linhas; i++)
        free(m[i]);

    free(m);

    return;
}

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

void limpabuffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
    return;
}