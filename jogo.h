# ifndef jogo_h
# define jogo_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 50

    //Struct com informações dos jogadores
    typedef struct
    {
        char nome[MAX]; //nome do jogador
        time_t tempo; //tempo gasto pelo jogador para resolver
        int tamanho; //tamanho do tabuleiro
    } Jogadores;


    //Struct com informações de um tabuleiro
    typedef struct
    {
        int *somaLinhas; //soma de cada uma das linhas do tabuleiro
        int *somaColunas; //soma de cada uma das colunas do tabuleiro
        int tamanho; //tamanho do tabuleiro
        int **matriz; //matriz do tabuleiro
    } InfoTabuleiro;


    void Ranking(Jogadores player);

    int Comandos(char*);

    int Comparador(InfoTabuleiro, int**, int**);

    void carregarJogo(InfoTabuleiro*, char*, Jogadores*, int***);

    InfoTabuleiro criaJogo(InfoTabuleiro, int***, char);

    void criaGabarito(int***, int, char);

    Jogadores ColetarDadosJogador(Jogadores);

    InfoTabuleiro ColetarDadosJogo(InfoTabuleiro, char*, char*);

# endif