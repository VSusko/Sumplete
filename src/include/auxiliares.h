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

#define MAX_STRING 50 // tamanho maximo de strings
#define TAB_TELA 50 // macro para o deslocamento do tabuleiro
#define NUMERO_DE_TABULEIROS 7 // numero de tabuleiros diferentes (começa como tamanho 3 até tamanho 9, totalizando 7)
#define MAX_JOGADORES_POR_DIFF 5 // numero maximo de jogadores por tamanho

// Estrutura que representa um tabuleiro
typedef struct
{
    int *somaLinhasTabela;    //soma de cada uma das linhas do tabuleiro
    int *somaColunasTabela;   //soma de cada uma das colunas do tabuleiro
    int *somaLinhasUsuario;   //soma de cada uma das linhas do tabuleiro feita pelo usuario
    int *somaColunasUsuario;  //soma de cada uma das colunas do tabuleiro feita pelo usuario
    int tamanho;              //tamanho do tabuleiro
    int **tabela_numeros;     //matriz do tabuleiro
    int **tabela_usuario;     //matriz do tabuleiro que o usuário irá manipular
    bool **gabarito;          //matriz gabarito do tabuleiro
    char dificuldade;         //dificuldade do jogo
    int max_dicas;            //quantidade máxima de dicas que o jogador pode usar
} Tabuleiro_t;

// Estrutura que representa um jogador
typedef struct
{
    char nome[MAX_STRING]; //nome do jogador
    time_t tempo;          //tempo gasto pelo jogador para resolver
    long pontuacao;        //pontuacao obtida pelo jogador
    int tamanho;           //tamanho do tabuleiro
} Jogador_t;

/**
 * @brief Função que compara se dois jogadores são iguais (mesmo nome, tamanho e pontuacao)
 * @param x jogador 1
 * @param y jogador 2
 * @returns true, se os jogadores sao iguais; false, caso contrário 
 */
bool jogadoresSaoIguais(Jogador_t x, Jogador_t y);

/**
 * @brief Função que aloca dinamicamente uma matriz de inteiros
 * @param matriz Uma ponteiro para uma matriz
 * @param numero_linhas O tamanho da matriz (nxn)
 */
void criaMatrizInt(int ***matriz, int numero_linhas);

/**
 * @brief Função que aloca dinamicamente uma matriz de booleanos
 * @param matriz Uma ponteiro para uma matriz
 * @param numero_linhas O tamanho da matriz (nxn)
 */
void criaMatrizBool(bool ***matriz, int numero_linhas);

/**
 * @brief Função que libera a memoria de uma matriz
 * @param matriz Uma ponteiro para uma matriz de qualquer tipo
 * @param numero_linhas O tamanho da matriz (nxn)
 */
void liberaMatriz(void* matriz, int numero_linhas);

/**
 * @brief Função que libera a memoria dos dados de um tabuleiro
 * @param tabuleiro Uma ponteiro para uam instância de um tabuleiro
 */
void liberaTabuleiro(Tabuleiro_t *tabuleiro);

/**
 * @brief Função que limpa o buffer de entrada de dados
 */
void limpabuffer();

#endif