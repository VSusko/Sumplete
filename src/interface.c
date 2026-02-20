#include "interface.h"
#include "novojogo.h"

void ExibirComandos()
{
	printf(BOLD(YELLOW("\n\nComandos:")));
	printf(GREEN(" resolver,"));
	printf(BLUE(" dica,"));
	printf(CYAN(" manter,"));
	printf(MAGENTA(" remover,"));
	printf(" salvar,");
	printf(RED(" voltar\n\n"));
}


void ImprimeTabTela(int quantidade_tabs)
{
	for(int i = 0; i < quantidade_tabs; i++)
		printf(" ");
}


void Valida_acao(int *acao)
{
	while (scanf("%d", acao) == 0 || *acao < 0 || *acao > 3){
			printError("\nAção inválida! Digite um número de 0 a 3: ");
			limpabuffer();
	}
}


void ValidaNomeArquivo(char *nome_do_arquivo)
{
	while (scanf("%s", nome_do_arquivo) == 0)
    {
        int tamanho_nome = strlen(nome_do_arquivo);
		if(!strcmp(nome_do_arquivo, "0"))
			return;
        if(nome_do_arquivo[tamanho_nome-1] != 't' || nome_do_arquivo[tamanho_nome-2] != 'x' || nome_do_arquivo[tamanho_nome-3] != 't' || nome_do_arquivo[tamanho_nome-4] != '.'){   
            printError("\nFormato NÃO suportado! Digite o nome do arquivo.txt: ");
        }
        else{
            printError("\nERRO! Digite apenas o nome do arquivo: ");
        }
        limpabuffer();
    }
}

void ExibirTabuleiro(Tabuleiro_t *tabuleiro)
{
	#if DEBUG
		// printf("Soma das linhas do tabuleiro: ");
		// for(int i = 0; i < tabuleiro->tamanho; i++){
		// 	printf("%d ", tabuleiro->somaLinhasUsuario[i]);
		// }
		// printf("\n");

		// printf("Soma das colunas do tabuleiro: ");
		// for(int i = 0; i < tabuleiro->tamanho; i++){
		// 	printf("%d ", tabuleiro->somaColunasUsuario[i]);
		// }
		// printf("\n");

		// printf("Dificuldade do jogo: %c\n", tabuleiro->dificuldade);
	#endif


	// Imprimindo o tabuleiro - 1 linha
	ImprimeTabTela(tabuleiro->tamanho);

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
	ImprimeTabTela(tabuleiro->tamanho);

	printf(TAB_VER "       " TAB_VER);

	for (int i = 0; i < tabuleiro->tamanho; i++)
	{
		printf("  %2d   " TAB_VER, i + 1);
	}

	printf("       " TAB_VER);
	printf("\n");

	// Imprimindo o tabuleiro - 3 linha
	ImprimeTabTela(tabuleiro->tamanho);

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
		ImprimeTabTela(tabuleiro->tamanho);
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
		if (tabuleiro->somaLinhasTabela[i] < -9){
			if(tabuleiro->somaLinhasTabela[i] == tabuleiro->somaLinhasUsuario[i]){
				printf(BOLD(YELLOW(" %2d   ")) TAB_VER, tabuleiro->somaLinhasTabela[i]);
			}
			else{
				printf(YELLOW(" %2d   ") TAB_VER, tabuleiro->somaLinhasTabela[i]);
			}
		}
		else{
			if(tabuleiro->somaLinhasTabela[i] == tabuleiro->somaLinhasUsuario[i]){
				printf(BOLD(YELLOW("  %2d   ")) TAB_VER, tabuleiro->somaLinhasTabela[i]); // soma de cada linha
			}
			else{
				printf(YELLOW("  %2d   ") TAB_VER, tabuleiro->somaLinhasTabela[i]); // soma de cada linha
			}

		}
		printf("\n");

		// Divisorias das linhas
		ImprimeTabTela(tabuleiro->tamanho);

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
	ImprimeTabTela(tabuleiro->tamanho);

	printf(TAB_VER "       " TAB_VER);

	for (int i = 0; i < tabuleiro->tamanho; i++)
	{
		if (tabuleiro->somaColunasTabela[i] < -9){
			if(tabuleiro->somaColunasTabela[i] == tabuleiro->somaColunasUsuario[i])
				printf(BOLD(YELLOW("  %2d  ")) TAB_VER, tabuleiro->somaColunasTabela[i]);
			else
				printf(YELLOW("  %2d  ") TAB_VER, tabuleiro->somaColunasTabela[i]);
		}
		else{
			if(tabuleiro->somaColunasTabela[i] == tabuleiro->somaColunasUsuario[i])
				printf(BOLD(YELLOW("  %2d   ")) TAB_VER, tabuleiro->somaColunasTabela[i]); // soma de cada coluna
			else{
				printf(YELLOW("  %2d   ") TAB_VER, tabuleiro->somaColunasTabela[i]); // soma de cada coluna
			}
		}
	}
	printf("       " TAB_VER);

	printf("\n");

	// Imprimindo o tabuleiro - ultima linha
	ImprimeTabTela(tabuleiro->tamanho);

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

	ExibirComandos();
}

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

void TelaDeFim(Jogador_t *jogador, time_t tempo_ini, bool usou_resolver, char dificuldade)
{
	time_t tempo_fim = time(NULL);
	int base = 1000;

	jogador->tempo = tempo_fim - tempo_ini;

	if(dificuldade == 'm' || dificuldade == 'M')
		jogador->pontuacao = (base*2) / (jogador->tempo+1);
	if(dificuldade == 'd' || dificuldade == 'D')
		jogador->pontuacao = (base*3) / (jogador->tempo+1);
	else
		jogador->pontuacao = base / (jogador->tempo+1);

	if(usou_resolver)
		jogador->pontuacao = 0;
		
	printf(CYAN("\nFIM DE JOGO!!\n"));
	printf("\nTempo gasto pelo jogador ");
	printf(BOLD(YELLOW("%s")), jogador->nome);
	printf(": ");
	printf(MAGENTA("%ld"), jogador->tempo);
	printf(" segundos.\n");
	
	printf("Pontuação obtida: ");
	printf(MAGENTA("%ld\n\n\n"), jogador->pontuacao);


	if(usou_resolver)
	{
		ExibirRanking();
		printf(RED("\n\nVOCÊ USOU O COMANDO RESOLVER, ENTÃO VOCÊ NÃO ENTRARÁ PARA O RANKING!\n\n"));
		return;
	}
	ConstroiRanking(jogador);
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