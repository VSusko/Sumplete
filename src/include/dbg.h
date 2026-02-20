/**
 * @file debug.h
 * @author Victor Susko
 * @brief Arquivo de cabeçalho que possui as funcoes de debug
 */

#ifndef dbg_h
#define dbg_h

#include "auxiliares.h"
#include "ranking.h"

// Macro do debug
#define DEBUG 0

// Macros para imprimir elementos de debug
#define Debug_str(string)       printf(FG_RGB(0, 0, 255) _BOLD string RESET);
#define Debug_mark              printf(FG_RGB(255, 255, 0) _BOLD "[DEBUG] " RESET);
#define printError(string)      printf(FG_RGB(255, 0, 0)  _BOLD string RESET);

/**
 * @brief Função que exibe o estado atual do construtor de rankinng
 * @param construtor_ranking Uma instância do construtor de ranking
 */
void DebugRankingBuilder(Ranking_t *construtor_ranking);


#endif