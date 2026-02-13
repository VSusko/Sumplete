#include "jogo.h"
#include "auxiliares.h"
#include "comandos.h"
#include "interface.h"
#include "dbg.h"

int main()
{
	// String que será utilizada ao longo de todo o codigo para receber comandos
	char entrada_usuario[2][MAX_STRING];
	// Variavel que irá fazer os comandos do Menu
	int acao = 0;
	// Variável que irá contar quantas dicas já foram dadas
	int contadicas;
	// Estrutura que armazena as informações do tabuleiro
	Tabuleiro_t tabuleiro = {0};
	// Estrutura que armazena as informações do jogador
	Jogador_t jogador;

	Menu();
	scanf("%d", &acao);
	
	// Validação da entrada do menu
	while (acao < 0 || acao > 4)
	{
		printError("\nAção inválida! Digite um número de 0 a 4: ");
		scanf("%d", &acao);
	}

	while (acao != 5)
	{
		contadicas = 0, tabuleiro.dificuldade = 'c';

		if (acao == 0)
			return 0;

		else if (acao == 1)
		{
			contadicas = 0, tabuleiro.dificuldade = 'c'; // reset das variaveis

			fflush(stdin); // Função que limpa o buffer

			#if DEBUG
				strcpy(jogador.nome, "SUQUINHO");
				tabuleiro.tamanho = 5;
				tabuleiro.dificuldade = 'f';
			#else
				// Entrada do nome do jogador
				printf(YELLOW("\nDigite o nome do jogador: "));
				scanf("%s", jogador->nome);
				limpabuffer();
				// Entrada de dados do jogo
				tabuleiro = ColetarDadosJogo(tabuleiro); 
			#endif

			criaJogo(&tabuleiro);
			jogador.tamanho = tabuleiro.tamanho;

			// Mostra o tabuleiro para o jogador
			ImprimeTabuleiro(&tabuleiro);
			
			// Comeca a contar o tempo do jogo
			time_t begin = time(NULL);

			while (JogadorGanhou(&tabuleiro) == false)
			{
				scanf("%s%s", entrada_usuario[0], entrada_usuario[1]);
				limpabuffer();

				int num_comando = ComandoParaNumero(entrada_usuario[0]);

				switch (num_comando)
				{
					case 0:
						printf("\n\nComando ");
						printf(RED("inválido!"));
						printf(" Digite um comando válido:\n\n");
						break;
					
					// Comando Resolver
					case 1:
						Resolver(&tabuleiro, &jogador, begin);
						acao = 5;
						break;
					
					// Comando dica
					case 2: 
						Dica(&tabuleiro, &contadicas);
						break;

					// Comando Manter
					case 3:
						Manter(&tabuleiro, entrada_usuario[1]);
						break;

					// Comando Salvar
					case 4:
						Salvar(&tabuleiro, &jogador, entrada_usuario[1], begin);
						break;
					
					// Comando Voltar
					case 5:
						Voltar(&tabuleiro, &acao);
						break;
						
					// Remover
					case 6:
						Remover(&tabuleiro, entrada_usuario[1], &contadicas, &acao);
						break;
						
					default:
						break;
				}
			}
			if (acao == 1) // O jogador digitou o comando voltar e depois digitou 1 para começar um novo jogo
				continue;
			else if (acao == 2) // O jogador digitou o comando voltar e depois digitou 2 para carregar jogo salvo
				continue;

			else
			{
				ImprimirFim(jogador, begin);
				liberaTabuleiro(&tabuleiro);
				acao = 5;
			}
		}

		else if (acao == 2) // Carregar jogo salvo
		{
			printf("\nNao implementado ainda\n");
			// carregarJogo(&*tabuleiro2, comando, &jogador2, &matriz2);

			// ImprimeTabuleiro(tabuleiro, matriz2);

			// fgets(comando, MAX_STRING, stdin);
			// acao = comando[0] - '0';
			// while(comando[1] != '\n' || acao < 0 || acao > 4)
			// {
			//   printf(RED("\n\nComando inválido!\n\n"));
			//   fgets(comando, MAX_STRING, stdin);
			//   acao = comando[0] - '0';
			// }
			// continue;
		}

		else if (acao == 3) // Continuar jogo atual
		{
			ImprimirAcao3(&acao);
			continue;
		}
		else if (acao == 4) // Exibir ranking
		{
			ImprimirAcao4(&acao);
			continue;
		}

		MenuJogarNovamente(&acao);
	}

	return 0;
}