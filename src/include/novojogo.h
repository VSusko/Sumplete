/**
 * @file jogo.h
 * @author Victor Susko
 * @brief Arquivo de cabeçalho com as funções de começar novo jogo
 */


#ifndef jogo_h
#define jogo_h

#include "cores.h"
#include "interface.h"
#include "dbg.h"
#include "comandos.h"
#include "ranking.h"


/**
 * @brief Função que compara se dois jogadores são iguais (mesmo nome, tamanho e pontuacao)
 * @param x jogador 1
 * @param y jogador 2
 * @returns true, se os jogadores sao iguais; false, caso contrário 
 */
bool jogadoresSaoIguais(Jogador_t x, Jogador_t y);

/**
 * @brief Função que recebe um comando e devolve um inteiro representativo do comando requisitado
 * @param entrada_usuario Uma string que possui o comando digitado pelo usuario
 * @returns 1, se o comando for resolver; 2, se o comando for dica; 3, se o comando for manter; 4, se o comando for salvar; 5, se o comando for voltar; 6, se o comando for remover
 */
int ComandoParaNumero(char *entrada_usuario);

/**
 * @brief Função que verifica a vitória do jogador por meio da soma das linhas e colunas
 * @param tabuleiro Uma instância de um jogo
 * @returns true, se o jogador ganhou o jogo; false caso contrário
 */
bool JogadorGanhou(Tabuleiro_t *tabuleiro);

/**
 * @brief Função que cria um jogo e retorna as alterações no tabuleiro e o gabarito desse jogo
 * @param tabuleiro Um tabuleiro vazio
 */
void criaJogo(Tabuleiro_t *tabuleiro);

/**
 * @brief Função que cria um gabarito para um jogo de acordo com a dificuldade
 * @param tabuleiro Uma instância de um jogo
 */
void criaGabarito(Tabuleiro_t *tabuleiro);

/**
 * @brief Função que coleta a entrada de dados do usuário
 * @param tabuleiro Uma estrutura de tabuleiro vazia
 */
void ColetarDadosJogo(Tabuleiro_t *tabuleiro);

/**
 * @brief Função que coleta a entrada de dados do usuário
 * @param tabuleiro Uma instância de um jogo
 * @param jogador O jogador atual
 * @param acao A ação que está sendo executada e manipulada
 * @returns true, se o jogo acabou com o jogador resolvendo o tabuleiro; false, caso contrário
 */
bool NovoJogo(Tabuleiro_t *tabuleiro, Jogador_t *jogador, int *acao);

#endif