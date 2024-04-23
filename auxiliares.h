# ifndef auxiliares_h
# define auxiliares_h

#include "jogo.h"

    void criaMatriz(int***, int);

    void liberaMatriz(int**, int);

    void liberaTabuleiro(InfoTabuleiro);

    int** iniciaMatrizBackEnding(InfoTabuleiro, int**, int**, int*);

    void trocaJogadores(Jogadores*, Jogadores*);

# endif