#include "jogo.h"
#include "auxiliares.h"
#include "comandos.h"
#include "interface.h"
#include "dbg.h"

int main()
{
	// Variavel que irá fazer os comandos do Menu
	int acao = 0;
	// Estrutura que armazena as informações do tabuleiro
	Tabuleiro_t tabuleiro = {0};
	// Estrutura que armazena as informações do jogador
	Jogador_t jogador = {0};

	// Exibe o menu de acoes
	Menu();
	
	// Validação da entrada do menu
	Valida_acao(&acao);

	while (acao != 0)
	{
		switch (acao)
		{
			// Começar um novo jogo
			case 1:
				ComecarNovoJogo(&tabuleiro, &jogador, &acao);
				MenuJogarNovamente(&acao);
				break;
			
			// Carregar jogo salvo
			case 2:
				CarregarJogoSalvo(&tabuleiro, &jogador, &acao);
				// MenuJogarNovamente(&acao);
				break;

			// Exibir Ranking
			case 3:
				ExibirRanking();
				Menu();
				Valida_acao(&acao);
				break;
			
			default:
				break;
		}
	}

	return 0;
}