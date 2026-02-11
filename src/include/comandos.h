/**
 * @file comandos.h
 * @author Victor Susko 
 * @brief Arquivo de cabeçalho com as funções de comando do jogo
 */


# ifndef comandos_h
# define comandos_h

#include "jogo.h"
#include "cores.h"

void Resolver(Tabuleiro_t, Jogadores, int***, int**, time_t);
    
void Dica(Tabuleiro_t,int***,int**, int*, int);

void Salvar(char*, Jogadores, Tabuleiro_t, int**, int**, time_t);

void Remover(Tabuleiro_t, char*, int***, int*, int**, int*);

void Voltar(Tabuleiro_t*, int***, int**, int*);

void Manter(char*, Tabuleiro_t, int***);

#endif