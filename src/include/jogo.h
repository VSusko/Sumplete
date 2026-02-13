#ifndef jogo_h
#define jogo_h


#include "cores.h"
#include "interface.h"
#include "auxiliares.h"
#include "dbg.h"
#include "comandos.h"

void Valida_acao(int *acao);

bool jogadoresSaoIguais(Jogador_t x, Jogador_t y);

void Ranking(Jogador_t player);

int ComandoParaNumero(char *entrada_usuario);

bool JogadorGanhou(Tabuleiro_t*);

void criaJogo(Tabuleiro_t *tabuleiro);

void criaGabarito(Tabuleiro_t *tabuleiro);

void ColetarDadosJogo(Tabuleiro_t *tabuleiro);

bool RankingWrite(Ranking_t RankingBuilder);

void ComecarNovoJogo(Tabuleiro_t *tabuleiro, Jogador_t *jogador, int *acao);

void CarregarJogoSalvo(Tabuleiro_t *tabuleiro, Jogador_t *jogador, int *acao);


#endif