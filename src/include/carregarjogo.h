/**
 * @file 
 * @author Victor Susko
 * @brief 
 */

#ifndef carregarjogo_h
#define carregarjogo_h

#define CAMINHO_SAVES "jogos_salvos/"

#include "jogo.h"


typedef struct
{
    Tabuleiro_t *tabuleiro;  //tabuleiro do jogo
    int *soma_acumulada_linha;
    int *soma_acumulada_coluna;
} Acha_gabarito_t;


void ContinuarJogo(Tabuleiro_t *tabuleiro, Jogador_t *jogador, int *acao);

void EncontraGabarito(Acha_gabarito_t *inst, int linha, int coluna, bool *acabou);

void CarregarJogoSalvo(Tabuleiro_t *tabuleiro, Jogador_t *jogador);


#endif