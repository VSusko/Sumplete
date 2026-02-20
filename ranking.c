#include "ranking.h"

bool SalvarRanking(Ranking_t *construtor_ranking)
{
	// Abrindo o arquivo em modo escrita
	FILE *arquivo = fopen(RANKING_PATH, "w");

	// Caso não seja possível abrir o arquivo
	if (arquivo == NULL)
	{
		printError("\nNão foi possível abrir o arquivo de ranking para escrita!\n");
		return false;
	}

    // Primeira linha do arquivo vem sem \n no começo
	bool primeiroSize = true; 

	for (int i = 0; i < NUMERO_DE_TABULEIROS; i++)
	{
		// Caso não tenha jogadores numa categoria, pular para a próxima
		if (construtor_ranking->num_jogadores_por_categoria[i] == 0)
			continue;

		if(primeiroSize)
		{
			fprintf(arquivo, "size = %d\n", i + 3);
			primeiroSize = false;
		}
		else 
			fprintf(arquivo, "\nsize = %d\n", i + 3);

		for(int j = 0; j < construtor_ranking->num_jogadores_por_categoria[i]; j++)
		{
			fprintf(arquivo, "player%d = %s\n", j + 1, construtor_ranking->ranking[i][j].nome);

			if (j == construtor_ranking->num_jogadores_por_categoria[i] - 1)
				fprintf(arquivo, "score%d = %ld", j + 1, construtor_ranking->ranking[i][j].pontuacao);
			else
				fprintf(arquivo, "score%d = %ld\n", j + 1, construtor_ranking->ranking[i][j].pontuacao);
		}

		fprintf(arquivo, "\n");
	}
	fclose(arquivo);

	return true;
}

void ConstroiRanking(Jogador_t *jogador)
{
	char linha[MAX_STRING];
	char arg1[MAX_STRING/2];
	char arg2[MAX_STRING/2];

	int tamanho_atual = 3, pos_jogador = 0;

	Ranking_t construtor_ranking = {0};

	FILE *arquivo = fopen(RANKING_PATH, "r");
	if (arquivo != NULL)
	{
		// Coleta de dados dos jogadores
		while (fgets(linha, sizeof(linha), arquivo) != NULL)
		{
			// obtem os argumentos da linha
			if (sscanf(linha, "%s = %s", arg1, arg2) != 2)
				continue;

			// se a linha for "size", o tamanho atual é atualizado
			if(strncmp(arg1, "size", 4) == 0) {
				tamanho_atual = (arg2[0] - '0') - 3;
				pos_jogador = 0;
			}
			
			// se a linha for "player", o nome do jogador é adicionado no ranking builder
			if(strncmp(arg1, "player", 6) == 0) {
				construtor_ranking.ranking[tamanho_atual][pos_jogador].tamanho = tamanho_atual;
				strcpy(construtor_ranking.ranking[tamanho_atual][pos_jogador].nome, arg2);
			}
			
			// se a linha for "time", coleta o tempo do jogadore atualiza contadores
			if(strncmp(arg1, "score", 4) == 0) {
				construtor_ranking.ranking[tamanho_atual][pos_jogador].pontuacao = atol(arg2);
				pos_jogador++;
				construtor_ranking.total_jogadores++;
				construtor_ranking.num_jogadores_por_categoria[tamanho_atual]++;
			}
			
		}

		#if DEBUG
			// _Debug_printRankingBuilder(r_builder);
			Debug_str("\nPLAYER TAMANHO = ")
			printf("%d\n", jogador->tamanho);
		#endif

		// Adicionando dados do jogador nos jogadores do ranking
		for (int i = 0; i < NUMERO_DE_TABULEIROS; i++)
		{
			// Se for a categoria do jogador
			if(jogador->tamanho == i+3)
			{
				// Procura a posição correta do jogador na categoria de acordo com o tempo gasto para resolver o jogo
				for(int j = 0; j < MAX_JOGADORES_POR_DIFF; j++)
				{
					if(construtor_ranking.ranking[i][j].pontuacao == 0)
					{
						construtor_ranking.ranking[i][j] = *jogador;
						construtor_ranking.total_jogadores++;
						construtor_ranking.num_jogadores_por_categoria[i]++;
						break;
					}

					if(jogador->pontuacao > construtor_ranking.ranking[i][j].pontuacao)
					{
						printf("num_jogadores_por_categoria[%d] = %d\n", i+3, construtor_ranking.num_jogadores_por_categoria[i]);
						// Deslocando os jogadores para baixo para adicionar o jogador atual na posição correta
						int k;
						if (construtor_ranking.num_jogadores_por_categoria[i] < MAX_JOGADORES_POR_DIFF)
							k = construtor_ranking.num_jogadores_por_categoria[i];
						else
							k = MAX_JOGADORES_POR_DIFF - 1;
						for(; k > j; k--)
						{
							printf("Deslocando jogador %d para a posição %d\n", k, k+1);
							printf("Jogador %d| NOME: %s | TEMPO = %ld|\n", k, construtor_ranking.ranking[i][k-1].nome, construtor_ranking.ranking[i][k-1].pontuacao);
							construtor_ranking.ranking[i][k] = construtor_ranking.ranking[i][k-1];
						}
						// Adicionando o jogador atual na posição correta
						construtor_ranking.ranking[i][j] = *jogador;
						if(construtor_ranking.num_jogadores_por_categoria[i] < MAX_JOGADORES_POR_DIFF)
						{
							construtor_ranking.total_jogadores++;
							construtor_ranking.num_jogadores_por_categoria[i]++;
						}
						break;
					}
				}
			}
		}

		#if DEBUG
			DebugRankingBuilder(&construtor_ranking);
		#endif

		// Gravando os dados do ranking no arquivo
		SalvarRanking(&construtor_ranking);

		// Imprimindo ranking no terminal - corpo do ranking
		ExibirRankingFim(&construtor_ranking, jogador);
	}
	else
		printError("\nO arquivo ""sumplete.ini"" não existe!\n");

	fclose(arquivo);
}


// Função que apenas imprime o rank do arquivo "sumplete.ini"
void ExibirRanking()
{
	FILE *arquivo = fopen(RANKING_PATH, "r");
	if (arquivo == NULL)
	{
		printError("\nO arquivo \"sumplete.ini\" não existe!\n");
		return;
	}

	char linha[MAX_STRING];
	char arg1[MAX_STRING/2];
	char arg2[MAX_STRING/2];

	bool primeiroSize = true;

	ImprimirCabecalhoRanking();

	while (fgets(linha, sizeof(linha), arquivo) != NULL)
	{
		if (sscanf(linha, "%s = %s", arg1, arg2) != 2)
			continue;

		if (strcmp(arg1, "size") == 0)
		{
			if (!primeiroSize)
				printf("\n");  // espaço apenas entre categorias

			printf(_PURPLE("size = %s\n"), arg2);
			primeiroSize = false;
		}
		else if (strncmp(arg1, "player", 6) == 0)
		{
			int numero;
			sscanf(arg1, "player%d", &numero);
			printf(_LIGHT_PURPLE("player%d = %s\n"), numero, arg2);
		}
		else if (strncmp(arg1, "score", 4) == 0)
		{
			int numero;
			sscanf(arg1, "score%d", &numero);
			printf(_LIGHT_PURPLE("score%d = %s\n"), numero, arg2);
		}
	}

	fclose(arquivo);
}



void ExibirRankingFim(Ranking_t *construtor_ranking, Jogador_t *jogador)
{
	ImprimirCabecalhoRanking();

	for (int i = 0; i < NUMERO_DE_TABULEIROS; i++)
	{
		// Caso não tenha jogadores numa categoria, pular para a próxima
		if (construtor_ranking->num_jogadores_por_categoria[i] == 0)
			continue;

		printf(_PURPLE("\nsize = %d\n"), i + 3);
		for (int j = 0; j < construtor_ranking->num_jogadores_por_categoria[i]; j++)
		{
			if (jogadoresSaoIguais(*jogador, construtor_ranking->ranking[i][j]))
			{
				printf(_CYAN("SUA COLOCAÇÃO:\n"));
				printf(_CYAN("player%d = %s\n"), j + 1, construtor_ranking->ranking[i][j].nome);
				printf(_CYAN("score%d = %ld\n"), j + 1, construtor_ranking->ranking[i][j].pontuacao);
			}
			else
			{
				printf(_LIGHT_PURPLE("player%d = %s\n"), j + 1, construtor_ranking->ranking[i][j].nome);
				printf(_LIGHT_PURPLE("score%d = %ld\n"), j + 1, construtor_ranking->ranking[i][j].pontuacao);
			}
		}
	}
}


void ImprimirCabecalhoRanking()
{
	ImprimeTabTela(TAB_TELA);
	printf("\t" TAB_TL);
	for (int i = 0; i < 23; i++)
	{
		if (i % 2 == 0)
			printf(MAGENTA(TAB_HOR));
		else
			printf(TAB_HOR);
	}
	printf(TAB_TR "\n");
	ImprimeTabTela(TAB_TELA);
	printf("\t" TAB_VER BLUE(" RANKING DOS JOGADORES ") TAB_VER);
	printf("\n");
	ImprimeTabTela(TAB_TELA);
	printf("\t" TAB_BL);
	for (int i = 0; i < 23; i++)
	{
		if (i % 2 == 0)
			printf(MAGENTA(TAB_HOR));
		else
			printf(TAB_HOR);
	}
	printf(TAB_BR "\n");

}