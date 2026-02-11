#ifndef jogo_h
#define jogo_h


#include "cores.h"
#include "interface.h"
#include "auxiliares.h"
#include "dbg.h"


// void rankingInicia(RankingBuilder *rankingBuilder);

bool jogadoresSaoIguais(Jogadores x, Jogadores y);

void Ranking(Jogadores player);

int Comandos(char*);

int Comparador(Tabuleiro_t, int**, int**);

void carregarJogo(Tabuleiro_t *tabuleiro, Jogadores *player, int ***BackEnding);

Tabuleiro_t criaJogo(Tabuleiro_t, int***, char);

void criaGabarito(int***, int, char);

Jogadores ColetarDadosJogador(Jogadores);

Tabuleiro_t ColetarDadosJogo(Tabuleiro_t, char*, char*);

bool RankingWrite(RankingBuilder);

#endif