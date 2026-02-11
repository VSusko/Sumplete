#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jogo.h"
#include "comandos.h"
#include "interface.h"
#include "auxiliares.h"

void Resolver(Tabuleiro_t tabuleiro, Jogadores player, int ***BackEnding, int** gabarito, time_t begin)
{
    for(int i = 0; i < tabuleiro.tamanho; i++)
        for(int j = 0; j < tabuleiro.tamanho; j++)
        {
        (*BackEnding)[i][j] = gabarito[i][j];
        if((*BackEnding)[i][j] == 1)
            (*BackEnding)[i][j] = 2;
        }
    ImprimeTabuleiro(tabuleiro, (*BackEnding));
    time_t end = time(NULL);
    player.tempo = end - begin;
}

void Dica(Tabuleiro_t tabuleiro,int ***BackEnding, int **gabarito, int *contadicas, int conta1)
{
    int dica_encontrada = 0, linha, coluna; 

    if(*contadicas == conta1)
    {
        printf(RED("\n\nAs dicas acabaram!\n\n"));
        return;
    }
    else
        do
        {
            linha = rand() % tabuleiro.tamanho;
            coluna = rand() % tabuleiro.tamanho;

            for(int i = 0; i < tabuleiro.tamanho; i++)
            {
                for(int j = 0; j < tabuleiro.tamanho; j++)
                {
                    if(gabarito[linha][coluna] == 1 && ((*BackEnding)[linha][coluna] != 2))
                    {
                        (*BackEnding)[linha][coluna] = 2;
                        dica_encontrada = 1;
                        break;
                    }
                }
                if(dica_encontrada == 1)
                break;
            }
        } 
        while (dica_encontrada != 1);

    if(*contadicas != conta1)
        (*contadicas)++;

    if(dica_encontrada == 1)
    {
        printf(RED("\n\nDICA REVELADA: "));
        printf("Linha: ");
        printf(GREEN("%d"), linha+1);
        printf(" Coluna: ");
        printf(GREEN("%d\n"), coluna+1);
    }
    ImprimeTabuleiro(tabuleiro, (*BackEnding));
}

//Função que salva o jogo atual e os dados do jogador

void Salvar(char *comando, Jogadores player, Tabuleiro_t tabuleiro, int** gabarito, int** matriz, time_t begin)
{
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

    char nomesave[MAX_STRING]; //string que conterá o nome do save do jogador
    int i = 0, manterCount = 0, removerCount = 0;
    do
    {
        nomesave[i] = comando[i+7];
        i++;
    }
    while(comando[i+7] != '\n');
    nomesave[i] = '\0';

    FILE *save = fopen(nomesave, "w"); 

    fprintf(save, "%d", player.tamanho); // tamanho do tabuleiro que o jogador escolheu

    fprintf(save, "\n");

    for(i = 0; i < tabuleiro.tamanho; i++) //matriz do tabuleiro gerada para o jogador naquela partida
    {
        for(int j = 0; j < tabuleiro.tamanho; j++)
        fprintf(save, "%d ", tabuleiro.matriz[i][j]);
        fprintf(save, "\n");
    }

    for(i = 0; i < tabuleiro.tamanho; i++) //soma das linhas do tabuleiro
        fprintf(save, "%d ", tabuleiro.somaLinhas[i]);

    fprintf(save, "\n");

    for(i = 0; i < tabuleiro.tamanho; i++) //soma das colunas do tabuleiro
        fprintf(save, "%d ", tabuleiro.somaColunas[i]);

    fprintf(save, "\n");

    for(i = 0; i < tabuleiro.tamanho; i++) //elementos que o jogador disse para manter
    {
        for(int j = 0; j < tabuleiro.tamanho; j++)
        {
        if(matriz[i][j] == 2)
            manterCount++;
        else if(matriz[i][j] == 0)
            removerCount++;
        }
    }

    fprintf(save, "%d\n", manterCount); //numero de vezes que o jogador usou o comando manter

    for(i = 0; i < tabuleiro.tamanho; i++) //elementos que o jogador disse para manter
    {
        for(int j = 0; j < tabuleiro.tamanho; j++)
        if(matriz[i][j] == 2)
            fprintf(save, "%d %d\n", i+1, j+1);
        
    }

    fprintf(save, "%d\n", removerCount); //numero de vezes que o jogador usou o comando remover

    for(i = 0; i < tabuleiro.tamanho; i++) //elementos que o jogador disse para manter
    {
        for(int j = 0; j < tabuleiro.tamanho; j++)
        if(matriz[i][j] == 0)
        {
            fprintf(save, "%d %d\n", i+1, j+1);
        }
    }

    fprintf(save, "%s\n", player.nome); //nome do jogador

    fprintf(save, "%ld", player.tempo); //tempo gasto pelo jogador

    fclose(save);


    printf(YELLOW("\nJogo salvo como "));

    int t = 0;
    do
    {
    printf(RED("%c"), comando[t+7]);
    t++;
    }
    while(comando[t+7] != '\n');
    comando[t+7] = '\0';
    printf(YELLOW(" com sucesso!\n\n"));
}

void Remover(Tabuleiro_t tabuleiro, char *comando, int ***BackEnding, int *contadicas, int **gabarito, int *acao)
{
    int linha, coluna;
    
    if(comando[10] != '\n') //validando o comando remover
    {
        printf(RED("\nEsse elemento não existe! Remova um elemento váldo:\n"));
        return;
    }

    linha = (comando[8] - '0') - 1;
    coluna = (comando[9] - '0') - 1;
    
    if(linha+1 > tabuleiro.tamanho || linha+1 < 1 || coluna+1 > tabuleiro.tamanho || coluna+1 < 1)
    {
        printf(RED("\nEsse elemento não existe! Remova um elemento váldo: "));
        return;
    }

    (*BackEnding)[linha][coluna] = 0;

    if((*BackEnding)[linha][coluna] == 0 && gabarito[linha][coluna] == 1)
        (*contadicas)--;
    
    if(Comparador(tabuleiro, gabarito, (*BackEnding)) == 0) //confere se o jogador ganhou o jogo naquele momento
    {
        ImprimeTabuleiro(tabuleiro, (*BackEnding));
        *acao = 5;
        return;
    }
    else //o jogador venceu todos os elemtos mantidos serão imprimidos em verde
    {
        for(int i = 0; i < tabuleiro.tamanho; i++)
        for(int j = 0; j < tabuleiro.tamanho; j++)
        {
            if((*BackEnding)[i][j] == 1)
            (*BackEnding)[i][j] = 2;
        }
        ImprimeTabuleiro(tabuleiro, (*BackEnding));
        return;
    }
}

void Voltar(Tabuleiro_t *tabuleiro, int*** gabarito, int **BackEnding, int *acao)
{
    char comando[MAX_STRING];
    int op;
    Menu();
    fgets(comando, MAX_STRING, stdin);
    op = comando[0] - '0';

    while(op < 0 || op > 4 || comando[1] != '\n')
    {
        printf(RED("\n\nComando inválido! Digite um número de 0 a 4: "));
        fgets(comando, MAX_STRING, stdin);
        op = comando[0] - '0';
    }
    
    if (op == 0)
    {
        liberaMatriz(*gabarito, tabuleiro->tamanho);
        liberaTabuleiro(*tabuleiro);
        return; 
    }
    else if(op == 1)
    {
        liberaMatriz(*gabarito, tabuleiro->tamanho);
        liberaTabuleiro(*tabuleiro);
        *acao = 1;
    }
    else if(op == 2)
    {
        liberaMatriz(*gabarito, tabuleiro->tamanho);
        liberaTabuleiro(*tabuleiro);
        *acao = 2;
    }
    else if(op == 3)
    {
        ImprimeTabuleiro(*tabuleiro, BackEnding);
        printf("\n");
        fflush(stdin);
        return;
    }
    else if(op == 4)
    {
        printf("\n\n");
        ImprimirRanking();
        ImprimeTabuleiro(*tabuleiro, BackEnding);
        printf("\n\n");
        return;
    }
}

void Manter(char *comando, Tabuleiro_t tabuleiro, int ***BackEnding)
{
    int linha, coluna;

    if(comando[9] != '\n') //validando o comando manter
    {
        printf(RED("\n\nEsse elemento não existe! Mantenha um elemento váldo:\n\n"));
        return;
    }

    linha = (comando[7] - '0') - 1; //Aritimética que transforma char para int
    coluna = (comando[8] - '0') - 1;
    
    //mais uma validação de manter
    if(linha+1 > tabuleiro.tamanho || linha+1 < 1 || coluna+1 > tabuleiro.tamanho || coluna+1 < 1)
    {
        printf(RED("\n\nEsse elemento não existe! Mantenha um elemento váldo:\n\n"));
        return;
    }
    (*BackEnding)[linha][coluna] = 2;
    ImprimeTabuleiro(tabuleiro, *BackEnding);
}
