#ifndef tabuleiro_h
#define tabuleiro_h

#include "auxiliares.h"


#define TAB_TELA 50

void Valida_acao(int *acao);

void ImprimeTabTela(int quantidade_tabs);

void ValidaNomeArquivo(char *nome_do_arquivo);

void Menu();

void MenuVoltar();

void ExibirComandos();
    
void ExibirTabuleiro(Tabuleiro_t *tabuleiro);

void TelaDeFim(Jogador_t *jogador, time_t tempo_ini, bool usou_resolver);

void MenuJogarNovamente(int *acao);

void ImprimirCabecalhoRanking();

void ExibirRanking();

void ExibirRankingFim(Ranking_t *construtor_ranking, Jogador_t *jogador);

void ImprimirSelecaoDificuldade(int tamanho_tabuleiro);

#endif