#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "cores.h"
#include "tabuleiro.h"
#include "auxiliares.h"
#include "jogo.h"


//Função que cria um gabarito para um jogo, não funciona sem a função criaJogo

    void criaGabarito(int ***gabarito, int nlines, char dificuldade)
    {
      criaMatriz(gabarito, nlines);

      srand(time(NULL));

      //Gerando gabarito aleatorio

      if(dificuldade == 'f' || dificuldade == 'F')
        for(int i = 0; i < nlines; i++)
          for(int j = 0; j < nlines; j++)
          {
            (*gabarito)[i][j] = rand() % 2;
          }


      else if (dificuldade == 'm' || dificuldade == 'M')
      {
        //variaveis que irão validar a soma das linhas e das colunas

        int Validar_Soma_Linha = 0;
        int Validar_Soma_Coluna = 0;

       do
       {
          for(int i = 0; i < nlines; i++)
          {
            Validar_Soma_Linha = 0;
            for(int j = 0; j < nlines; j++)
            {
              (*gabarito)[i][j] = rand() % 2;
              if((*gabarito)[i][j] == 1)
              {
                Validar_Soma_Linha++;
              }
              else if(j == nlines - 1 && (Validar_Soma_Linha == nlines || Validar_Soma_Linha == 0))       
                break;
            }
            if(Validar_Soma_Linha == nlines || Validar_Soma_Linha == 0)
              break;
          }

          if(Validar_Soma_Linha == nlines || Validar_Soma_Linha == 0)
            continue;
          
          else
          {
            for(int i = 0; i < nlines; i++)
            {
              Validar_Soma_Coluna = 0;
              for(int j = 0; j < nlines; j++)
              {
                  if((*gabarito)[j][i] == 1)
                    Validar_Soma_Coluna++;       
                  else if(j == nlines - 1 && (Validar_Soma_Coluna == nlines || Validar_Soma_Coluna == 0))       
                    break;
              }
              if(Validar_Soma_Coluna == nlines || Validar_Soma_Coluna == 0)       
                    break; 
            }
          }
       }
       while (Validar_Soma_Linha == nlines || Validar_Soma_Coluna == nlines || Validar_Soma_Linha == 0 || Validar_Soma_Coluna == 0);
       
      }

      else if (dificuldade == 'd' || dificuldade == 'D')
      {
        //variaveis que irão validar a soma das linhas e das colunas

        int Validar_Soma_Linha = 0;
        int Validar_Soma_Coluna = 0;

        do
       {
          for(int i = 0; i < nlines; i++)
          {
            Validar_Soma_Linha = 0;
            for(int j = 0; j < nlines; j++)
            {
              (*gabarito)[i][j] = rand() % 2;
                if((*gabarito)[i][j] == 1)
                {
                  Validar_Soma_Linha++;
                }
                else if(j == nlines - 1 && Validar_Soma_Linha == nlines)       
                  break;
            }
            if(Validar_Soma_Linha == nlines)
              break;
          }

          if(Validar_Soma_Linha == nlines)
            continue;
          
          else
          {
            for(int i = 0; i < nlines; i++)
            {
              Validar_Soma_Coluna = 0;
              for(int j = 0; j < nlines; j++)
              {
                  if((*gabarito)[j][i] == 1)
                  {
                    Validar_Soma_Coluna++;       
                  }
                  else if(j == nlines - 1 && Validar_Soma_Coluna == nlines)       
                    break;
              }
              if(Validar_Soma_Coluna == nlines)       
                    break; 
            }
          }
       }
       while (Validar_Soma_Linha == nlines || Validar_Soma_Coluna == nlines);
       
      }

    } 


    //Função que imrprime o rank "sumplete.ini" e acrescenta os dados do jogador

    void Ranking(Jogadores player)
    {
        FILE *arquivo = fopen("sumplete.ini", "r"); 
        
        if(arquivo != NULL)
        {

            Jogadores *players;
            char string[100], stringaux[100];
            int size, contador_players = 0, j, i = 0;

            //Cálculo de contagem dos jogadores

            while (!feof(arquivo))
            {   
                fgets(string, 100, arquivo);

                if(string[0] == 'p')
                    contador_players++;
                else
                    continue;
            }
            
            fseek(arquivo, 0, SEEK_SET);

            contador_players++;

            players = malloc(contador_players * sizeof(Jogadores));
            
            //adicionando dados do jogador nos jogadores do ranking

            players[i].tempo = player.tempo;
            players[i].tamanho = player.tamanho;
            strcpy(players[i].nome, player.nome);
            i++;

            //Coleta de dados dos jogadores

            while (!feof(arquivo))
            {   
                fgets(string, 100, arquivo);

                if(string[0] == 's')
                {
                    size = string[7] - '0';
                }
                
                players[i].tamanho = size; 

                if(string[0] == 'p')
                {   
                    j = 0;
                    while(string[j+10] != '\0')
                    {
                        players[i].nome[j] = string[j+10];
                        j++;
                    }
                    players[i].nome[j-1] = '\0';
                }   

                if(string[0] == 't')
                {
                    sscanf(string, "%s %*c %ld", stringaux, &players[i].tempo);
                    i++;
                }
            }

            //Imprimindo o ranking no terminal - cabeçalho

            printf(TAB_TL);
            for(int i = 0; i < 23; i++)
            {
                if(i % 2 == 0)
                    printf(MAGENTA(TAB_HOR));
                else
                    printf(TAB_HOR);
            }
            printf(TAB_TR"\n");
            printf(TAB_VER BLUE(" RANKING DOS JOGADORES ") TAB_VER);
            printf("\n"TAB_BL);
            for(int i = 0; i < 23; i++)
            {
                if(i % 2 == 0)
                    printf(MAGENTA(TAB_HOR));
                else
                    printf(TAB_HOR);
            }
            printf(TAB_BR"\n\n");

            //Colocando o jogador na ordem - Insertion Sort

            Jogadores aux;
            int j;
            
            //organizando a ordem de cada jogador por tamanho de tabuleiro
            for(int i = 1; i < contador_players; i++)
            {
              aux = players[i];
              j = i - 1;
              while(j >= 0 && players[j].tamanho < aux.tamanho)
              {
                players[j+1] = players[j]
                j--;
              }
            }

            //organizando a ordem de cada jogador por tempo
            for(int i = 1; i < contador_players; i++)
            {
              aux = players[i];
              j = i - 1;
              while(j >= 0 && (players[j].tamanho == aux.tamanho && players[j].tempo > aux.tempo))
              {
                players[j+1] = players[j]
                j--;
              }
            }
            
            //imprimindo ranking no terminal - ranking

            int sizemax = 1;

            for(int i = 0; i < contador_players; i++)
            {
                if(sizemax > 5)
                {
                    sizemax = 1;
                    continue;
                }
                if(sizemax == 1)
                    printf(RED("\nsize = %d\n"), players[i].tamanho);
            
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

                if(players[i+1].tamanho > players[i].tamanho)
                    sizemax = 1;
                else
                    sizemax++;       
            }
        
            
            FILE *gravar = fopen("sumplete.ini", "w");

            sizemax = 1;

            for(int i = 0; i < contador_players; i++)
            {
                if(sizemax > 5)
                {
                    sizemax = 1;
                    continue;
                }

                if(i == 0)
                    fprintf(gravar, "size = %d\n", players[i].tamanho);
                else if(sizemax == 1)
                    fprintf(gravar, "\nsize = %d\n", players[i].tamanho);
        
                fprintf(gravar, "player%d = %s\n", sizemax, players[i].nome);

                if(i == contador_players - 1 || (i == contador_players - 2 && sizemax == 5))
                fprintf(gravar, "time%d = %ld", sizemax, players[i].tempo);
                else
                fprintf(gravar, "time%d = %ld\n", sizemax, players[i].tempo);
                
                if(players[i+1].tamanho > players[i].tamanho)
                    sizemax = 1;
                else
                    sizemax++;       
            }
        
            fclose(gravar);
            
            free(players);
        }
        else
            printf("\nO arquivo ""sumplete.ini"" não existe!\n");
        
        fclose(arquivo);
    }

    //Função que cria um jogo e retorna as alterações no tabuleiro e o gabarito desse jogo

    InfoTabuleiro criaJogo(InfoTabuleiro tabuleiro, int*** gabarito, char dificuldade)
    {                   
        //Alocando memoria para a matriz do tabuleiro

        criaMatriz(&tabuleiro.matriz, tabuleiro.tamanho);

        //Alocando memoria para a soma de linhas e colunas do tabuleiro

        tabuleiro.somaColunas = malloc(tabuleiro.tamanho * sizeof(int));
        tabuleiro.somaLinhas = malloc(tabuleiro.tamanho * sizeof(int));

        //Gerando semente aleatória para os números e a soma

        srand(time(NULL));

        //Gerando uma matriz com numeros aleatorios

        if(dificuldade == 'f' || dificuldade == 'F' || dificuldade == 'm' || dificuldade == 'M')
        {
          for(int i = 0; i < tabuleiro.tamanho; i++)
          {
            for(int j = 0; j < tabuleiro.tamanho; j++)
            {
                tabuleiro.matriz[i][j] = 1 + (rand() % 9);
            }
          }
        }

        else if(dificuldade == 'd' || dificuldade == 'D')
        {
          for(int i = 0; i < tabuleiro.tamanho; i++)
          {
            for(int j = 0; j < tabuleiro.tamanho; j++)
            {
                tabuleiro.matriz[i][j] = (rand() % 19) - 9;
            }
          }
        }

        //Gerando matriz gabarito 

        criaGabarito(&*gabarito, tabuleiro.tamanho, dificuldade);
        
        //Limpando a memoria das somas das linhas e colunas

        for(int i = 0; i < tabuleiro.tamanho; i++)
        {
          tabuleiro.somaLinhas[i] = 0;
          tabuleiro.somaColunas[i] = 0;
        }
        
        //Soma das linhas e colunas segundo o gabarito
        for (int i = 0; i < tabuleiro.tamanho; i++) 
        {
          for(int j = 0; j < tabuleiro.tamanho; j++)
          {
            if((*gabarito)[i][j] == 1)
            {
              tabuleiro.somaLinhas[i] += tabuleiro.matriz[i][j];
              tabuleiro.somaColunas[j] += tabuleiro.matriz[i][j]; 
            }
          }
        }       
        
    return tabuleiro;
    }

    //Função que compara o gabarito com a matriz que está sendo manipulada pelo usuario

    int Comparador(InfoTabuleiro tabuleiro, int **gabarito, int **matriz)
    {
      for(int i = 0; i < tabuleiro.tamanho; i++)
      {
        for(int j = 0; j < tabuleiro.tamanho; j++)
        {
          if(gabarito[i][j] == 0 && matriz[i][j] != 0)
            return 0;
        }
      } 
        return 1; // 1 significa que ganhou -> quando todos os elementos de matriz são iguasi aos de gabarito e iguais a zero
    }


    

    //Função que faz as operações dos comandos
    
    int Comandos(char *comando)
    {
      if (strcmp (comando, "resolver\n") == 0)
        return 1;

      else if (strcmp (comando, "dica\n") == 0)    
        return 2;
      
      else
      {
        for (int i = 0; i < MAX; i++)
        {
          if(comando[0] == 'm' && comando[1] == 'a' && comando[2] == 'n' && comando[3] == 't' && comando[4] == 'e' && comando[5] == 'r')
            return 3;
          else if(comando[0] == 's' && comando[1] == 'a' && comando[2] == 'l' && comando[3] == 'v' && comando[4] == 'a' && comando[5] == 'r')
            return 4;
          else if (comando[0] == 'v' && comando[1] == 'o' && comando[2] == 'l' && comando[3] == 't' && comando[4] == 'a' && comando[5] == 'r')
            return 5;
          else if(comando[0] == 'r' && comando[1] == 'e' && comando[2] == 'm' && comando[3] == 'o' && comando[4] == 'v' && comando[5] == 'e' && comando[6] == 'r')
            return 6;
        }
      }
      return 0;
    }

    Jogadores ColetarDadosJogador(Jogadores player)
    {
      printf(YELLOW("\nDigite o nome do jogador: "));
      fgets(player.nome, MAX, stdin);

      int i = 0;      //tirando o \n do nome do jogador
      while(player.nome[i] != '\n')
      {
        i++;
      }
      player.nome[i] = '\0';

      return player;
    }

    InfoTabuleiro ColetarDadosJogo(InfoTabuleiro tabuleiro, char *comando, char *dificuldade)
    {
        printf(YELLOW("\nDigite o tamanho do tabuleiro (3 à 9): "));
        fgets(comando, MAX, stdin);
        
        tabuleiro.tamanho = comando[0] - '0';

        while((tabuleiro.tamanho > 9 || tabuleiro.tamanho < 3 ) || comando[1] != '\n') //validação do tamanho do tabuleiro
        {
          printf("\nTamanho ");
          printf(RED("INVÁLIDO!"));
          printf(" Digite uma número de 3 à 9: ");
          fgets(comando, MAX, stdin);
          tabuleiro.tamanho = comando[0] - '0';
        }
      
        if(tabuleiro.tamanho < 5)
          *dificuldade = 'f';
        
        else if(tabuleiro.tamanho < 7)
        {
          printf(YELLOW("\nDigite o nível de dificuldade: Fácil("));
          printf(BLUE("F"));
          printf(YELLOW(" ou "));
          printf(BLUE("f"));
          printf(YELLOW(") ou Médio("));
          printf(GREEN("M"));
          printf(YELLOW(" ou "));
          printf(GREEN("m"));
          printf(YELLOW("): "));
          fgets(comando, MAX, stdin);
          *dificuldade = comando[0];
        }

        else if(tabuleiro.tamanho <= 9)
        {
          printf(YELLOW("\nDigite o nível de dificuldade: Fácil("));
          printf(BLUE("F"));
          printf(YELLOW(" ou "));
          printf(BLUE("f"));
          printf(YELLOW("), Médio("));
          printf(GREEN("M"));
          printf(YELLOW(" ou "));
          printf(GREEN("m"));
          printf(YELLOW(") ou Difícil("));
          printf(RED("D"));
          printf(YELLOW(" ou "));
          printf(RED("d"));
          printf(YELLOW("): "));
          fgets(comando, MAX, stdin);
          *dificuldade = comando[0];
        }

        //Validando a dificuldade
        while(((*dificuldade) != 'f' && (*dificuldade) != 'F' && (*dificuldade) != 'm' && (*dificuldade) != 'M' && (*dificuldade) != 'd' && (*dificuldade) != 'D') || comando[1] != '\n')
        {
          printf("\n\nComando ");
          printf(RED("inválido!"));
          printf(" Digite apenas um dos caracteres mostrados: ");
          fflush(stdin);
          fgets(comando, MAX, stdin);
          (*dificuldade) = comando[0];
        }
        

        while(tabuleiro.tamanho < 7 && ((*dificuldade) == 'd' || (*dificuldade) == 'D'))
        {
          printf("\nO nível ");
          printf(RED("DIFÍCIL"));
          printf(" só está disponível para dimensões acima de 7!\n");

          printf("\nDigite novamente o nível de dificuldade: ");

          if(tabuleiro.tamanho < 7)
          {
            printf("Fácil(");
            printf(BLUE("F"));
            printf(" ou ");
            printf(BLUE("f"));
            printf(") ou Médio(");
            printf(GREEN("M"));
            printf(" ou ");
            printf(GREEN("m"));
            printf("): ");
          }
          
          fgets(comando, MAX, stdin);
          (*dificuldade) = comando[0];

          while(comando[1] != '\n')
          {
            printf("\nDigite apenas um caracter!\n");
            fgets(comando, MAX, stdin);
            (*dificuldade) = comando[0];  
          }
        }
        return tabuleiro;
    }



