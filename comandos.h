# ifndef comandos_h
# define comandos_h

#include <stdio.h>
#include "jogo.h"
#include "ui.h"

    void Resolver(InfoTabuleiro, Jogadores, int***, int**, time_t);
        
    void Dica(InfoTabuleiro,int***,int**, int*, int);
    
    void Salvar(char*, Jogadores, InfoTabuleiro, int**, int**, time_t);
    
    void Remover(InfoTabuleiro, char*, int***, int*, int**, int*);

    void Voltar(InfoTabuleiro*, int***, int**, int*);

    void Manter(char*, InfoTabuleiro, int***);

# endif