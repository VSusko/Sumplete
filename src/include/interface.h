#ifndef tabuleiro_h
#define tabuleiro_h

#include "auxiliares.h"

void Valida_acao(int *acao);

void ValidaNomeArquivo(char *nome_do_arquivo);

void Menu();

void MenuVoltar();

void ImprimeComandos();
    
void ImprimeTabuleiro(Tabuleiro_t *tabuleiro);

void ExibirRanking();

void ImprimirFim(Jogador_t *jogador, time_t tempo_ini);

void MenuJogarNovamente(int *acao);

void ImprimirCabecalhoRanking();

void ImprimirCorpoRanking(Ranking_t*, Jogador_t);

void ImprimirSelecaoDificuldade(int tamanho_tabuleiro);

#endif