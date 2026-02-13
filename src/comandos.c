#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jogo.h"
#include "comandos.h"
#include "interface.h"
#include "auxiliares.h"

void Resolver(Tabuleiro_t *tabuleiro, Jogador_t *jogador, time_t begin)
{
    for(int i = 0; i < tabuleiro->tamanho; i++)
        for(int j = 0; j < tabuleiro->tamanho; j++)
        {
            tabuleiro->tabela_usuario[i][j] = tabuleiro->gabarito[i][j];
            if(tabuleiro->gabarito[i][j] == 1)
                tabuleiro->tabela_usuario[i][j] = 2;
        }
    ImprimeTabuleiro(tabuleiro);
    time_t end = time(NULL);
    jogador->tempo = end - begin;

    return;
}

void Dica(Tabuleiro_t *tabuleiro, int *contadicas)
{
    int linha, coluna;
    bool dica_encontrada = false; 

    if(*contadicas > tabuleiro->max_dicas)
    {
        printf(RED("\n\nAs dicas acabaram!\n\n"));
        return;
    }
    else
    {
        while (dica_encontrada != true)
        {
            linha = rand() % tabuleiro->tamanho;
            coluna = rand() % tabuleiro->tamanho;            
            if(tabuleiro->gabarito[linha][coluna] == true && tabuleiro->tabela_usuario[linha][coluna] != 2)
            {
                tabuleiro->tabela_usuario[linha][coluna] = 2;
                dica_encontrada = true;
                (*contadicas)++;
            }
        }
            
    }        
    // Imprime a dica revelada
    printf(RED("\n\nDICA REVELADA: "));
    printf("Linha: ");
    printf(GREEN("%d"), linha+1);
    printf(" Coluna: ");
    printf(GREEN("%d\n"), coluna+1);

    ImprimeTabuleiro(tabuleiro);
}

//Função que salva o jogo atual e os dados do jogador
void Salvar(Tabuleiro_t *tabuleiro, Jogador_t *jogador, char *entrada_usuario, time_t begin)
{
    if(entrada_usuario[6] == '\n')
    {
        printf("\n\nFormato ");
        printf(RED("NÃO"));
        printf(" suportado! Digite o nome do arquivo.txt\n\n");
    }

    else
    {
        // Validando o formato do texto
        int t = 0;
        while(entrada_usuario[t] != '.')
            t++;

        if(entrada_usuario[t+1] != 't' || entrada_usuario[t+2] != 'x' || entrada_usuario[t+3] != 't' || entrada_usuario[t] != '.')
        {
            printf("\n\nFormato ");
            printf(RED("NÃO"));
            printf(" suportado! Digite o nome do arquivo.txt\n\n");
            return;
        }

        time_t end = time(NULL);
        jogador->tempo = end - begin;
    }

    // String que conterá o nome do save do jogador
    char nomesave[MAX_STRING]; 
    int i = 0, manterCount = 0, removerCount = 0;
    do
    {
        nomesave[i] = entrada_usuario[i+7];
        i++;
    }
    while(entrada_usuario[i+7] != '\n');
    nomesave[i] = '\0';

    // ========== Salvando o jogo em um arquivo de texto ========== //

    FILE *save = fopen(nomesave, "w"); 

    // Tamanho do tabuleiro que o jogador escolheu
    fprintf(save, "%d\n", jogador->tamanho); 

    // Números gerados para o jogador naquela partida
    for(i = 0; i < tabuleiro->tamanho; i++) 
    {
        for(int j = 0; j < tabuleiro->tamanho; j++)
            fprintf(save, "%d ", tabuleiro->tabela_numeros[i][j]);
        fprintf(save, "\n");
    }

    // Soma das linhas do tabuleiro
    for(i = 0; i < tabuleiro->tamanho; i++) 
        fprintf(save, "%d ", tabuleiro->somaLinhas[i]);
    fprintf(save, "\n");

    // Soma das colunas do tabuleiro
    for(i = 0; i < tabuleiro->tamanho; i++) 
        fprintf(save, "%d ", tabuleiro->somaColunas[i]);
    fprintf(save, "\n");

    // Contando quantos elementos o jogador manteve e removeu
    for(i = 0; i < tabuleiro->tamanho; i++) 
    {
        for(int j = 0; j < tabuleiro->tamanho; j++)
        {
            if(tabuleiro->tabela_usuario[i][j] == 2)
                manterCount++;
            else if(tabuleiro->tabela_usuario[i][j] == 0)
                removerCount++;
        }
    }

    // Numero de vezes que o jogador usou o comando manter
    fprintf(save, "%d\n", manterCount); 

    // Numeros que o jogador escolheu manter
    for(i = 0; i < tabuleiro->tamanho; i++) 
    {
        for(int j = 0; j < tabuleiro->tamanho; j++)
        if(tabuleiro->tabela_usuario[i][j] == 2)
            fprintf(save, "%d %d\n", i+1, j+1);
        
    }

    // Numero de vezes que o jogador usou o comando remover
    fprintf(save, "%d\n", removerCount); 

    // Elementos que o jogador esocolheu remover
    for(i = 0; i < tabuleiro->tamanho; i++) 
    {
        for(int j = 0; j < tabuleiro->tamanho; j++)
        if(tabuleiro->tabela_usuario[i][j] == 0)
        {
            fprintf(save, "%d %d\n", i+1, j+1);
        }
    }

    // Nome do jogador
    fprintf(save, "%s\n", jogador->nome); 

    // Tempo gasto pelo jogador
    fprintf(save, "%ld", jogador->tempo); 

    // Fecha o arquivo
    fclose(save);

    // Imprime mensagem de sucesso
    printf(YELLOW("\nJogo salvo como "));
    int t = 0;
    do
    {
        printf(RED("%c"), entrada_usuario[t+7]);
        t++;
    }
    while(entrada_usuario[t+7] != '\n');
    entrada_usuario[t+7] = '\0';
    printf(YELLOW(" com sucesso!\n\n"));

    return;
}

void Remover(Tabuleiro_t *tabuleiro, char *comando, int *contadicas, int *acao)
{
    int linha, coluna;
    
    if(comando[10] != '\n') //validando o comando remover
    {
        printf(RED("\nEsse elemento não existe! Remova um elemento váldo:\n"));
        return;
    }

    linha = (comando[8] - '0') - 1;
    coluna = (comando[9] - '0') - 1;
    
    if(linha+1 > tabuleiro->tamanho || linha+1 < 1 || coluna+1 > tabuleiro->tamanho || coluna+1 < 1)
    {
        printf(RED("\nEsse elemento não existe! Remova um elemento váldo: "));
        return;
    }

    tabuleiro->tabela_usuario[linha][coluna] = 0;

    if(tabuleiro->tabela_usuario[linha][coluna] == 0 && tabuleiro->gabarito[linha][coluna] == 1)
        (*contadicas)--;
    
    // Confere se o jogador ganhou o jogo naquele momento
    if(JogadorGanhou(tabuleiro) == false) 
    {
        ImprimeTabuleiro(tabuleiro);
        *acao = 5;
        return;
    }
    // O jogador venceu, todos os elemtos mantidos serão imprimidos em verde
    else 
    {
        for(int i = 0; i < tabuleiro->tamanho; i++)
            for(int j = 0; j < tabuleiro->tamanho; j++)
            {
                if(tabuleiro->gabarito[i][j] == 1)
                    tabuleiro->tabela_usuario[i][j] = 2;
            }
        }

    ImprimeTabuleiro(tabuleiro);
    return;
}

void Voltar(Tabuleiro_t *tabuleiro, int *acao)
{
    Menu();
    scanf("%d", acao);
    limpabuffer();

    while(*acao < 0 || *acao > 4)
    {
        printError("\n\nComando inválido! Digite um número de 0 a 4: ");
        scanf("%d", acao);
        limpabuffer();
    }
    
    if(*acao == 3)
    {
        ImprimeTabuleiro(tabuleiro);
        printf("\n");
        fflush(stdin);
        return;
    }
    else if(*acao == 4)
    {
        printf("\n\n");
        ImprimirRanking();
        ImprimeTabuleiro(tabuleiro);
        printf("\n\n");
        return;
    }
    else{
        liberaTabuleiro(tabuleiro);
    }

    return;
}

void Manter(Tabuleiro_t *tabuleiro, char *entrada_usuario)
{
    int linha, coluna;

    // Validando o comando manter
    if(entrada_usuario[9] != '\n') 
    {
        printError("\n\nEsse elemento não existe! Mantenha um elemento váldo:\n\n");
        return;
    }

    // Aritimética que transforma char para int
    linha = (entrada_usuario[7] - '0') - 1; 
    coluna = (entrada_usuario[8] - '0') - 1;
    
    // Mais uma validação de manter
    if(linha+1 > tabuleiro->tamanho || linha+1 < 1 || coluna+1 > tabuleiro->tamanho || coluna+1 < 1)
    {
        printError("\n\nEsse elemento não existe! Mantenha um elemento váldo:\n\n");
        return;
    }

    tabuleiro->tabela_usuario[linha][coluna] = 2;
    ImprimeTabuleiro(tabuleiro);
}
