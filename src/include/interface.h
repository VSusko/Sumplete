#ifndef tabuleiro_h
#define tabuleiro_h

#include "auxiliares.h"

void Menu();

void ImprimeComandos();
    
void ImprimeTabuleiro(Tabuleiro_t* tabuleiro);

void ImprimirRanking();

void ImprimirFim(Jogador_t, time_t);

void MenuJogarNovamente(int *acao);

void ImprimirAcao3(int *acao);

void ImprimirAcao4(int *acao);

void ImprimirCabecalhoRanking();

void ImprimirCorpoRanking(Ranking_t*, Jogador_t);

#endif