#include <stdio.h>

    int sizemax = 1;

    for(int i = 0; i < contador_players; i++)
    {
        j = i+1;
        printf(RED("\nsize = %d\n"), i);
        while(j <= 5 && players[j].tamanho < players[j+1].tamanho)
        {
            if(!strcmp(players[i].nome, player.nome))
            {
                printf(CYAN("SUA COLOCAÇÃO:\nplayer%d = %s\n"), sizemax, players[i].nome);
                printf(CYAN("time%d = %ld\n"), sizemax, players[i].tempo);
            }
            else
            {
                printf("player%d = %s\n", sizemax, players[i].nome);
                printf("time%d = %ld\n", sizemax, players[i].tempo);
            }     
        }
        i = j;     
    }