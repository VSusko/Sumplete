#include "jogo.h"

// void rankingInicia(RankingBuilder *rankingBuilder)
// {
//   // Inicializando jogadores_por_categoria e total_jogadores

//   rankingBuilder->total_jogadores = 0;

//   // Inicializando a matriz ranking
//   for (int i = 0; i < 6; i++)
//   {
//     rankingBuilder->jogadores_por_categoria[i] = 0;
//     for (int j = 0; j < 5; j++)
//     {
//       strcpy(rankingBuilder->ranking[i][j].nome, ""); // Inicializa o nome com uma string vazia
//       rankingBuilder->ranking[i][j].tempo = 0;        // Inicializa o tempo com 0
//       rankingBuilder->ranking[i][j].tamanho = 0;      // Inicializa o tamanho com 0
//     }
//   }
// }

bool jogadoresSaoIguais(Jogadores x, Jogadores y)
{
	if (strcmp(x.nome, y.nome) || x.tamanho != y.tamanho || x.tempo != y.tempo)
		return false;

	return true;
}

// Função que cria um gabarito para um jogo, não funciona sem a função criaJogo

void criaGabarito(int ***gabarito, int nlines, char dificuldade)
{
	criaMatriz(gabarito, nlines);

	srand(time(NULL));

	// Gerando gabarito aleatorio

	if (dificuldade == 'f' || dificuldade == 'F')
		for (int i = 0; i < nlines; i++)
			for (int j = 0; j < nlines; j++)
			{
				(*gabarito)[i][j] = rand() % 2;
			}

	else if (dificuldade == 'm' || dificuldade == 'M')
	{
		// variaveis que irão validar a soma das linhas e das colunas

		int Validar_Soma_Linha = 0;
		int Validar_Soma_Coluna = 0;

		do
		{
			for (int i = 0; i < nlines; i++)
			{
				Validar_Soma_Linha = 0;
				for (int j = 0; j < nlines; j++)
				{
					(*gabarito)[i][j] = rand() % 2;
					if ((*gabarito)[i][j] == 1)
					{
						Validar_Soma_Linha++;
					}
					else if (j == nlines - 1 && (Validar_Soma_Linha == nlines || Validar_Soma_Linha == 0))
						break;
				}
				if (Validar_Soma_Linha == nlines || Validar_Soma_Linha == 0)
					break;
			}

			if (Validar_Soma_Linha == nlines || Validar_Soma_Linha == 0)
				continue;

			else
			{
				for (int i = 0; i < nlines; i++)
				{
					Validar_Soma_Coluna = 0;
					for (int j = 0; j < nlines; j++)
					{
						if ((*gabarito)[j][i] == 1)
							Validar_Soma_Coluna++;
						else if (j == nlines - 1 && (Validar_Soma_Coluna == nlines || Validar_Soma_Coluna == 0))
							break;
					}
					if (Validar_Soma_Coluna == nlines || Validar_Soma_Coluna == 0)
						break;
				}
			}
		} while (Validar_Soma_Linha == nlines || Validar_Soma_Coluna == nlines || Validar_Soma_Linha == 0 || Validar_Soma_Coluna == 0);
	}

	else if (dificuldade == 'd' || dificuldade == 'D')
	{
		// variaveis que irão validar a soma das linhas e das colunas

		int Validar_Soma_Linha = 0;
		int Validar_Soma_Coluna = 0;

		do
		{
			for (int i = 0; i < nlines; i++)
			{
				Validar_Soma_Linha = 0;
				for (int j = 0; j < nlines; j++)
				{
					(*gabarito)[i][j] = rand() % 2;
					if ((*gabarito)[i][j] == 1)
					{
						Validar_Soma_Linha++;
					}
					else if (j == nlines - 1 && Validar_Soma_Linha == nlines)
						break;
				}
				if (Validar_Soma_Linha == nlines)
					break;
			}

			if (Validar_Soma_Linha == nlines)
				continue;

			else
			{
				for (int i = 0; i < nlines; i++)
				{
					Validar_Soma_Coluna = 0;
					for (int j = 0; j < nlines; j++)
					{
						if ((*gabarito)[j][i] == 1)
						{
							Validar_Soma_Coluna++;
						}
						else if (j == nlines - 1 && Validar_Soma_Coluna == nlines)
							break;
					}
					if (Validar_Soma_Coluna == nlines)
						break;
				}
			}
		} while (Validar_Soma_Linha == nlines || Validar_Soma_Coluna == nlines);
	}
}

bool RankingWrite(RankingBuilder _r_builder)
{
	/*
	  Variáveis para armazenar as posições do último jogador a ser gravado no ranking.
	  A única função dessas variáveis é a de evitar a escrita de uma linha vazia no final do arquivo,
	  pois caso isso aconteça, na próxima leitura de ranking a linha vazia será lida e preenchida como sendo
	  um jogador existente.
	*/
	Jogadores ultimo;

	// Abrindo o arquivo em modo escrita
	FILE *gravar = fopen(RANKING_PATH, "w");

	// Caso não seja possível abrir o arquivo
	if (gravar == NULL)
		return false;

	// Procurando pelo último jogador
	for (int i = 0; i < NUM_TABULEIROS; i++)
	{
		if (_r_builder.jogadores_por_categoria[i] != 0)
		{
			ultimo = _r_builder.ranking[i][_r_builder.jogadores_por_categoria[i] - 1];
		}
	}

	for (int i = 0; i < NUM_TABULEIROS; i++)
	{
		// Caso não tenha jogadores numa categoria, pular para a próxima
		if (_r_builder.jogadores_por_categoria[i] == 0)
			continue;

		fprintf(gravar, "size = %d\n", i + 3);
		for (int j = 0; j < _r_builder.jogadores_por_categoria[i]; j++)
		{
			fprintf(gravar, "player%d = %s\n", j + 1, _r_builder.ranking[i][j].nome);

			if (jogadoresSaoIguais(ultimo, _r_builder.ranking[i][j]))
				fprintf(gravar, "time%d = %ld", j + 1, _r_builder.ranking[i][j].tempo);
			else
				fprintf(gravar, "time%d = %ld\n", j + 1, _r_builder.ranking[i][j].tempo);
		}

		if (i != NUM_TABULEIROS - 1)
			fprintf(gravar, "\n");
	}
	fclose(gravar);

	return true;
}

// Função que imrprime o rank "sumplete.ini" e acrescenta os dados do jogador

void Ranking(Jogadores player)
{
	Jogadores players_buffer[MAX_PLAYERS] = {};
	char string[100], stringaux[100];
	unsigned int size, contador_players = 0, j, i = 0, contador_size[6] = {0};
	unsigned int player_pos;

	RankingBuilder r_builder = {};

	FILE *arquivo = fopen(RANKING_PATH, "r");
	if (arquivo != NULL)
	{
		// Coleta de dados dos jogadores

		while (!feof(arquivo))
		{
			fgets(string, 100, arquivo);

			if (string[0] == 's')
			{
				size = string[7] - '0';
				i = 0;
			}

			if (string[0] == 'p')
			{
				sscanf(string, "%*s %*c %s", r_builder.ranking[size - 3][i].nome);
				r_builder.ranking[size - 3][i].tamanho = size;
			}

			if (string[0] == 't')
			{
				sscanf(string, "%*s %*c %ld", &r_builder.ranking[size - 3][i].tempo);
				r_builder.total_jogadores++;
				r_builder.jogadores_por_categoria[size - 3]++;
				i++;
			}
		}

#if DEBUG
		// _Debug_printRankingBuilder(r_builder);
			Debug_str("\nPLAYER TAMANHO = ")
			printf("%d\n", player.tamanho);
#endif

		// Adicionando dados do jogador nos jogadores do ranking
		j = 0;
		for (i = 0; i < NUM_TABULEIROS; i++)
		{
			// Caso não seja a categoria do jogador, pegue a proxima
			if (player.tamanho != i + 3)
				continue;

			// Caso a categoria está cheia e o jogador teve um tempo maior que o último colocado, o jogador não entra no ranking e o loop encerra
			if (r_builder.jogadores_por_categoria[i] == PLAYERS_POR_TABULEIRO &&
				player.tempo > r_builder.ranking[i][r_builder.jogadores_por_categoria[i] - 1].tempo)
				break;

			// Caso a categoria esteja vazia, o jogador será inserido na primeira posição
			if (r_builder.jogadores_por_categoria[i] == 0)
			{
				r_builder.ranking[i][0] = player;
				r_builder.jogadores_por_categoria[i]++;
				r_builder.total_jogadores++;
				break;
			}

			// Caso uma categoria não esteja cheia e o tempo do jogador seja o último da categoria, ele será inserido na ultima posição
			if (r_builder.jogadores_por_categoria[i] < PLAYERS_POR_TABULEIRO &&
				player.tempo >= r_builder.ranking[i][r_builder.jogadores_por_categoria[i] - 1].tempo)
			{
				r_builder.ranking[i][r_builder.jogadores_por_categoria[i]] = player;
				r_builder.jogadores_por_categoria[i]++;
				r_builder.total_jogadores++;
				break;
			}

			/*
			  Último caso: o jogador fez um tempo melhor do que o último colocado. É preciso percorrer
			  os jogadores da categoria para encontrar a posição do jogador no ranking. Depois de encontrada essa posição,
			  a posição dos outros jogadores no ranking deve ser reajustada
			*/
			if (player.tempo < r_builder.ranking[i][r_builder.jogadores_por_categoria[i] - 1].tempo)
			{
				// Percorrendo os jogadores do ranking
				for (j = 0; j < r_builder.jogadores_por_categoria[i]; j++)
				{
					// Se o tempo do jogador for melhor do que o jogador da iteração, ele deve ser encaixado nessa posição
					if (player.tempo < r_builder.ranking[i][j].tempo)
					{
						player_pos = j; // Pegando a posição do jogador
						break;
					}
				}

				// Caso a categoria ainda não esteja cheia, o número de jogadores nessa categoria aumenta
				if (r_builder.jogadores_por_categoria[i] < PLAYERS_POR_TABULEIRO)
				{
					r_builder.jogadores_por_categoria[i]++;
					r_builder.total_jogadores++;
				}

				// j recebe a posição do último jogador dessa categoria
				j = r_builder.jogadores_por_categoria[i] - 1;

				// Enquanto j for maior que a posição do jogador, os demais jogadores serão empurrados para baixo
				while (j > player_pos)
				{
					r_builder.ranking[i][j] = r_builder.ranking[i][j - 1];
					j--;
				}

				// A posição do jogador no ranking é sobrescrita com os dados do jogador
				r_builder.ranking[i][player_pos] = player;
				break;
			}
		}

#if DEBUG
		_Debug_printRankingandPlayer(r_builder, player);
#endif

		// Imprimindo o ranking no terminal - cabeçalho
		ImprimirRankingHeader();

		// Imprimindo ranking no terminal - corpo do ranking
		ImprimirRankingBody(r_builder, player);

		// Gravando os dados do ranking no arquivo
		RankingWrite(r_builder);
	}
	else
		printError("\nO arquivo ""sumplete.ini"" não existe!\n")

	fclose(arquivo);
}

// Função que cria um jogo e retorna as alterações no tabuleiro e o gabarito desse jogo

Tabuleiro_t criaJogo(Tabuleiro_t tabuleiro, int ***gabarito, char dificuldade)
{
	// Alocando memoria para a matriz do tabuleiro

	criaMatriz(&tabuleiro.matriz, tabuleiro.tamanho);

	// Alocando memoria para a soma de linhas e colunas do tabuleiro

	tabuleiro.somaColunas = malloc(tabuleiro.tamanho * sizeof(int));
	tabuleiro.somaLinhas = malloc(tabuleiro.tamanho * sizeof(int));

	// Gerando semente aleatória para os números e a soma

	srand(time(NULL));

	// Gerando uma matriz com numeros aleatorios

	if (dificuldade == 'f' || dificuldade == 'F' || dificuldade == 'm' || dificuldade == 'M')
	{
		for (int i = 0; i < tabuleiro.tamanho; i++)
		{
			for (int j = 0; j < tabuleiro.tamanho; j++)
			{
				tabuleiro.matriz[i][j] = 1 + (rand() % 9);
			}
		}
	}

	else if (dificuldade == 'd' || dificuldade == 'D')
	{
		for (int i = 0; i < tabuleiro.tamanho; i++)
		{
			for (int j = 0; j < tabuleiro.tamanho; j++)
			{
				tabuleiro.matriz[i][j] = (rand() % 19) - 9;
			}
		}
	}

	// Gerando matriz gabarito

	criaGabarito(&*gabarito, tabuleiro.tamanho, dificuldade);

	// Limpando a memoria das somas das linhas e colunas

	for (int i = 0; i < tabuleiro.tamanho; i++)
	{
		tabuleiro.somaLinhas[i] = 0;
		tabuleiro.somaColunas[i] = 0;
	}

	// Soma das linhas e colunas segundo o gabarito
	for (int i = 0; i < tabuleiro.tamanho; i++)
	{
		for (int j = 0; j < tabuleiro.tamanho; j++)
		{
			if ((*gabarito)[i][j] == 1)
			{
				tabuleiro.somaLinhas[i] += tabuleiro.matriz[i][j];
				tabuleiro.somaColunas[j] += tabuleiro.matriz[i][j];
			}
		}
	}

	return tabuleiro;
}

// Função que compara o gabarito com a matriz que está sendo manipulada pelo usuario

int Comparador(Tabuleiro_t tabuleiro, int **gabarito, int **matriz)
{
	for (int i = 0; i < tabuleiro.tamanho; i++)
	{
		for (int j = 0; j < tabuleiro.tamanho; j++)
		{
			if (gabarito[i][j] == 0 && matriz[i][j] != 0)
				return 0;
		}
	}
	return 1; // 1 significa que ganhou -> quando todos os elementos de matriz são iguasi aos de gabarito e iguais a zero
}

// Função que faz as operações dos comandos

int Comandos(char *comando)
{
	if (strcmp(comando, "resolver\n") == 0)
		return 1;

	else if (strcmp(comando, "dica\n") == 0)
		return 2;

	else
	{
		for (int i = 0; i < MAX_STRING; i++)
		{
			if (comando[0] == 'm' && comando[1] == 'a' && comando[2] == 'n' && comando[3] == 't' && comando[4] == 'e' && comando[5] == 'r')
				return 3;
			else if (comando[0] == 's' && comando[1] == 'a' && comando[2] == 'l' && comando[3] == 'v' && comando[4] == 'a' && comando[5] == 'r')
				return 4;
			else if (comando[0] == 'v' && comando[1] == 'o' && comando[2] == 'l' && comando[3] == 't' && comando[4] == 'a' && comando[5] == 'r')
				return 5;
			else if (comando[0] == 'r' && comando[1] == 'e' && comando[2] == 'm' && comando[3] == 'o' && comando[4] == 'v' && comando[5] == 'e' && comando[6] == 'r')
				return 6;
		}
	}
	return 0;
}

Jogadores ColetarDadosJogador(Jogadores player)
{
	printf(YELLOW("\nDigite o nome do jogador: "));
	fgets(player.nome, MAX_STRING, stdin);

	int i = 0; // tirando o \n do nome do jogador
	while (player.nome[i] != '\n')
	{
		i++;
	}
	player.nome[i] = '\0';

	return player;
}

Tabuleiro_t ColetarDadosJogo(Tabuleiro_t tabuleiro, char *comando, char *dificuldade)
{
	printf(YELLOW("\nDigite o tamanho do tabuleiro (3 à 9): "));
	fgets(comando, MAX_STRING, stdin);

	tabuleiro.tamanho = comando[0] - '0';

	while ((tabuleiro.tamanho > 9 || tabuleiro.tamanho < 3) || comando[1] != '\n') // validação do tamanho do tabuleiro
	{
		printf("\nTamanho ");
		printf(RED("INVÁLIDO!"));
		printf(" Digite uma número de 3 à 9: ");
		fgets(comando, MAX_STRING, stdin);
		tabuleiro.tamanho = comando[0] - '0';
	}

	if (tabuleiro.tamanho < 5)
		*dificuldade = 'f';

	else if (tabuleiro.tamanho < 7)
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
		fgets(comando, MAX_STRING, stdin);
		*dificuldade = comando[0];
	}

	else if (tabuleiro.tamanho <= 9)
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
		fgets(comando, MAX_STRING, stdin);
		*dificuldade = comando[0];
	}

	// Validando a dificuldade
	while (((*dificuldade) != 'f' && (*dificuldade) != 'F' && (*dificuldade) != 'm' && (*dificuldade) != 'M' && (*dificuldade) != 'd' && (*dificuldade) != 'D') || comando[1] != '\n')
	{
		printf("\n\nComando ");
		printf(RED("inválido!"));
		printf(" Digite apenas um dos caracteres mostrados: ");
		fflush(stdin);
		fgets(comando, MAX_STRING, stdin);
		(*dificuldade) = comando[0];
	}

	while (tabuleiro.tamanho < 7 && ((*dificuldade) == 'd' || (*dificuldade) == 'D'))
	{
		printf("\nO nível ");
		printf(RED("DIFÍCIL"));
		printf(" só está disponível para dimensões acima de 7!\n");

		printf("\nDigite novamente o nível de dificuldade: ");

		if (tabuleiro.tamanho < 7)
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

		fgets(comando, MAX_STRING, stdin);
		(*dificuldade) = comando[0];

		while (comando[1] != '\n')
		{
			printf("\nDigite apenas um caracter!\n");
			fgets(comando, MAX_STRING, stdin);
			(*dificuldade) = comando[0];
		}
	}
	return tabuleiro;
}
