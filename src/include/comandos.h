/**
 * @file comandos.h
 * @author Victor Susko 
 * @brief Arquivo de cabeçalho com as funções de comando do jogo
 */


# ifndef comandos_h
# define comandos_h

#include "jogo.h"
#include "cores.h"

void Resolver(Tabuleiro_t *tabuleiro, Jogador_t player, time_t begin);
    
void Dica(Tabuleiro_t *tabuleiro, int *contadicas);

void Salvar(Tabuleiro_t *tabuleiro, Jogador_t *jogador, char *comando, time_t begin);

void Remover(Tabuleiro_t *tabuleiro, char *comando, int *contadicas, int *acao);

void Voltar(Tabuleiro_t *tabuleiro, int *acao);

void Manter(Tabuleiro_t *tabuleiro, char *comando);

#endif