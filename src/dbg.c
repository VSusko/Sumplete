#include "dbg.h"

void DebugRankingBuilder(Ranking_t *construtor_ranking)
{
    printf("\n"); Debug_mark printf(_ORANGE("TOTALJOGADORES = %d\n"), construtor_ranking->total_jogadores);
    for(int i = 0; i < NUMERO_DE_TABULEIROS; i++)
    {
        printf("\n"); Debug_mark 
        printf(_RED("NÚMERO DE JOGADORES EM SIZE")); 
        printf(_GREEN(" [%d] "), i+3); 
        printf(("= %d\n\n"), construtor_ranking->num_jogadores_por_categoria[i]);
        for (int j = 0; j < MAX_JOGADORES_POR_DIFF; j++)
        {
            Debug_mark printf(_YELLOW("JOGADOR %d| NOME: %s | PONTUACAO = %ld|\n"), j+1, construtor_ranking->ranking[i][j].nome, construtor_ranking->ranking[i][j].pontuacao);
        }
        
    }
}
