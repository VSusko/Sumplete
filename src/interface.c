
#include "interface.h"
#include "jogo.h"

// Função que imprime os comandos do jogo
void ImprimeComandos()
{
	printf(YELLOW("\n\nComandos:"));
	printf(GREEN(" resolver,"));
	printf(BLUE(" dica,"));
	printf(CYAN(" manter,"));
	printf(MAGENTA(" remover,"));
	printf(" salvar,");
	printf(RED(" voltar\n\n"));
}

// Função responsável por imprimir um jogo, recebe uma variavel do tipo tabuleiro
void ImprimeTabuleiro(Tabuleiro_t *tabuleiro)
{
	// Imprimindo o tabuleiro - 1 linha
	int size = tabuleiro->tamanho + 2;

	printf(TAB_TL);
	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j < 7; j++)
			printf(TAB_HOR);

		printf(TAB_TJ);
	}

	for (int j = 0; j < 7; j++)
		printf(TAB_HOR);
	printf(TAB_TR);

	printf("\n");

	// Imprimindo o tabuleiro - 2 linha
	printf(TAB_VER "       " TAB_VER);

	for (int i = 0; i < tabuleiro->tamanho; i++)
	{
		printf("  %2d   " TAB_VER, i + 1);
	}

	printf("       " TAB_VER);
	printf("\n");

	// Imprimindo o tabuleiro - 3 linha
	printf(TAB_ML);
	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j < 7; j++)
			printf(TAB_HOR);

		printf(MAGENTA(TAB_MJ));
	}

	for (int j = 0; j < 7; j++)
		printf(TAB_HOR);

	printf(TAB_MR);

	printf("\n");

	// Imprimindo o tabuleiro - matriz principal
	for (int i = 0; i < tabuleiro->tamanho; i++)
	{
		printf(TAB_VER "  %2d   " TAB_VER, i + 1);
		for (int j = 0; j < tabuleiro->tamanho; j++)
		{
			if (tabuleiro->tabela_usuario[i][j] == 1)
				printf("  %2d   " TAB_VER, tabuleiro->tabela_numeros[i][j]);
			else if (tabuleiro->tabela_usuario[i][j] == 2)
				printf(GREEN("  %2d   ") TAB_VER, tabuleiro->tabela_numeros[i][j]);
			else if (tabuleiro->tabela_usuario[i][j] == 0)
				printf(RED("  %2d   ") TAB_VER, tabuleiro->tabela_numeros[i][j]);
		}
		if (tabuleiro->somaLinhas[i] < -9)
			printf(YELLOW(" %2d   ") TAB_VER, tabuleiro->somaLinhas[i]);
		else
			printf(YELLOW("  %2d   ") TAB_VER, tabuleiro->somaLinhas[i]); // soma de cada linha
		printf("\n");

		// Divisorias das linhas
		if (i < tabuleiro->tamanho - 1)
		{
			printf(TAB_ML);
			for (int k = 0; k < tabuleiro->tamanho + 1; k++)
			{
				for (int j = 0; j < 7; j++)
					printf(TAB_HOR);
				printf(MAGENTA(TAB_MJ));
			}

			for (int j = 0; j < 7; j++)
				printf(TAB_HOR);

			printf(TAB_MR);

			printf("\n");
		}
	}

	// Imprimindo o tabuleiro - antepenultima linha
	printf(TAB_ML);
	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j < 7; j++)
			printf(TAB_HOR);
		printf(MAGENTA(TAB_MJ));
	}

	for (int j = 0; j < 7; j++)
		printf(TAB_HOR);
	printf(TAB_MR);

	printf("\n");

	// Imprimindo o tabuleiro - penultima linha
	printf(TAB_VER "       " TAB_VER);

	for (int i = 0; i < tabuleiro->tamanho; i++)
	{
		if (tabuleiro->somaColunas[i] < -9)
			printf(YELLOW("  %2d  ") TAB_VER, tabuleiro->somaColunas[i]);
		else
			printf(YELLOW("  %2d   ") TAB_VER, tabuleiro->somaColunas[i]); // soma de cada coluna
	}
	printf("       " TAB_VER);

	printf("\n");

	// Imprimindo o tabuleiro - ultima linha
	printf(TAB_BL);
	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j < 7; j++)
			printf(TAB_HOR);
		printf(TAB_BJ);
	}

	for (int j = 0; j < 7; j++)
		printf(TAB_HOR);
	printf(TAB_BR);

	ImprimeComandos();
}

// Função que apenas imprime o rank do arquivo "sumplete.ini"
void ExibirRanking()
{
	FILE *arquivo = fopen(RANKING_PATH, "r");
	if (arquivo != NULL)
	{

		Jogador_t *players;
		char linha[100];
		int size = 3, contador_players = 0, j, i = 0;

		// Cálculo de contagem dos jogadores
		while (fgets(linha, sizeof(linha), arquivo)) {
			if (strncmp(linha, "player", 6) == 0) {
				contador_players++;
			}
		}

		fseek(arquivo, 0, SEEK_SET);

		players = malloc(contador_players * sizeof(Jogador_t));

		// Coleta de dados dos jogadores
		while (!feof(arquivo))
		{
			fgets(linha, 100, arquivo);

			if (strncmp(linha, "size", 4) == 0)
			{
				size = linha[7] - '0';
			}

			players[i].tamanho = size;

			if (strncmp(linha, "player", 6) == 0)
			{
				j = 0;
				while (linha[j + 10] != '\0')
				{
					players[i].nome[j] = linha[j + 10];
					j++;
				}
				players[i].nome[j - 1] = '\0';
			}

			if (strncmp(linha, "time", 4) == 0)
			{
				sscanf(linha, "%*s %*c %ld", &players[i].tempo);
				i++;
			}
		}

		// Imprimindo o ranking no terminal - cabeçalho
		ImprimirCabecalhoRanking();

		// imprimindo ranking no terminal - ranking
		int sizemax = 1;

		for (int i = 0; i < contador_players; i++)
		{
			if (sizemax > 5)
			{
				sizemax = 1;
				continue;
			}
			if (sizemax == 1)
				printf(RED("\nsize = %d\n"), players[i].tamanho);

			printf("player%d = %s\n", sizemax, players[i].nome);
			printf("time%d = %ld\n", sizemax, players[i].tempo);

			if (players[i + 1].tamanho > players[i].tamanho)
				sizemax = 1;
			else
				sizemax++;
		}

		free(players);
	}
	else
		printf("\nO arquivo ""sumplete.ini"" não existe!\n");

	fclose(arquivo);
}

// Função Menu
void Menu()
{
	printf(YELLOW("\n BEM VINDO AO "));
	printf(RED("SU"));printf(BLUE("MP"));printf(CYAN("LE"));printf(MAGENTA("T"));printf("E!\n");
	printf(YELLOW("\nAções:\n"));
	printf(("\n0 |"));printf(YELLOW(" Sair do jogo"));
	printf(("\n1 |"));printf(YELLOW(" Começar um novo jogo"));
	printf(("\n2 |"));printf(YELLOW(" Continuar um jogo salvo em arquivo"));
	printf(("\n3 |"));printf(YELLOW(" Exibir o ranking"));
	printf(YELLOW("\n\nDurante o jogo digite "));printf(RED("“voltar”"));printf(YELLOW(" para retornar ao menu.\n\n"));
}

void MenuVoltar()
{
	printf(YELLOW("\n BEM VINDO AO "));
	printf(RED("SU"));printf(BLUE("MP"));printf(CYAN("LE"));printf(MAGENTA("T"));printf("E!\n");
	printf(YELLOW("\nAções:\n"));
	printf(("\n0 |"));printf(YELLOW(" Sair do jogo"));
	printf(("\n1 |"));printf(YELLOW(" Começar um novo jogo"));
	printf(("\n2 |"));printf(YELLOW(" Continuar um jogo salvo em arquivo"));
	printf(("\n3 |"));printf(YELLOW(" Exibir o ranking"));
	printf(("\n4 |"));printf(YELLOW(" Continuar o jogo atual"));
	printf(YELLOW("\n\nDurante o jogo digite "));printf(RED("“voltar”"));printf(YELLOW(" para retornar ao menu.\n\n"));
}

void ImprimirFim(Jogador_t *jogador, time_t tempo_ini)
{
	time_t tempo_fim = time(NULL);
	jogador->tempo = tempo_fim - tempo_ini; // coleta do tempo do jogador
	printf(CYAN("\nFIM DE JOGO!!\n"));
	printf("\nTempo gasto pelo jogador ");
	printf(BOLD(YELLOW("%s")), jogador->nome);
	printf(": ");
	printf(MAGENTA("%ld"), jogador->tempo);
	printf(" segundos.\n\n\n");
	Ranking(*jogador);
}

void MenuJogarNovamente(int *acao)
{
	printf(YELLOW("\nDeseja jogar novamente?"));
	printf(YELLOW("\nDigite "));printf(RED("1"));
	printf(YELLOW(" para jogar novamente ou "));printf(RED("0"));
	printf(YELLOW(" para sair do jogo:\n\n"));

	while (scanf("%d", acao) == 0 || *acao < 0 || *acao > 1)
	{
		printError("\nComando inválido.");
		printf(YELLOW("\nDigite "));
		printf(RED("1"));
		printf(YELLOW(" para jogar novamente ou "));
		printf(RED("0"));
		printf(YELLOW(" para sair do jogo:\n\n"));
		limpabuffer();
	}

	if (*acao == 1)
	{
		Menu();
		scanf("%d", acao);
		limpabuffer();
		while (*acao < 0 || *acao > 4)
		{
			printError("\nAção inválida! Digite um número de 0 a 4: ");
			scanf("%d", acao);
			limpabuffer();
		}
	}

	return;
}


void ImprimirCabecalhoRanking()
{
	printf("\t" TAB_TL);
	for (int i = 0; i < 23; i++)
	{
		if (i % 2 == 0)
			printf(MAGENTA(TAB_HOR));
		else
			printf(TAB_HOR);
	}
	printf(TAB_TR "\n");
	printf("\t" TAB_VER BLUE(" RANKING DOS JOGADORES ") TAB_VER);
	printf("\n\t" TAB_BL);
	for (int i = 0; i < 23; i++)
	{
		if (i % 2 == 0)
			printf(MAGENTA(TAB_HOR));
		else
			printf(TAB_HOR);
	}
	printf(TAB_BR "\n");
}

void ImprimirCorpoRanking(Ranking_t *_r_builder, Jogador_t _player)
{
	for (int i = 0; i < NUM_TABULEIROS; i++)
	{
		// Caso não tenha jogadores numa categoria, pular para a próxima
		if (_r_builder->jogadores_por_categoria[i] == 0)
			continue;

		printf(_PURPLE("\nsize = %d\n"), i + 3);
		for (int j = 0; j < _r_builder->jogadores_por_categoria[i]; j++)
		{
			if (jogadoresSaoIguais(_player, _r_builder->ranking[i][j]))
			{
				printf(_CYAN("SUA COLOCAÇÃO:\n"));
				printf(_CYAN("player%d = %s\n"), j + 1, _r_builder->ranking[i][j].nome);
				printf(_CYAN("time%d = %ld\n"), j + 1, _r_builder->ranking[i][j].tempo);
			}
			else
			{
				printf(_LIGHT_PURPLE("player%d = %s\n"), j + 1, _r_builder->ranking[i][j].nome);
				printf(_LIGHT_PURPLE("time%d = %ld\n"), j + 1, _r_builder->ranking[i][j].tempo);
			}
		}
	}
}

void ImprimirSelecaoDificuldade(int tamanho_tabuleiro)
{
	if(tamanho_tabuleiro < 7)
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
	}
	else
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
	}
}