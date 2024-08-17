#include "dbg.h"

    void _Debug_printRankingBuilder(RankingBuilder r_builder)
    {
        printf("\n"); Debug_mark printf(_ORANGE("TOTALJOGADORES = %d\n"), r_builder.total_jogadores);
        for(int i = 0; i < NUM_TABULEIROS; i++)
        {
            printf("\n"); Debug_mark 
            printf(_RED("NÚMERO DE JOGADORES EM SIZE")); 
            printf(_GREEN(" [%d] "), i+3); 
            printf(("= %d\n\n"), r_builder.jogadores_por_categoria[i]);
            for (int j = 0; j < PLAYERS_POR_TABULEIRO; j++)
            {
                Debug_mark printf(_YELLOW("JOGADOR %d| NOME: %s | TEMPO = %ld|\n"), j+1, r_builder.ranking[i][j].nome, r_builder.ranking[i][j].tempo);
            }
            
        }
    }

    void _Debug_printRankingandPlayer(RankingBuilder r_builder, Jogadores player)
    {
        printf("\n"); Debug_mark printf(_ORANGE("TOTALJOGADORES = %d\n"), r_builder.total_jogadores);
        for(int i = 0; i < NUM_TABULEIROS; i++)
        {
            printf("\n"); Debug_mark 
            printf(_RED("NÚMERO DE JOGADORES EM SIZE")); 
            printf(_GREEN(" [%d] "), i+3); 
            printf(("= %d\n\n"), r_builder.jogadores_por_categoria[i]);            
            for (int j = 0; j < PLAYERS_POR_TABULEIRO; j++)
            {
                if(!strcmp(r_builder.ranking[i][j].nome, player.nome))
                {
                    Debug_mark printf(_CYAN("JOGADOR %d| NOME: %s | TEMPO = %ld|\n"), j+1, r_builder.ranking[i][j].nome, r_builder.ranking[i][j].tempo);
                }
                else
                {
                    Debug_mark printf(_YELLOW("JOGADOR %d| NOME: %s | TEMPO = %ld|\n"), j, r_builder.ranking[i][j].nome, r_builder.ranking[i][j].tempo);
                }
            }
        }
    }