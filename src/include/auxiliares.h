/**
 * @file auxiliares.h
 * @author Victor Susko
 * @brief Arquivo de cabeçalho com as funções auxiliares do projeto
 */

#ifndef auxiliares_h
#define auxiliares_h

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "cores.h"

#define MAX_STRING 50
#define MAX_PLAYERS 30
#define NUM_TABULEIROS 7
#define MAX_JOGADORES_POR_DIFF 5
#define RANKING_PATH "ranking/sumplete.ini"

//Struct com informações de um tabuleiro
typedef struct
{
    int *somaLinhas;  //soma de cada uma das linhas do tabuleiro
    int *somaColunas; //soma de cada uma das colunas do tabuleiro
    int tamanho;      //tamanho do tabuleiro
    int **tabela_numeros;     //matriz do tabuleiro
    int **tabela_usuario;     //matriz do tabuleiro que o usuário irá manipular
    bool **gabarito;   //matriz gabarito do tabuleiro
    char dificuldade;  //dificuldade do jogo
    int max_dicas;     //quantidade máxima de dicas que o jogador pode usar
} Tabuleiro_t;

//Struct com informações dos jogadores
typedef struct
{
    char nome[MAX_STRING]; //nome do jogador
    time_t tempo;          //tempo gasto pelo jogador para resolver
    int tamanho;           //tamanho do tabuleiro
} Jogador_t;

typedef struct
{
    int jogadores_por_categoria[NUM_TABULEIROS];    
    int total_jogadores;
    Jogador_t ranking[NUM_TABULEIROS][MAX_JOGADORES_POR_DIFF];
} Ranking_t; 

void criaMatrizInt(int***, int);

void criaMatrizBool(bool***, int);

void liberaMatriz(void* matriz, int num_linhas);

void liberaTabuleiro(Tabuleiro_t*);

void trocaJogadores(Jogador_t*, Jogador_t*);

void limpabuffer();

#endif