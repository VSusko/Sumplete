/**
 * @file carregarjogo.h
 * @author Victor Susko
 * @brief Arquivo de cabeçalho que possui as funcoes de continuar jogo salvo
 */

#ifndef carregarjogo_h
#define carregarjogo_h

#define CAMINHO_SAVES "jogos_salvos/" // caminho da pasta de jogos salvos

#include "novojogo.h"
#include "ranking.h"

// Estrutura para encontrar uma solução para um jogo salvo
typedef struct
{
    Tabuleiro_t *tabuleiro;     // tabuleiro do jogo
    int *soma_acumulada_linha;  // vetor que possui a soma atual das linhas
    int *soma_acumulada_coluna; // vetor que possui a soma atual das colunas
} Encontra_gabarito_t;

/**
 * @brief Função que realiza o loop de continuar um jogo salvo
 * @param tabuleiro Uma instância de um jogo
 * @param jogador O jogador que está jogando
 * @param acao Qual ação vai ser executada
 * @returns true, se o jogador finalizou o jogo; false, se ocorreu algum problema ou ele pediu para encerrar
 */
bool ContinuarJogo(Tabuleiro_t *tabuleiro, Jogador_t *jogador, int *acao);

/**
 * @brief Função que encontra um gabarito para um jogo salvo via branch and bound
 * @param inst Uma instância da estrutura que encontra um gabarito
 * @param posicao Posição atual no tabuleiro
 * @param acabou Se ja foi encontrada uma solução ou não
 */
void EncontraGabarito(Encontra_gabarito_t *inst, int posicao, bool *acabou);

/**
 * @brief Função que realiza o cálculo do numero maximo de dicas e ajusta o contador a partir de um jogo salvo
 * @param tabuleiro Uma instância de um jogo
 * @param contadicas O contador de dicas que será atualizado
 */
void RecalculaDicas(Tabuleiro_t *tabuleiro, int *contadicas);

/**
 * @brief Função que preenche as informações do tabuleiro e do jogador a partir de um arquivo de texto
 * @param tabuleiro Um tabuleiro que será carregado
 * @param jogador O jogador que está jogando
 * @returns true, se conseguiu carregar o jogo com sucesso; false, caso contrário
 */
bool CarregarJogoSalvo(Tabuleiro_t *tabuleiro, Jogador_t *jogador);

/**
 * @brief Função que verifica se um gabarito é válido
 * @param inst Uma instância da estrutura que encontra um gabarito
 * @returns true, se a solução encontrada é válida; false, caso contrário
 */
bool VerificaGabarito(Encontra_gabarito_t *inst);

#endif