/**
 * @file ranking.h
 * @author Victor Susko
 * @brief Arquivo de cabeçalho com as funções de ranking
 */

#ifndef ranking_h
#define ranking_h

#include "auxiliares.h"
#include "interface.h"

#define RANKING_PATH "ranking/sumplete.ini" // Caminho do arquivo do ranking

// Estrutura que representa o construtor do ranking
typedef struct
{
    int num_jogadores_por_categoria[NUMERO_DE_TABULEIROS]; // Vetor que quantiza o número de jogadorespor tamanho de tabuleiro
    int total_jogadores; // Numero total de jogadores no ranking
    Jogador_t ranking[NUMERO_DE_TABULEIROS][MAX_JOGADORES_POR_DIFF]; // Matriz que representa cada jogador em cada tamanho do ranking
} Ranking_t; 

/**
 * @brief Função que faz o rank "sumplete.ini" e acrescenta os dados do jogador
 * @param player jogador que terminou o jogo 
 */
void ConstroiRanking(Jogador_t *player);

/**
 * @brief Função que salva o ranking pronto no arquivo
 * @param construtor_ranking Uma instância do construtor de ranking 
 * @returns true, se salvou com sucesso; false, caso contrário
 */
bool SalvarRanking(Ranking_t *construtor_ranking);

/**
 * @brief Função que lê o ranking do arquivo e imprime na tela do usuário
 */
void ExibirRanking();

/**
 * @brief Função que lê o ranking do arquivo e imprime na tela do usuário. Caso o jogador tenha entrado para o ranking, mostra a colocação dele
 * @param construtor_ranking Uma instância do construtor de ranking 
 * @param jogador O jogador que acabou de finalizar o jogo
 */
void ExibirRankingFim(Ranking_t *construtor_ranking, Jogador_t *jogador);

/**
 * @brief Função que exibe o cabeçalho do ranking
 */
void ImprimirCabecalhoRanking();

#endif