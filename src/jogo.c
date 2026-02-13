#include "jogo.h"

void Valida_acao(int *acao)
{
	while (scanf("%d", acao) == 0 || *acao < 0 || *acao > 3){
			printError("\nAção inválida! Digite um número de 0 a 3: ");
			limpabuffer();
	}
}

bool jogadoresSaoIguais(Jogador_t x, Jogador_t y)
{
	if (strcmp(x.nome, y.nome) || x.tamanho != y.tamanho || x.tempo != y.tempo)
		return false;

	return true;
}

// Função que cria um gabarito para um jogo, não funciona sem a função criaJogo
void criaGabarito(Tabuleiro_t *tabuleiro)
{
	srand(time(NULL));

	// Gerando gabarito aleatorio

	if (tabuleiro->dificuldade == 'f' || tabuleiro->dificuldade == 'F')
		for (int i = 0; i < tabuleiro->tamanho; i++)
			for (int j = 0; j < tabuleiro->tamanho; j++)
			{
				tabuleiro->gabarito[i][j] = rand() % 2;
			}

	else if (tabuleiro->dificuldade == 'm' || tabuleiro->dificuldade == 'M')
	{
		// variaveis que irão validar a soma das linhas e das colunas
		int Validar_Soma_Linha = 0;
		int Validar_Soma_Coluna = 0;

		do
		{
			for (int i = 0; i < tabuleiro->tamanho; i++)
			{
				Validar_Soma_Linha = 0;
				for (int j = 0; j < tabuleiro->tamanho; j++)
				{
					tabuleiro->gabarito[i][j] = rand() % 2;
					if (tabuleiro->gabarito[i][j] == 1)
					{
						Validar_Soma_Linha++;
					}
					else if (j == tabuleiro->tamanho - 1 && (Validar_Soma_Linha == tabuleiro->tamanho || Validar_Soma_Linha == 0))
						break;
				}
				if (Validar_Soma_Linha == tabuleiro->tamanho || Validar_Soma_Linha == 0)
					break;
			}

			if (Validar_Soma_Linha == tabuleiro->tamanho || Validar_Soma_Linha == 0)
				continue;

			else
			{
				for (int i = 0; i < tabuleiro->tamanho; i++)
				{
					Validar_Soma_Coluna = 0;
					for (int j = 0; j < tabuleiro->tamanho; j++)
					{
						if (tabuleiro->gabarito[j][i] == 1)
							Validar_Soma_Coluna++;
						else if (j == tabuleiro->tamanho - 1 && (Validar_Soma_Coluna == tabuleiro->tamanho || Validar_Soma_Coluna == 0))
							break;
					}
					if (Validar_Soma_Coluna == tabuleiro->tamanho || Validar_Soma_Coluna == 0)
						break;
				}
			}
		} while (Validar_Soma_Linha == tabuleiro->tamanho || Validar_Soma_Coluna == tabuleiro->tamanho || Validar_Soma_Linha == 0 || Validar_Soma_Coluna == 0);
	}

	else if (tabuleiro->dificuldade == 'd' || tabuleiro->dificuldade == 'D')
	{
		// variaveis que irão validar a soma das linhas e das colunas

		int Validar_Soma_Linha = 0;
		int Validar_Soma_Coluna = 0;

		do
		{
			for (int i = 0; i < tabuleiro->tamanho; i++)
			{
				Validar_Soma_Linha = 0;
				for (int j = 0; j < tabuleiro->tamanho; j++)
				{
					tabuleiro->gabarito[i][j] = rand() % 2;
					if (tabuleiro->gabarito[i][j] == 1)
					{
						Validar_Soma_Linha++;
					}
					else if (j == tabuleiro->tamanho - 1 && Validar_Soma_Linha == tabuleiro->tamanho)
						break;
				}
				if (Validar_Soma_Linha == tabuleiro->tamanho)
					break;
			}

			if (Validar_Soma_Linha == tabuleiro->tamanho)
				continue;

			else
			{
				for (int i = 0; i < tabuleiro->tamanho; i++)
				{
					Validar_Soma_Coluna = 0;
					for (int j = 0; j < tabuleiro->tamanho; j++)
					{
						if (tabuleiro->gabarito[j][i] == 1)
						{
							Validar_Soma_Coluna++;
						}
						else if (j == tabuleiro->tamanho - 1 && Validar_Soma_Coluna == tabuleiro->tamanho)
							break;
					}
					if (Validar_Soma_Coluna == tabuleiro->tamanho)
						break;
				}
			}
		} while (Validar_Soma_Linha == tabuleiro->tamanho || Validar_Soma_Coluna == tabuleiro->tamanho);
	}
	return;
}

bool RankingWrite(Ranking_t _r_builder)
{
	/*
	  Variáveis para armazenar as posições do último jogador a ser gravado no ranking.
	  A única função dessas variáveis é a de evitar a escrita de uma linha vazia no final do arquivo,
	  pois caso isso aconteça, na próxima leitura de ranking a linha vazia será lida e preenchida como sendo
	  um jogador existente.
	*/
	Jogador_t ultimo;

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
void Ranking(Jogador_t player)
{
	char string[100];
	int size = 3, j, i = 0;
	int player_pos = 0;

	Ranking_t r_builder = {};

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
			if (r_builder.jogadores_por_categoria[i] == MAX_JOGADORES_POR_DIFF &&
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
			if (r_builder.jogadores_por_categoria[i] < MAX_JOGADORES_POR_DIFF &&
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
				if (r_builder.jogadores_por_categoria[i] < MAX_JOGADORES_POR_DIFF)
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
		ImprimirCabecalhoRanking();

		// Imprimindo ranking no terminal - corpo do ranking
		ImprimirCorpoRanking(&r_builder, player);

		// Gravando os dados do ranking no arquivo
		RankingWrite(r_builder);
	}
	else
		printError("\nO arquivo ""sumplete.ini"" não existe!\n")

	fclose(arquivo);
}

// Função que cria um jogo e retorna as alterações no tabuleiro e o gabarito desse jogo
void criaJogo(Tabuleiro_t *tabuleiro)
{
	// Alocando memoria para a matriz dos numeros do tabuleiro
	criaMatrizInt(&(tabuleiro->tabela_numeros), tabuleiro->tamanho);
	// Alocando memoria para a matriz manipulada pelo usuario
	criaMatrizInt(&(tabuleiro->tabela_usuario), tabuleiro->tamanho);
	// Alocando memoria para a matriz do gabarito
	criaMatrizBool(&(tabuleiro->gabarito), tabuleiro->tamanho);

	// Alocando memoria para a soma de linhas e colunas do tabuleiro
	tabuleiro->somaColunas = calloc(tabuleiro->tamanho, sizeof(int));
	tabuleiro->somaLinhas = calloc(tabuleiro->tamanho, sizeof(int));

	// Gerando semente aleatória para os números e a soma
	srand(time(NULL));

	// Gerando uma matriz com numeros aleatorios
	if (tabuleiro->dificuldade == 'f' || tabuleiro->dificuldade == 'F' || tabuleiro->dificuldade == 'm' || tabuleiro->dificuldade == 'M')
	{
		for (int i = 0; i < tabuleiro->tamanho; i++)
		{
			for (int j = 0; j < tabuleiro->tamanho; j++)
			{
				tabuleiro->tabela_numeros[i][j] = 1 + (rand() % 9);
			}
		}
	}

	else if (tabuleiro->dificuldade == 'd' || tabuleiro->dificuldade == 'D')
	{
		for (int i = 0; i < tabuleiro->tamanho; i++)
		{
			for (int j = 0; j < tabuleiro->tamanho; j++)
			{
				tabuleiro->tabela_numeros[i][j] = (rand() % 19) - 9;
			}
		}
	}

	// Gerando matriz gabarito
	criaGabarito(tabuleiro);

	// Soma das linhas e colunas segundo o gabarito
	for (int i = 0; i < tabuleiro->tamanho; i++)
	{
		for (int j = 0; j < tabuleiro->tamanho; j++)
		{
			if (tabuleiro->gabarito[i][j] == true)
			{
				tabuleiro->somaLinhas[i] += tabuleiro->tabela_numeros[i][j];
				tabuleiro->somaColunas[j] += tabuleiro->tabela_numeros[i][j];
			}
		}
	}

	// Inicializando a matriz manipulada pelo usuário com o valor 1, que significa que o número daquela posição ainda não foi manipulado
	for (int i = 0; i < tabuleiro->tamanho; i++)
	{
		for (int j = 0; j < tabuleiro->tamanho; j++)
		{
			tabuleiro->tabela_usuario[i][j] = 1;
			// Se no gabarito o valor deve ser mantido, o jogador tem direito a uma dica para aquele número
			if(tabuleiro->gabarito[i][j] == 1)
                tabuleiro->max_dicas++;
		}
	}

	return;
}

// Função que compara o gabarito com a matriz que está sendo manipulada pelo usuario
bool JogadorGanhou(Tabuleiro_t *tabuleiro)
{
	for (int i = 0; i < tabuleiro->tamanho; i++)
	{
		for (int j = 0; j < tabuleiro->tamanho; j++)
		{
			if (tabuleiro->gabarito[i][j] == 0 && tabuleiro->tabela_usuario[i][j] != 0)
				return false;
		}
	}
	return true; // 1 significa que ganhou -> quando todos os elementos de matriz são iguais aos de gabarito e iguais a zero
}

// Função que faz as operações dos comandos

int ComandoParaNumero(char *entrada_usuario)
{
	if (strcmp(entrada_usuario, "resolver") == 0)
		return 1;

	else if (strcmp(entrada_usuario, "dica") == 0)
		return 2;

	else
	{
		for (int i = 0; i < MAX_STRING; i++)
		{
			if (strcmp(entrada_usuario, "manter") == 0)
				return 3;
			else if (strcmp(entrada_usuario, "salvar") == 0)
				return 4;
			else if (strcmp(entrada_usuario, "voltar") == 0)
				return 5;
			else if (strcmp(entrada_usuario, "remover") == 0)
				return 6;
		}
	}
	return 0;
}


void ColetarDadosJogo(Tabuleiro_t *tabuleiro)
{
	printf(YELLOW("\nDigite o tamanho do tabuleiro (3 à 9): "));
	
	// Validação do tamanho do tabuleiro
	while (scanf("%d", &tabuleiro->tamanho) == 0 || tabuleiro->tamanho > 9 || tabuleiro->tamanho < 3)
	{
		printError("\nTamanho INVÁLIDO! Digite um número de 3 à 9: ");
		limpabuffer();
	}

	if (tabuleiro->tamanho < 5){
		tabuleiro->dificuldade = 'f';
		limpabuffer();
		return;
	}
	
	if (tabuleiro->tamanho < 7){
		ImprimirSelecaoDificuldade(tabuleiro->tamanho);
		while(scanf(" %c", &tabuleiro->dificuldade) == 0 || (tabuleiro->dificuldade != 'f' && tabuleiro->dificuldade != 'F' 
			&& tabuleiro->dificuldade != 'm' && tabuleiro->dificuldade != 'M'))
		{
			if(tabuleiro->dificuldade == 'd' || tabuleiro->dificuldade == 'D')
			{
				printError("\nO nível DIFÍCIL só está disponível para tabuleiros acima de 6!\n");
				printf(YELLOW("\nDigite novamente o nível de dificuldade: "));
			}
			else
				printError("\nComando inválido! Digite um nível de dificuldade válido: ");

			limpabuffer();
		}

	}
	else{
		ImprimirSelecaoDificuldade(tabuleiro->tamanho);
		while(scanf(" %c", &tabuleiro->dificuldade) == 0 || (tabuleiro->dificuldade != 'f' && tabuleiro->dificuldade != 'F' 
			&& tabuleiro->dificuldade != 'm' && tabuleiro->dificuldade != 'M'
			&& tabuleiro->dificuldade != 'd' && tabuleiro->dificuldade != 'D'))
		{
			printError("\nComando inválido! Digite um nível de dificuldade válido: \n");
			limpabuffer();
		}
	}

	limpabuffer();
	return;
}


void ComecarNovoJogo(Tabuleiro_t *tabuleiro, Jogador_t *jogador, int *acao)
{
	// String que será utilizada ao longo de todo o codigo para receber comandos
	char entrada_usuario[MAX_STRING];
	char comando_arg1[MAX_STRING/2];
	char comando_arg2[MAX_STRING/2];

	// Variável que irá contar quantas dicas já foram dadas
	int contadicas = 0;
	tabuleiro->dificuldade = 'c'; 

	#if DEBUG
		strcpy(jogador.nome, "SUQUINHO");
		tabuleiro.tamanho = 5;
		tabuleiro.dificuldade = 'f';
		limpabuffer();
	#else
		// Entrada do nome do jogador
		printf(YELLOW("\nDigite o nome do jogador: "));
		scanf("%s", jogador->nome);
		limpabuffer();
		// Entrada de dados do jogo
		ColetarDadosJogo(tabuleiro); 
	#endif

	criaJogo(tabuleiro);
	jogador->tamanho = tabuleiro->tamanho;

	// Mostra o tabuleiro para o jogador
	ImprimeTabuleiro(tabuleiro);
	
	// Comeca a contar o tempo do jogo
	time_t tempo_ini = time(NULL);

	while (JogadorGanhou(tabuleiro) == false)
	{
		while(fgets(entrada_usuario, sizeof(entrada_usuario), stdin) == NULL)
		{
			printError("\nComando inválido! Digite um comando válido: ");
		}
		sscanf(entrada_usuario,"%s %s", comando_arg1, comando_arg2);

		int num_comando = ComandoParaNumero(comando_arg1);

		switch (num_comando)
		{ 
			// Comando Resolver
			case 1:
				Resolver(tabuleiro, jogador, tempo_ini);
				*acao = 0;
				break;
			
			// Comando dica
			case 2: 
				Dica(tabuleiro, &contadicas);
				break;

			// Comando Manter
			case 3:
				Manter(tabuleiro, comando_arg2);
				break;

			// Comando Salvar
			case 4:
				Salvar(tabuleiro, jogador, comando_arg2, tempo_ini);
				break;
			
			// Comando Voltar
			case 5:
				Voltar(tabuleiro, acao);
				if(*acao == 0 || *acao == 1 || *acao == 2) 
					return;
				break;
				
			// Remover
			case 6:
				Remover(tabuleiro, comando_arg2, &contadicas, acao);
				break;
				
			default:
				printError("\nComando inválido! Digite um comando válido: ");
				break;
		}
	}
	ImprimirFim(jogador, tempo_ini);
	liberaTabuleiro(tabuleiro);
	*acao = 0;
}


void CarregarJogoSalvo(Tabuleiro_t *tabuleiro, Jogador_t *jogador, int *acao)
{
	tabuleiro->dificuldade = 'c';
	jogador->tamanho = 0;
	*acao = *acao;
	printError("\nCarregar jogo salvo ainda não implementado!\n");
	return;
}