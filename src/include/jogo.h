#ifndef jogo_h
#define jogo_h


#include "cores.h"
#include "interface.h"
#include "auxiliares.h"
#include "dbg.h"


// void rankingInicia(RankingBuilder *rankingBuilder);

bool jogadoresSaoIguais(Jogador_t x, Jogador_t y);

void Ranking(Jogador_t player);

int Comandos(char*);

bool Comparador(Tabuleiro_t*);

void carregarJogo(Tabuleiro_t *tabuleiro, Jogador_t *player, int ***BackEnding);

void criaJogo(Tabuleiro_t *tabuleiro);

void criaGabarito(Tabuleiro_t *tabuleiro, int num_linhas);

void ColetarDadosJogador(Jogador_t *jogador);

void ColetarDadosJogo(Tabuleiro_t *tabuleiro);

bool RankingWrite(RankingBuilder);

#endif