#include "carregarjogo.h"


bool CarregarJogoSalvo(Tabuleiro_t *tabuleiro, Jogador_t *jogador)
{
    char nome_do_arquivo[MAX_STRING/2];
    char caminho_do_arquivo[MAX_STRING];

    int contador_manter, contador_remover;

    printf(YELLOW("\nDigite o nome do arquivo salvo"));
    printf(" (ex: save.txt) ");
    printf(YELLOW("ou digite "));
    printf("0 ");
    printf(YELLOW("para voltar ao menu principal: "));

    ValidaNomeArquivo(nome_do_arquivo);
    
    // Se o jogador quer voltar
    if(!strcmp(nome_do_arquivo,"0"))
        return false;

    // Concatenando o caminho do arquivo com o nome do arquivo
    strcpy(caminho_do_arquivo, CAMINHO_SAVES);
    strcat(caminho_do_arquivo, nome_do_arquivo);

    FILE *arquivo;
    while ((arquivo = fopen(caminho_do_arquivo, "r")) == NULL)
    {
        printError("\nArquivo não encontrado! Digite um nome de arquivo válido ou 0 para voltar: ");
        ValidaNomeArquivo(nome_do_arquivo);
        return false;
    }

    // Lendo o tamanho do tabuleiro
    if (fscanf(arquivo, "%d", &tabuleiro->tamanho) == 0 || tabuleiro->tamanho < 3 || tabuleiro->tamanho > 9)
    {
        printError("\nErro ao ler o arquivo! O tamanho do tabuleiro é inválido.\n");
        fclose(arquivo);
        return false;
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
                return false;
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
            return false;
        }
    }

    // Coletando a soma das colunas do tabuleiro
    for(int i = 0; i < tabuleiro->tamanho; i++)
    {
        if (fscanf(arquivo, "%d", &tabuleiro->somaColunasTabela[i]) == 0)
        {
            printError("\nErro ao ler o arquivo! Sem soma de colunas!\n");
            fclose(arquivo);
            return false;
        }
    }

    // Coletando o número de vezes que o jogador usou o comando manter
    if (fscanf(arquivo, "%d", &contador_manter) == 0)
    {
        printError("\nErro ao ler o arquivo! O formato do arquivo é inválido.\n");
        fclose(arquivo);
        return false;
    }

    // Inserindo elementos que o jogador escolheu manter na matriz do usuário
    for(int i = 0; i < contador_manter; i++)
    {
        int linha, coluna;
        if (fscanf(arquivo, "%d %d", &linha, &coluna) == 0)
        {
            printError("\nErro ao ler o arquivo! Elemento inexistente!.\n");
            fclose(arquivo);
            return false;
        }
        tabuleiro->tabela_usuario[linha-1][coluna-1] = 2;
    }

    // Coletando o número de vezes que o jogador usou o comando remover
    if (fscanf(arquivo, "%d", &contador_remover) == 0)
    {
        printError("\nErro ao ler o arquivo! O formato do arquivo é inválido.\n");
        fclose(arquivo);
        return false;
    }

    // Inserindo elementos que o jogador escolheu remover na matriz do usuário
    for(int i = 0; i < contador_remover; i++)
    {
        int linha, coluna;
        if (fscanf(arquivo, "%d %d", &linha, &coluna) == 0)
        {
            printError("\nErro ao ler o arquivo! Elemento inexistente!\n");
            fclose(arquivo);
            return false;
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
        return false;
    }

    // Coletando o tempo gasto pelo jogador até aquele momento
    if (fscanf(arquivo, "%ld", &jogador->tempo) == 0)
    {
        printError("\nErro ao ler o arquivo! Sem o tempo do jogador.\n");
        fclose(arquivo);
        return false;
    }
    
    if (fscanf(arquivo, "%c", &tabuleiro->dificuldade) == 0)
    {
        printError("\nErro ao ler o arquivo! Sem a dificuldade do jogo.\n");
        fclose(arquivo);
        return false;
    }

    return true;
}

bool VerificaGabarito(Encontra_gabarito_t *inst)
{
    // Itera sobre as somas
    for (int i = 0; i < inst->tabuleiro->tamanho; i++)
    {
        // Se alguma soma não bate, retorna falso
        if (inst->soma_acumulada_linha[i] != inst->tabuleiro->somaLinhasTabela[i] ||
            inst->soma_acumulada_coluna[i] != inst->tabuleiro->somaColunasTabela[i])
                return false;
    }
    return true;
}


void EncontraGabarito(Encontra_gabarito_t *inst, int posicao, bool *acabou)
{
    // Copia o tamanho do tabuleiro
    int n = inst->tabuleiro->tamanho;

    // Se ja encontrou uma solução, retorna
    if (*acabou)
        return;

    // Se ja chegou na ultima posucao
    if (posicao == n * n)
    {
        if(VerificaGabarito(inst))
            *acabou = true;
            
        return;
    }

    // Obtem a linha e a coluna
    int i = posicao / n;
    int j = posicao % n;

    
    int valor = inst->tabuleiro->tabela_numeros[i][j];

    // ========= Obtendo limitante por linha =========
    // Somas minimas e maximas por linha
    int soma_min_linha = 0;
    int soma_max_linha = 0;

    // A partir da coluna j, itera ate o final da linha
    for (int k = j; k < n; k++)
    {
        int v = inst->tabuleiro->tabela_numeros[i][k];
        if (v > 0)
            soma_max_linha += v;
        else
            soma_min_linha += v;
    }

    // Copia a soma já acumulada
    int atual_linha = inst->soma_acumulada_linha[i];
    // Copia a soma real (alvo)
    int alvo_linha = inst->tabuleiro->somaLinhasTabela[i];

    // Se a soma atual da linha + minimo ultrapassa o valor da soma real ou 
    // soma atual da linha + max não atinge o valor da soma real, retorna
    if (atual_linha + soma_min_linha > alvo_linha ||
        atual_linha + soma_max_linha < alvo_linha)
        return;

    // ========= Obtendo limitante por coluna =========
    // Somas minimas e maximas por coluna
    int soma_min_coluna = 0;
    int soma_max_coluna = 0;

    // A partir da coluna i, itera ate o final da coluna
    for (int k = i; k < n; k++)
    {
        int v = inst->tabuleiro->tabela_numeros[k][j];
        if (v > 0)
            soma_max_coluna += v;
        else
            soma_min_coluna += v;
    }

    // Copia a soma já acumulada
    int atual_coluna = inst->soma_acumulada_coluna[j];
    // Copia a soma real (alvo)
    int alvo_coluna = inst->tabuleiro->somaColunasTabela[j];

    // Se a soma atual da coluna + minimo ultrapassa o valor da soma real ou 
    // soma atual da coluna + max não atinge o valor da soma real, retorna
    if (atual_coluna + soma_min_coluna > alvo_coluna ||
        atual_coluna + soma_max_coluna < alvo_coluna)
        return;

    // tenta inserir 1 e realiza as somas
    inst->tabuleiro->gabarito[i][j] = 1;
    inst->soma_acumulada_linha[i] += valor;
    inst->soma_acumulada_coluna[j] += valor;

    EncontraGabarito(inst, posicao + 1, acabou);

    // Desfaz as somas
    inst->soma_acumulada_linha[i] -= valor;
    inst->soma_acumulada_coluna[j] -= valor;

    // Se ainda não encontrou uma solução, insere 0
    if (!(*acabou))
    {
        inst->tabuleiro->gabarito[i][j] = 0;
        EncontraGabarito(inst, posicao + 1, acabou);
    }

    // Se já encontrou a solução, retorna
    return;
}

void RecalculaDicas(Tabuleiro_t *tabuleiro, int *contadicas)
{
    tabuleiro->max_dicas = 0;
    for (int i = 0; i < tabuleiro->tamanho; i++)
	{
		for (int j = 0; j < tabuleiro->tamanho; j++)
		{
			// Se no gabarito o valor deve ser mantido, o jogador tem direito a uma dica para aquele número
			if(tabuleiro->gabarito[i][j] == 1)
            {
                tabuleiro->max_dicas++;
                if(tabuleiro->tabela_usuario[i][j] == 1)
                    (*contadicas)++;
            }
		}
	}
}


bool ContinuarJogo(Tabuleiro_t *tabuleiro, Jogador_t *jogador, int *acao)
{
    // Caso tenha algum erro ao carregar o jogo salvo ou o jogador escolheu voltar ao menu
	if(!CarregarJogoSalvo(tabuleiro, jogador))
        return false;

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
    
    // Strings que serao utilizadas para receber comandos
    char entrada_usuario[MAX_STRING];
	char comando_arg1[MAX_STRING/2];
	char comando_arg2[MAX_STRING/2];
    // Flag que define se um gabarito foi encontrado
    bool possui_gabarito = false;
    // Flag que define se o usuario usou o comando resolver
    bool usou_resolver = false;

    // Variável que irá contar quantas dicas já foram dadas
    int contadicas = 0;

    // Criando a instância da estrutura que procura um gabarito
    Encontra_gabarito_t instancia_gabarito = {0};
    instancia_gabarito.tabuleiro = tabuleiro;
    instancia_gabarito.soma_acumulada_linha = calloc(tabuleiro->tamanho, sizeof(int));
    instancia_gabarito.soma_acumulada_coluna = calloc(tabuleiro->tamanho, sizeof(int));
    
    printf(BOLD(RED("\nEncontrando solução! Aguarde...\n\n")));
    
    // Função que econtra um gabarito
    EncontraGabarito(&instancia_gabarito, 0, &possui_gabarito);
    
    // Liberando a estrutura
    free(instancia_gabarito.soma_acumulada_linha);
    free(instancia_gabarito.soma_acumulada_coluna);

    // Se não existe nenhum gabarito, retorna false
    if(possui_gabarito == false)
    {
        printError("O jogo não possui solução!.\n");
        return false;

    }

    // Caso contrário, mostra que encontrou uma solução
    printf(BOLD(GREEN("Solução Encontrada!\n\n")));
    
    // Recalcula as dicas (contador e máxima) conforme o gabarito encontrado
    RecalculaDicas(tabuleiro, &contadicas);
    
    // Mostra o tabuleiro para o jogador
	ExibirTabuleiro(tabuleiro);

    // Comeca a contar o tempo do jogo
	time_t tempo_ini = time(NULL) - jogador->tempo;
    limpabuffer();

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
			
            // Comando inválido
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