#ifndef dbg_h
#define dbg_h

#include "auxiliares.h"
    
#define DEBUG 1

#define Debug_str(string)       printf(FG_RGB(0, 0, 255) _BOLD string RESET);
#define Debug_mark              printf(FG_RGB(255, 255, 0) _BOLD "[DEBUG] " RESET);
#define printError(string)      printf(FG_RGB(255, 0, 0)  _BOLD string RESET);

void _Debug_printRankingBuilder(RankingBuilder);

void _Debug_printRankingandPlayer(RankingBuilder, Jogadores);


#endif