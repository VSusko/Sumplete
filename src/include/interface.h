/**
 * @file interface.h
 * @author Victor Susko
 * @brief Arquivo de cabeçalho que possui as funcoes de exibição de mensagens e menus do jogo
 */

#ifndef tabuleiro_h
#define tabuleiro_h

#include "auxiliares.h"

/**
 * @brief Função que valida a ação que o usuario deseja fazer (novo jogo, carregar jogo, exibir ranking e sair)
 * @param acao o inteiro que representa o comando
 */
void Valida_acao(int *acao);

/**
 * @brief Função auxiliar que imprime espaços
 * @param quantidade_tabs número de espaços
 */
void ImprimeTabTela(int quantidade_tabs);

/**
 * @brief Função que valida o nome do jogo carregado (.txt)
 * @param nome_do_arquivo o nome do arquivo
 */
void ValidaNomeArquivo(char *nome_do_arquivo);

/**
 * @brief Função que exibe o menu principal
 */
void Menu();

/**
 * @brief Função que exibe o menu que aparece ao usar o comando voltar
 */
void MenuVoltar();

/**
 * @brief Função que exibe os comandos dentro do jogo
 */
void ExibirComandos();

/**
 * @brief Função que exibe o tabuleiro de um jogo
 * @param tabuleiro Uma instância de um jogo
 */
void ExibirTabuleiro(Tabuleiro_t *tabuleiro);

/**
 * @brief Função que exibe a tela final do jogo, imprime o ranking e mostra os resultados da partida
 * @param jogador O jogador que finalizou o jogo
 * @param tempo_ini O tempo de inicio do jogo
 * @param usou_resolver Flag que indica se o jogador usou ou não o comando resolver
 * @param dificuldade Dificuldade do tabuleiro
 */
void TelaDeFim(Jogador_t *jogador, time_t tempo_ini, bool usou_resolver, char dificuldade);

/**
 * @brief Função que exibe o menu de jogar novamente
 * @param acao Qual ação o jogador escolheu 
 */
void MenuJogarNovamente(int *acao);

/**
 * @brief Função que exibe perguntas de qual dificuldade o jogador quer jogar
 * @param tamanho_tabuleiro O tamanho de tabuleiro escolhido
 */
void ImprimirSelecaoDificuldade(int tamanho_tabuleiro);

#endif