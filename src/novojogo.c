#include "novojogo.h"

void criaGabarito(Tabuleiro_t *tabuleiro)
{
	// Obtendo semente aleatória
	srand(time(NULL));

	// Gerando gabarito aleatorio para a dificuldade facil
	if (tabuleiro->dificuldade == 'f' || tabuleiro->dificuldade == 'F'){
		
		for (int i = 0; i < tabuleiro->tamanho; i++){
			for (int j = 0; j < tabuleiro->tamanho; j++)
			{
				tabuleiro->gabarito[i][j] = rand() % 2;
			}
		}
	}
	
	// Gerando gabarito aleatorio para a dificuldade médio. Não pode existir linhas nem colunas com apenas 0s ou 1s
	else if (tabuleiro->dificuldade == 'm' || tabuleiro->dificuldade == 'M'){
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

	// Gerando gabarito aleatorio para a dificuldade médio. Não pode existir linhas nem colunas com apenas 1s
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

	// Gerando uma matriz com numeros aleatorios para as dificuldades fácil e médio
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

	// Gerando uma matriz com numeros aleatorios para a dificuldades difícil
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

	// Inicializando o numero maximo de dicas
	tabuleiro->max_dicas = 0;

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
	// Itera sobre o tamanho do tabuleiro
	for(int i = 0; i < tabuleiro->tamanho; i++)
	{
		// Se encontrar alguma soma que não bate, retorna false
		if (tabuleiro->somaLinhasTabela[i] != tabuleiro->somaLinhasUsuario[i]  
			 || tabuleiro->somaColunasTabela[i] != tabuleiro->somaColunasUsuario[i])
			return false;
	}

	// Passou por todas as somas e todas bateram
    return true;
}

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

	// Se o tamanho do tabuleiro é menor que 5, a dificuldade é sempre fácil
	if (tabuleiro->tamanho < 5){
		tabuleiro->dificuldade = 'f';
		limpabuffer();
		return;
	}
	
	// Se o tamanho do tabuleiro é até 6, a dificuldade pode ser fácil ou médio
	if (tabuleiro->tamanho < 7){
		ImprimirSelecaoDificuldade(tabuleiro->tamanho);
		// Validação da seleção de dificuldade
		while(scanf(" %c", &tabuleiro->dificuldade) == 0 || (tabuleiro->dificuldade != 'f' && tabuleiro->dificuldade != 'F' 
			&& tabuleiro->dificuldade != 'm' && tabuleiro->dificuldade != 'M'))
		{
			// Verificação da dificuldade difícil (so disponivel aciam de 6)
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
	// Se o tamanho do tabuleiro é até 9, a dificuldade pode ser fácil, médio ou difícil
	else{
		ImprimirSelecaoDificuldade(tabuleiro->tamanho);
		// Validação da seleção de dificuldade
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


bool NovoJogo(Tabuleiro_t *tabuleiro, Jogador_t *jogador, int *acao)
{
	// Strings que serao utilizadas para receber comandos
	char entrada_usuario[MAX_STRING];
	char comando_arg1[MAX_STRING/2];
	char comando_arg2[MAX_STRING/2];

	// Variável que conta quantas dicas já foram dadas
	int contadicas = 0;
	// Flag que define se o usuario usou o comando resolver
	bool usou_resolver = false;
	tabuleiro->dificuldade = 'c'; 

	#if DEBUG
		strcpy(jogador->nome, "SUQUINHO");
		tabuleiro->tamanho = 5;
		tabuleiro->dificuldade = 'm';
		limpabuffer();
	#else
		// Entrada do nome do jogador
		printf(YELLOW("\nDigite o nome do jogador: "));
		scanf("%s", jogador->nome);
		limpabuffer();
		// Entrada de dados do jogo
		ColetarDadosJogo(tabuleiro); 
	#endif

	// Cria uma instancia de jogo
	criaJogo(tabuleiro);
	// Obtem o tamanho do tabuleiro
	jogador->tamanho = tabuleiro->tamanho;

	// Mostra o tabuleiro para o jogador
	ExibirTabuleiro(tabuleiro);
	
	// Comeca a contar o tempo do jogo
	time_t tempo_ini = time(NULL);

	// Enquanto o jogador não tiver ganhado, repete o loop de comandos
	while (JogadorGanhou(tabuleiro) == false)
	{
		// Obtem e valida a entrada do usuario
		while(fgets(entrada_usuario, sizeof(entrada_usuario), stdin) == NULL)
		{
			printError("\nComando inválido! Digite um comando válido: ");
		}
		// Separando o comando em 2 argumentos
		sscanf(entrada_usuario,"%s %s", comando_arg1, comando_arg2);

		// Obtendo o numero correspondente ao comando
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
				Manter(tabuleiro, comando_arg2, &contadicas);
				break;

			// Comando Salvar
			case 4:
				Salvar(tabuleiro, jogador, comando_arg2, tempo_ini);
				break;
			
			// Comando Voltar
			case 5:
				Voltar(tabuleiro, acao);
				// Se o jogador optou por sair do jogo, iniciar um jogo novo ou continuar jogo salvo, libera a memoria e retorna falso
				if(*acao == 0 || *acao == 1 || *acao == 2) 
					return false;
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
	// Exibe a tela de fim de jogo
	TelaDeFim(jogador, tempo_ini, usou_resolver, tabuleiro->dificuldade);
	// Libera a memória
	liberaTabuleiro(tabuleiro);
	// Retorna true se o jogador resolveu o jogo
	return true;
}