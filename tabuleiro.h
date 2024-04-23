# ifndef tabuleiro_h
# define tabuleiro_h

#include <stdio.h>
#include "jogo.h"

    void Menu();

    void ImprimeComandos();
        
    void ImprimeTabuleiro(InfoTabuleiro, int**);

    void ImprimirRanking();

    void ImprimirFim(Jogadores, time_t);

    void MenuJogarNovamente(int*);

    void ImprimirAcao3(int*);

    void ImprimirAcao4(int*);

# endif