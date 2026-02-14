#include "carregarjogo.h"


void CarregarJogoSalvo(Tabuleiro_t *tabuleiro, Jogador_t *jogador)
{
    char nome_do_arquivo[MAX_STRING/2];
    char caminho_do_arquivo[MAX_STRING];

    int contador_manter, contador_remover;

    printf(YELLOW("\nDigite o nome do arquivo salvo (ex: save.txt): "));

    ValidaNomeArquivo(nome_do_arquivo);
    
    // Concatenando o caminho do arquivo com o nome do arquivo
    strcpy(caminho_do_arquivo, CAMINHO_SAVES);
    strcat(caminho_do_arquivo, nome_do_arquivo);

    FILE *arquivo;
    while ((arquivo = fopen(caminho_do_arquivo, "r")) == NULL)
    {
        printError("\nArquivo não encontrado! Digite um nome de arquivo válido: ");
        ValidaNomeArquivo(nome_do_arquivo);
        return;
    }

    // Lendo o tamanho do tabuleiro
    if (fscanf(arquivo, "%d", &tabuleiro->tamanho) == 0 || tabuleiro->tamanho < 3 || tabuleiro->tamanho > 9)
    {
        printError("\nErro ao ler o arquivo! O tamanho do tabuleiro é inválido.\n");
        fclose(arquivo);
        return;
    }

    // Alocando memoria para a matriz dos numeros do tabuleiro
	criaMatrizInt(&(tabuleiro->tabela_numeros), tabuleiro->tamanho);
	// Alocando memoria para a matriz manipulada pelo usuario
	criaMatrizInt(&(tabuleiro->tabela_usuario), tabuleiro->tamanho);
	// Alocando memoria para a matriz do gabarito
	criaMatrizBool(&(tabuleiro->gabarito), tabuleiro->tamanho);

    for (int i = 0; i < tabuleiro->tamanho; i++)
    {
        for (int j = 0; j < tabuleiro->tamanho; j++)
        {
            tabuleiro->tabela_usuario[i][j] = 1;
        }
    }

    // Alocando memoria para a soma de linhas e colunas do tabuleiro
	tabuleiro->somaColunasTabela = calloc(tabuleiro->tamanho, sizeof(int));
	tabuleiro->somaLinhasTabela = calloc(tabuleiro->tamanho, sizeof(int));

    tabuleiro->somaColunasUsuario = calloc(tabuleiro->tamanho, sizeof(int));
    tabuleiro->somaLinhasUsuario = calloc(tabuleiro->tamanho, sizeof(int));

    // Coletando os números do tabuleiro
    for(int i = 0; i < tabuleiro->tamanho; i++)
    {
        for(int j = 0; j < tabuleiro->tamanho; j++){
            if (fscanf(arquivo, "%d", &tabuleiro->tabela_numeros[i][j]) == 0)
            {
                printError("\nErro ao ler o arquivo! Número do tabuleiro inexistenet.\n");
                fclose(arquivo);
                return;
            }
            tabuleiro->somaLinhasUsuario[i] += tabuleiro->tabela_numeros[i][j];
            tabuleiro->somaColunasUsuario[j] += tabuleiro->tabela_numeros[i][j];
        }
    }
        
    // Coletando a soma das linhas do tabuleiro
    for(int i = 0; i < tabuleiro->tamanho; i++)
    {
        if (fscanf(arquivo, "%d", &tabuleiro->somaLinhasTabela[i]) == 0)
        {
            printError("\nErro ao ler o arquivo! Sem soma de linhas!\n");
            fclose(arquivo);
            return;
        }
    }

    // Coletando a soma das colunas do tabuleiro
    for(int i = 0; i < tabuleiro->tamanho; i++)
    {
        if (fscanf(arquivo, "%d", &tabuleiro->somaColunasTabela[i]) == 0)
        {
            printError("\nErro ao ler o arquivo! Sem soma de colunas!\n");
            fclose(arquivo);
            return;
        }
    }

    // Coletando o número de vezes que o jogador usou o comando manter
    if (fscanf(arquivo, "%d", &contador_manter) == 0)
    {
        printError("\nErro ao ler o arquivo! O formato do arquivo é inválido.\n");
        fclose(arquivo);
        return;
    }

    // Inserindo elementos que o jogador escolheu manter na matriz do usuário
    for(int i = 0; i < contador_manter; i++)
    {
        int linha, coluna;
        if (fscanf(arquivo, "%d %d", &linha, &coluna) == 0)
        {
            printError("\nErro ao ler o arquivo! Elemento inexistente!.\n");
            fclose(arquivo);
            return;
        }
        tabuleiro->tabela_usuario[linha-1][coluna-1] = 2;
    }

    // Coletando o número de vezes que o jogador usou o comando remover
    if (fscanf(arquivo, "%d", &contador_remover) == 0)
    {
        printError("\nErro ao ler o arquivo! O formato do arquivo é inválido.\n");
        fclose(arquivo);
        return;
    }

    // Inserindo elementos que o jogador escolheu remover na matriz do usuário
    for(int i = 0; i < contador_remover; i++)
    {
        int linha, coluna;
        if (fscanf(arquivo, "%d %d", &linha, &coluna) == 0)
        {
            printError("\nErro ao ler o arquivo! Elemento inexistente!\n");
            fclose(arquivo);
            return;
        }
        tabuleiro->tabela_usuario[linha-1][coluna-1] = 0;
        tabuleiro->somaLinhasUsuario[linha-1] -= tabuleiro->tabela_numeros[linha-1][coluna-1];
        tabuleiro->somaColunasUsuario[coluna-1] -= tabuleiro->tabela_numeros[linha-1][coluna-1];
    }

    // Coletando o nome do jogador
    if (fscanf(arquivo, "%s", jogador->nome) == 0)
    {
        printError("\nErro ao ler o arquivo! Sem nome do jogador.\n");
        fclose(arquivo);
        return;
    }

    // Coletando o tempo gasto pelo jogador até aquele momento
    if (fscanf(arquivo, "%ld", &jogador->tempo) == 0)
    {
        printError("\nErro ao ler o arquivo! Sem o tempo do jogador.\n");
        fclose(arquivo);
        return;
    }

    return;
}

bool VerificaGabarito(Tabuleiro_t *tabuleiro)
{
    int somaLinha, somaColuna;
    for(int i = 0; i < tabuleiro->tamanho; i++)
    {
        somaLinha = 0;
        somaColuna = 0;
        for(int j = 0; j < tabuleiro->tamanho; j++)
        {
            somaLinha += tabuleiro->tabela_numeros[i][j];
            somaColuna += tabuleiro->tabela_numeros[j][i];
        }
        if(tabuleiro->somaLinhasTabela[i] != somaLinha || tabuleiro->somaColunasTabela[i] != somaColuna)
            return false;
    }

    return true;
}


void EncontraGabarito(Acha_gabarito_t *inst, int linha, int coluna, bool *acabou)
{
    if(linha == inst->tabuleiro->tamanho || coluna == inst->tabuleiro->tamanho)
    {
        if(VerificaGabarito(inst->tabuleiro) == true)
        {
            *acabou = true;
            return;
        }
    }

    for(int i = linha; i < inst->tabuleiro->tamanho; i++)
    {
        for(int j = coluna; j < inst->tabuleiro->tamanho; j++)
        {
            if(inst->tabuleiro->tabela_numeros[linha][coluna] + inst->soma_acumulada_linha[linha] <= inst->tabuleiro->somaLinhasTabela[linha]
            && inst->tabuleiro->tabela_numeros[linha][coluna] + inst->soma_acumulada_coluna[coluna] <= inst->tabuleiro->somaColunasTabela[coluna]
            && !(*acabou))
            {
                inst->soma_acumulada_linha[linha] += inst->tabuleiro->tabela_numeros[linha][coluna];
                inst->soma_acumulada_coluna[coluna] += inst->tabuleiro->tabela_numeros[linha][coluna];
                inst->tabuleiro->gabarito[linha][coluna] = 1;

                EncontraGabarito(inst, linha, coluna+1, acabou);
                EncontraGabarito(inst, linha+1, coluna, acabou);

                inst->soma_acumulada_linha[linha] -= inst->tabuleiro->tabela_numeros[linha][coluna];
                inst->soma_acumulada_coluna[coluna] -= inst->tabuleiro->tabela_numeros[linha][coluna];
                inst->tabuleiro->gabarito[linha][coluna] = 0;
            }
        }
    }

    EncontraGabarito(inst, linha+1, coluna, acabou);
    EncontraGabarito(inst, linha, coluna+1, acabou);

    return;
}


void ContinuarJogo(Tabuleiro_t *tabuleiro, Jogador_t *jogador, int *acao)
{
	CarregarJogoSalvo(tabuleiro, jogador);

    #if DEBUG
        // Debug_str("\nDEBUG DO JOGO\n");
        // printf("Nome do jogador: %s\n", jogador->nome);
        // printf("Tempo gasto: %ld\n", jogador->tempo);
        // printf("Tamanho do tabuleiro: %d\n", jogador->tamanho);

        // printf("Tabuleiro numeros:\n");
        // for(int i = 0; i < tabuleiro->tamanho; i++){
        //     for(int j = 0; j < tabuleiro->tamanho; j++){
        //         printf("%d ", tabuleiro->tabela_numeros[i][j]);
        //     }
        //     printf("\n");
        // }

        // printf("Tabuleiro usuario:\n");
        // for(int i = 0; i < tabuleiro->tamanho; i++){
        //     for(int j = 0; j < tabuleiro->tamanho; j++){
        //         printf("%d ", tabuleiro->tabela_usuario[i][j]);
        //     }
        //     printf("\n");
        // }

        // printf("Soma linhas:\n");
        // for(int i = 0; i < tabuleiro->tamanho; i++){
        //     printf("%d ", tabuleiro->somaLinhasTabela[i]);
        // }

        // printf("\nSoma colunas:\n");
        // for(int i = 0; i < tabuleiro->tamanho; i++){
        //     printf("%d ", tabuleiro->somaColunasTabela[i]);
        // }
        // printf("\n");

    #endif
    
    char entrada_usuario[MAX_STRING];
	char comando_arg1[MAX_STRING/2];
	char comando_arg2[MAX_STRING/2];
    bool possui_gabarito = false;
    bool usou_resolver = false;

    // Variável que irá contar quantas dicas já foram dadas
    int contadicas = 0;

    // Mostra o tabuleiro para o jogador
	ExibirTabuleiro(tabuleiro);

    Acha_gabarito_t instancia_gabarito = {0};
    instancia_gabarito.tabuleiro = tabuleiro;
    instancia_gabarito.soma_acumulada_linha = calloc(tabuleiro->tamanho, sizeof(int));
    instancia_gabarito.soma_acumulada_coluna = calloc(tabuleiro->tamanho, sizeof(int));
    
    // Função que econtra um gabarito
    EncontraGabarito(&instancia_gabarito, 0, 0, &possui_gabarito);

    free(instancia_gabarito.soma_acumulada_linha);
    free(instancia_gabarito.soma_acumulada_coluna);

    if(possui_gabarito == false)
    {
        printError("\nO jogo não possui solução!.\n");
        return;
    }

    // Comeca a contar o tempo do jogo
	time_t tempo_ini = time(NULL);
    tempo_ini += jogador->tempo;
    limpabuffer();

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
                usou_resolver = true;
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
			
            // Comando inválido
			default:
				printError("\nComando inválido! Digite um comando válido: ");
				break;
		}
	}
	TelaDeFim(jogador, tempo_ini, usou_resolver);
	liberaTabuleiro(tabuleiro);
	*acao = 0;

	return;
}