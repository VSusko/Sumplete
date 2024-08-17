#ifndef auxiliares_h
#define auxiliares_h

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <time.h>
    #include <string.h>
    #include "ui.h"
    
    #define MAX_STRING 50
    #define MAX_PLAYERS 30
    #define NUM_TABULEIROS 7
    #define PLAYERS_POR_TABULEIRO 5

    //Struct com informações de um tabuleiro
    typedef struct
    {
        int *somaLinhas; //soma de cada uma das linhas do tabuleiro
        int *somaColunas; //soma de cada uma das colunas do tabuleiro
        int tamanho; //tamanho do tabuleiro
        int **matriz; //matriz do tabuleiro
    } InfoTabuleiro;

    //Struct com informações dos jogadores
    typedef struct
    {
        char nome[MAX_STRING]; //nome do jogador
        time_t tempo; //tempo gasto pelo jogador para resolver
        int tamanho; //tamanho do tabuleiro
    } Jogadores;
    
    typedef struct
    {
        int jogadores_por_categoria[NUM_TABULEIROS];    
        int total_jogadores;
        Jogadores ranking[NUM_TABULEIROS][PLAYERS_POR_TABULEIRO];
    } RankingBuilder; 

    void criaMatriz(int***, int);

    void liberaMatriz(int**, int);

    void liberaTabuleiro(InfoTabuleiro);

    int** iniciaMatrizBackEnding(InfoTabuleiro, int**, int**, int*);

    void trocaJogadores(Jogadores*, Jogadores*);

#endif