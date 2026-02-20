/**
 * @file comandos.h
 * @author Victor Susko 
 * @brief Arquivo de cabeçalho com as funções de comando do jogo
 */


#ifndef comandos_h
#define comandos_h

#include "novojogo.h"
#include "cores.h"

/**
 * @brief Função que resolve o jogo para o jogador
 * @param tabuleiro Uma instância de um jogo
 * @param jogador O jogador que está jogando
 * @param tempo_ini Tempo de início do jogador
 */
void Resolver(Tabuleiro_t *tabuleiro, Jogador_t *jogador, time_t tempo_ini);

/**
 * @brief Função que fornece uma dica de qual elemento manter
 * @param tabuleiro Uma instância de um jogo
 * @param contadicas O contador de dicas
 */
void Dica(Tabuleiro_t *tabuleiro, int *contadicas);

/**
 * @brief Função que salva um jogo em andamento
 * @param tabuleiro Uma instância de um jogo
 * @param jogador O jogador que está jogando
 * @param nome_do_save Nome que o jogador passou para salvar o arquivodo jogo em andamento
 * @param tempo_ini Tempo inicial do jogador
 */
void Salvar(Tabuleiro_t *tabuleiro, Jogador_t *jogador, char *nome_do_save, time_t tempo_ini);

/**
 * @brief Função que remove um elemento do tabuleiro
 * @param tabuleiro Uma instância de um jogo
 * @param elemento_removido O elemento escolhido para remover (em string)
 * @param contadicas O contador de dicas
 * @param acao A ação que está sendo manipulada (para caso o jogo termine com a vitoria do jogador)
 */
void Remover(Tabuleiro_t *tabuleiro, char *elemento_removido, int *contadicas, int *acao);

/**
 * @brief Função que remove um elemento do tabuleiro
 * @param tabuleiro Uma instância de um jogo
 * @param acao A ação que está sendo manipulada (para caso o jogador escolha sair ou mudar o modo de jogo)
 */
void Voltar(Tabuleiro_t *tabuleiro, int *acao);

/**
 * @brief Função que mantem um elemento do tabuleiro
 * @param tabuleiro Uma instância de um jogo
 * @param elemento_removido O elemento escolhido para remover (em string)
 * @param contadicas O contador de dicas
 */
void Manter(Tabuleiro_t *tabuleiro, char *elemento_mantido, int *contadicas);

#endif