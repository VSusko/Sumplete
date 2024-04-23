
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "tabuleiro.h"
#include "cores.h"
#include "jogo.h"
#include "auxiliares.h"
#include "comandos.h"

    int main()
    {
        char comando[MAX], dificuldade; //string que será utilizada ao longo de todo o codigo para receber comandos
        int **gabarito;
        int conta1 = 0; //variável que conta quantos elementos serão mantidos no jogo -> utilidade na função de dica
        int acao = 0; //variavel que irá fazer os comandos do Menu
        int contadicas = 0; //variável que irá contar quantas dicas já foram dadas
        InfoTabuleiro tabuleiro;
        Jogadores player; 

        Menu();
        fgets(comando, MAX, stdin);
        acao = comando[0] - '0';
        
        while(acao < 0 || acao > 4 || comando[1] != '\n')
        {
          printf(RED("\nAção inválida! Digite um número de 0 a 4: "));
          fgets(comando, 30, stdin);
          acao = comando[0] - '0';
        }    

        while(acao != 5)
        {
          conta1 = 0, contadicas = 0, dificuldade = 'c';

            if(acao == 0)
              return 0;

            else if(acao == 1)
            {
                conta1 = 0, contadicas = 0, dificuldade = 'c'; //reset das variaveis

                fflush(stdin); //Função que limpa o buffer
                
                player = ColetarDadosJogador(player); //Entrada do nome do jogador
                tabuleiro = ColetarDadosJogo(tabuleiro, comando, &dificuldade); //Entrada de dados do jogo

                tabuleiro = criaJogo(tabuleiro, &gabarito, dificuldade);

                int **BackEnding; //Matriz que será manipulada
                criaMatriz(&BackEnding, tabuleiro.tamanho);
                BackEnding = iniciaMatrizBackEnding(tabuleiro, BackEnding, gabarito, &conta1);

                player.tamanho = tabuleiro.tamanho;
                
                ImprimeTabuleiro(tabuleiro, BackEnding);

                time_t begin = time(NULL);

                while(Comparador(tabuleiro, gabarito, BackEnding) == 0)
                {
                  fgets(comando, MAX, stdin);

                  int n = Comandos(comando);

                  if(n == 0) //Comando inválido
                  {
                    printf("\n\nComando ");
                    printf(RED("inválido!"));
                    printf(" Digite um comando válido:\n\n");
                  }
                  else if(n == 1) //Comando Resolver
                  {
                    Resolver(tabuleiro, player, &BackEnding, gabarito, begin);
                    acao = 5;
                  }
                  else if(n == 2) //Comando Dica
                  {
                    Dica(tabuleiro, &BackEnding, gabarito, &contadicas, conta1);
                  }
                  else if(n == 3) //Comando Manter
                  {
                    Manter(comando, tabuleiro, &BackEnding);              
                  }
                  else if(n == 4) //Comando Salvar
                  {
                    Salvar(comando, player, tabuleiro, gabarito, BackEnding, begin);
                  }
                  else if(n == 5) //Comando Voltar
                  {
                    Voltar(&tabuleiro, &gabarito, BackEnding, &acao);
                  }
                  else if(n == 6) //Remover 
                  {
                    Remover(tabuleiro, comando, &BackEnding, &contadicas, gabarito, &acao);
                  }
                }
                if(acao == 1) //O jogador digitou o comando voltar e depois digitou 1 para começar um novo jogo
                  continue;
                else if(acao == 2) //O jogador digitou o comando voltar e depois digitou 2 para carregar jogo salvo
                  continue;

                else
                {
                  ImprimirFim(player, begin);
                  liberaTabuleiro(tabuleiro);
                  liberaMatriz(gabarito, tabuleiro.tamanho);
                  acao = 5;
                }
            }

            else if(acao == 2) //Carregar jogo salvo
            {
              carregarJogo(&*tabuleiro2, comando, &player2, &matriz2);

              ImprimeTabuleiro(tabuleiro, matriz2);

              fgets(comando, MAX, stdin);
              acao = comando[0] - '0';
              while(comando[1] != '\n' || acao < 0 || acao > 4)
              {
                printf(RED("\n\nComando inválido!\n\n"));
                fgets(comando, MAX, stdin);
                acao = comando[0] - '0';
              }
              continue;
            }

            else if(acao == 3) //Continuar jogo atual
            {
              ImprimirAcao3(&acao);
              continue;
            }
            else if(acao == 4) //Exibir ranking
            {
              ImprimirAcao4(&acao);
              continue;
            }
            
          MenuJogarNovamente(&acao);
        }
    
        return 0;
    }