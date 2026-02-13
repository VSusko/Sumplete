#ifndef jogo_h
#define jogo_h


#include "cores.h"
#include "interface.h"
#include "auxiliares.h"
#include "dbg.h"


bool jogadoresSaoIguais(Jogador_t x, Jogador_t y);

void Ranking(Jogador_t player);

int ComandoParaNumero(char *entrada_usuario);

bool JogadorGanhou(Tabuleiro_t*);

void carregarJogo(Tabuleiro_t *tabuleiro, Jogador_t *player, int ***BackEnding);

void criaJogo(Tabuleiro_t *tabuleiro);

void criaGabarito(Tabuleiro_t *tabuleiro);

void ColetarDadosJogo(Tabuleiro_t *tabuleiro);

bool RankingWrite(Ranking_t RankingBuilder);

#endif