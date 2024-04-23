#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include "cores.h"
#include "tabuleiro.h"
#include "auxiliares.h"


    int encontraGabarito(int i, int j, int tam, InfoTabuleiro tabuleiro, int somaLinha. int ***gabarito)
    {
        if(i > tam-1 || j > tam-1)
            return 0; 
        
        int soma = tabuleiro.matriz[i][j];
        return soma + encontraGabarito(i+1, j, tam, tabuleiro, somalinha, gabarito);

        if(soma + tabuleiro.matriz[i][j] > somaLinha)
        {
            (*gabarito)[i][j] = 0;
            return 0;
        }
        
        (*gabarito)[i][j] = 1;
        
        return soma + encontraGabarito(i, j+1, tam, tabuleiro, somalinha, gabarito);
    }   


    //Função que carrega jogo

    void carregarJogo(InfoTabuleiro *tabuleiro, Jogadores *player, int ***BackEnding)
    {
        char comando[MAX];

        printf("\nDigite o nome do arquivo.txt:\n\n");
        fgets(comando, MAX, stdin);

        if(comando[6] == '\n')
        {
            printf("\n\nFormato ");
            printf(RED("NÃO"));
            printf(" suportado! Digite o nome do arquivo.txt\n\n");
        }

        else
        {
            //validando o formato do texto
            int t = 0;
            while(comando[t] != '.')
                t++;

            if(comando[t+1] != 't' || comando[t+2] != 'x' || comando[t+3] != 't' || comando[t] != '.')
            {
                printf("\n\nFormato ");
                printf(RED("NÃO"));
                printf(" suportado! Digite o nome do arquivo.txt\n\n");
                return;
            }

            time_t end = time(NULL);
            player.tempo = end - begin;
        }

        FILE *arquivo = fopen("savenome", "r");
        int manterCount;
        int removerCount;
        int linha, coluna;

        fscanf(arquivo, " %d", &(*tabuleiro).tamanho);
        
        criaMatriz(&(*tabuleiro).matriz, (*tabuleiro).tamanho);
        criaMatriz(&*matriz, (*tabuleiro).tamanho);

        //Colocando os valores da matriz do tabuleiro

        for(int i = 0; i < (*tabuleiro).tamanho; i++)
            for(int j = 0; j < (*tabuleiro).tamanho; j++)
                fscanf(arquivo, " %d", &(*tabuleiro).matriz[i][j]);

        //alocando dinamicamente o tamanho da soma das linhas e das colunas

        (*tabuleiro).somaLinhas = malloc((*tabuleiro).tamanho * sizeof(int));
        (*tabuleiro).somaColunas = malloc((*tabuleiro).tamanho * sizeof(int));

        //pegando os valores da soma das linhas

        for(int i = 0; i < (*tabuleiro).tamanho; i++)
            fscanf(arquivo, " %d", &(*tabuleiro).somaLinhas[i]);

        //pegando os valores da soma das colunas
        
        for(int i = 0; i < (*tabuleiro).tamanho; i++)
            fscanf(arquivo, " %d", &(*tabuleiro).somaColunas[i]);

        fscanf(arquivo, " %d", &manterCount);

        for(int i = 0; i < manterCount; i++)
        {
            fscanf(arquivo, "%d %d", &linha, &coluna);
            linha--;
            coluna--;
            *(matriz)[linha][coluna] = 2;
        }
          
        fscanf(arquivo, " %d", &removerCount);

        for(int i = 0; i < removerCount; i++)
        {
            fscanf(arquivo, "%d %d", &linha, &coluna);
            linha--;
            coluna--;
            (*matriz)[linha][coluna] = 0;
        }

        fgets((*player).nome, MAX, arquivo);

        fscanf(arquivo, " %ld", &(*player).tempo);

        fclose(arquivo);

        
    }
