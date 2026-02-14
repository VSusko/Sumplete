#include "jogo.h"


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

bool SalvarRanking(Ranking_t *construtor_ranking)
{
	/*
	  Variáveis para armazenar as posições do último jogador a ser gravado no ranking.
	  A única função dessas variáveis é a de evitar a escrita de uma linha vazia no final do arquivo,
	  pois caso isso aconteça, na próxima leitura de ranking a linha vazia será lida e preenchida como sendo
	  um jogador existente.
	*/
	// Jogador_t ultimo;

	// Abrindo o arquivo em modo escrita
	FILE *arquivo = fopen(RANKING_PATH, "w");

	// Caso não seja possível abrir o arquivo
	if (arquivo == NULL)
	{
		printError("\nNão foi possível abrir o arquivo de ranking para escrita!\n");
		return false;
	}

	// Procurando pelo último jogador
	// for (int i = 0; i < NUMERO_DE_TABULEIROS; i++)
	// {
	// 	if (construtor_ranking->jogadores_por_categoria[i] != 0)
	// 	{
	// 		ultimo = construtor_ranking->ranking[i][construtor_ranking->jogadores_por_categoria[i] - 1];
	// 	}
	// }

	for (int i = 0; i < NUMERO_DE_TABULEIROS; i++)
	{
		// Caso não tenha jogadores numa categoria, pular para a próxima
		if (construtor_ranking->num_jogadores_por_categoria[i] == 0)
			continue;

		fprintf(arquivo, "size = %d\n", i + 3);
		for(int j = 0; j < construtor_ranking->num_jogadores_por_categoria[i]; j++)
		{
			fprintf(arquivo, "player%d = %s\n", j + 1, construtor_ranking->ranking[i][j].nome);

			if (j == construtor_ranking->num_jogadores_por_categoria[i] - 1)
				fprintf(arquivo, "time%d = %ld", j + 1, construtor_ranking->ranking[i][j].tempo);
			else
				fprintf(arquivo, "time%d = %ld\n", j + 1, construtor_ranking->ranking[i][j].tempo);
		}

		fprintf(arquivo, "\n");
	}
	fclose(arquivo);

	return true;
}

// Função que faz o rank "sumplete.ini" e acrescenta os dados do jogador
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
		while (!feof(arquivo))
		{
			// le a linha
			fgets(linha, sizeof(linha), arquivo);
			// obtem os argumentos da linha
			sscanf(linha, "%s = %s", arg1, arg2);

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
			if(strncmp(arg1, "time", 4) == 0) {
				construtor_ranking.ranking[tamanho_atual][pos_jogador].tempo = atol(arg2);
				pos_jogador++;
				construtor_ranking.total_jogadores++;
				construtor_ranking.num_jogadores_por_categoria[tamanho_atual]++;
			}
			
		}

		#if DEBUG
			// _Debug_printRankingBuilder(r_builder);
			Debug_str("\nPLAYER TAMANHO = ")
			printf("%d\n", player.tamanho);
		#endif

		// Adicionando dados do jogador nos jogadores do ranking
		for (int i = 0; i < NUMERO_DE_TABULEIROS; i++)
		{
			// Se for a categoria do jogador
			if(jogador->tamanho == i+3)
			{
				// Procura a posição correta do jogador na categoria de acordo com o tempo gasto para resolver o jogo
				for(int j = 0; j < construtor_ranking.num_jogadores_por_categoria[i]; j++)
				{
					if(jogador->tempo < construtor_ranking.ranking[i][j].tempo)
					{
						// Deslocando os jogadores para baixo para adicionar o jogador atual na posição correta
						for(int k = construtor_ranking.num_jogadores_por_categoria[i]-1; k > j; k--)
						{
							construtor_ranking.ranking[i][k] = construtor_ranking.ranking[i][k-1];
						}
						// Adicionando o jogador atual na posição correta
						construtor_ranking.ranking[i][j] = *jogador;
						break;
					}
				}
			}
		}

		// #if DEBUG
			// _Debug_printRankingandPlayer(r_builder, player);
		// #endif

		// Gravando os dados do ranking no arquivo
		SalvarRanking(&construtor_ranking);

		// Imprimindo ranking no terminal - corpo do ranking
		ExibirRankingFim(&construtor_ranking, jogador);
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
	tabuleiro->somaColunasTabela = calloc(tabuleiro->tamanho, sizeof(int));
	tabuleiro->somaLinhasTabela = calloc(tabuleiro->tamanho, sizeof(int));

	tabuleiro->somaColunasUsuario = calloc(tabuleiro->tamanho, sizeof(int));
	tabuleiro->somaLinhasUsuario = calloc(tabuleiro->tamanho, sizeof(int));

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
				tabuleiro->somaLinhasTabela[i] += tabuleiro->tabela_numeros[i][j];
				tabuleiro->somaColunasTabela[j] += tabuleiro->tabela_numeros[i][j];
			}
			tabuleiro->somaColunasUsuario[j] += tabuleiro->tabela_numeros[i][j];
			tabuleiro->somaLinhasUsuario[i] += tabuleiro->tabela_numeros[i][j];
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

bool JogadorGanhou(Tabuleiro_t *tabuleiro)
{
	for(int i = 0; i < tabuleiro->tamanho; i++)
	{
		if (tabuleiro->somaLinhasTabela[i] != tabuleiro->somaLinhasUsuario[i] 
			|| tabuleiro->somaColunasTabela[i] != tabuleiro->somaColunasUsuario[i])
			return false;
	}

    return true;
}

// Função que faz as operações dos comandos
int ComandoParaNumero(char *entrada_usuario)
{
	if (strcmp(entrada_usuario, "resolver") == 0)
		return 1;
	else if (strcmp(entrada_usuario, "dica") == 0)
		return 2;
	else if (strcmp(entrada_usuario, "manter") == 0)
		return 3;
	else if (strcmp(entrada_usuario, "salvar") == 0)
		return 4;
	else if (strcmp(entrada_usuario, "voltar") == 0)
		return 5;
	else if (strcmp(entrada_usuario, "remover") == 0)
		return 6;
		
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
	bool usou_resolver = false;
	tabuleiro->dificuldade = 'c'; 

	#if DEBUG
		strcpy(jogador->nome, "SUQUINHO");
		tabuleiro->tamanho = 9;
		tabuleiro->dificuldade = 'd';
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
	ExibirTabuleiro(tabuleiro);
	
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
				usou_resolver = true;
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
	TelaDeFim(jogador, tempo_ini, usou_resolver);
	liberaTabuleiro(tabuleiro);
	*acao = 0;
}