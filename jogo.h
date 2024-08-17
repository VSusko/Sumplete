#ifndef jogo_h
#define jogo_h


#include "ui.h"
#include "tabuleiro.h"
#include "auxiliares.h"
#include "dbg.h"


    // void rankingInicia(RankingBuilder *rankingBuilder);

    bool jogadoresSaoIguais(Jogadores x, Jogadores y);

    void Ranking(Jogadores player);

    int Comandos(char*);

    int Comparador(InfoTabuleiro, int**, int**);

    void carregarJogo(InfoTabuleiro*, char*, Jogadores*, int***);

    InfoTabuleiro criaJogo(InfoTabuleiro, int***, char);

    void criaGabarito(int***, int, char);

    Jogadores ColetarDadosJogador(Jogadores);

    InfoTabuleiro ColetarDadosJogo(InfoTabuleiro, char*, char*);

    bool RankingWrite(RankingBuilder);

#endif