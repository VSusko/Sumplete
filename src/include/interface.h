#ifndef tabuleiro_h
#define tabuleiro_h

#include "auxiliares.h"

void Menu();

void ImprimeComandos();
    
void ImprimeTabuleiro(Tabuleiro_t, int**);

void ImprimirRanking();

void ImprimirFim(Jogadores, time_t);

void MenuJogarNovamente(int*);

void ImprimirAcao3(int*);

void ImprimirAcao4(int*);

void ImprimirRankingHeader();

void ImprimirRankingBody(RankingBuilder, Jogadores);

#endif