#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jogo.h"
#include "comandos.h"
#include "interface.h"
#include "auxiliares.h"

void Resolver(Tabuleiro_t *tabuleiro, Jogador_t *jogador, time_t tempo_ini)
{
    for(int i = 0; i < tabuleiro->tamanho; i++)
    {
        tabuleiro->somaLinhasUsuario[i] = 0;
        tabuleiro->somaColunasUsuario[i] = 0;
    }    
    
    for(int i = 0; i < tabuleiro->tamanho; i++)
    {
        for(int j = 0; j < tabuleiro->tamanho; j++)
        {
            tabuleiro->tabela_usuario[i][j] = tabuleiro->gabarito[i][j];
            if(tabuleiro->gabarito[i][j] == 1)
            {
                tabuleiro->tabela_usuario[i][j] = 2;
                tabuleiro->somaLinhasUsuario[i] += tabuleiro->tabela_numeros[i][j];
                tabuleiro->somaColunasUsuario[j] += tabuleiro->tabela_numeros[i][j];
            }
        }
    }
    ExibirTabuleiro(tabuleiro);
    time_t tempo_fim = time(NULL);
    jogador->tempo = tempo_fim - tempo_ini;

    return;
}

void Dica(Tabuleiro_t *tabuleiro, int *contadicas)
{
    int linha, coluna;
    bool dica_encontrada = false; 

    if(*contadicas >= tabuleiro->max_dicas)
    {
        printf(RED("\nAs dicas acabaram!\n"));
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

    ExibirTabuleiro(tabuleiro);
}

//Função que salva o jogo atual e os dados do jogador
void Salvar(Tabuleiro_t *tabuleiro, Jogador_t *jogador, char *nome_do_save, time_t tempo_ini)
{
    if(nome_do_save[6] == '\n')
    {
        printf("\n\nFormato ");
        printf(RED("NÃO"));
        printf(" suportado! Digite o nome do arquivo.txt\n\n");
    }

    else
    {
        // Validando o formato do texto
        int t = 0;
        while(nome_do_save[t] != '.')
            t++;

        if(nome_do_save[t+1] != 't' || nome_do_save[t+2] != 'x' || nome_do_save[t+3] != 't' || nome_do_save[t] != '.')
        {
            printf("\n\nFormato ");
            printf(RED("NÃO"));
            printf(" suportado! Digite o nome do arquivo.txt\n\n");
            return;
        }

        time_t tempo_fim = time(NULL);
        jogador->tempo = tempo_fim - tempo_ini;
    }

    // String que conterá o nome do save do jogador
    char nomesave[MAX_STRING]; 
    int i = 0, manterCount = 0, removerCount = 0;
    do
    {
        nomesave[i] = nome_do_save[i+7];
        i++;
    }
    while(nome_do_save[i+7] != '\n');
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
        fprintf(save, "%d ", tabuleiro->somaLinhasTabela[i]);
    fprintf(save, "\n");

    // Soma das colunas do tabuleiro
    for(i = 0; i < tabuleiro->tamanho; i++) 
        fprintf(save, "%d ", tabuleiro->somaColunasTabela[i]);
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
        printf(RED("%c"), nome_do_save[t+7]);
        t++;
    }
    while(nome_do_save[t+7] != '\n');
    nome_do_save[t+7] = '\0';
    printf(YELLOW(" com sucesso!\n\n"));

    return;
}

void Remover(Tabuleiro_t *tabuleiro, char *elemento_removido, int *contadicas, int *acao)
{
    int linha = (elemento_removido[0] - '0') - 1;
    int coluna = (elemento_removido[1] - '0') - 1;
    
    if(elemento_removido[2] != '\0' || linha+1 > tabuleiro->tamanho || linha+1 < 1 
        || coluna+1 > tabuleiro->tamanho || coluna+1 < 1)
    {
        printError("\nEsse elemento não existe! Remova um elemento váldo: ");
        return;
    }

    tabuleiro->tabela_usuario[linha][coluna] = 0;
    tabuleiro->somaLinhasUsuario[linha] -= tabuleiro->tabela_numeros[linha][coluna];
    tabuleiro->somaColunasUsuario[coluna] -= tabuleiro->tabela_numeros[linha][coluna];

    if(tabuleiro->tabela_usuario[linha][coluna] == 0 && tabuleiro->gabarito[linha][coluna] == 1)
        (*contadicas)--;
    
    // Confere se o jogador ganhou o jogo naquele momento
    if(JogadorGanhou(tabuleiro) == false) 
    {
        ExibirTabuleiro(tabuleiro);
        *acao = 0;
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

    ExibirTabuleiro(tabuleiro);
    return;
}

void Voltar(Tabuleiro_t *tabuleiro, int *acao)
{
    MenuVoltar();
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
        printf("\n\n");
        ExibirRanking();
        ExibirTabuleiro(tabuleiro);
        printf("\n\n");
        return;
    }
    else if(*acao == 4)
    {
        ExibirTabuleiro(tabuleiro);
        printf("\n");
        limpabuffer();
        return;
    }
    else{
        liberaTabuleiro(tabuleiro);
    }

    return;
}

void Manter(Tabuleiro_t *tabuleiro, char *elemento_mantido)
{
    // Aritimética que transforma char para int
    int linha = (elemento_mantido[0] - '0') - 1; 
    int coluna = (elemento_mantido[1] - '0') - 1;

    // Mais uma validação de manter
    if(elemento_mantido[2] != '\0' || linha+1 > tabuleiro->tamanho || linha+1 < 1 || coluna+1 > tabuleiro->tamanho || coluna+1 < 1)
    {
        printError("\n\nEsse elemento não existe! Mantenha um elemento váldo:\n\n");
        return;
    }

    tabuleiro->tabela_usuario[linha][coluna] = 2;
    tabuleiro->somaLinhasUsuario[linha] += tabuleiro->tabela_numeros[linha][coluna];
    tabuleiro->somaColunasUsuario[coluna] += tabuleiro->tabela_numeros[linha][coluna];
    ExibirTabuleiro(tabuleiro);
}
