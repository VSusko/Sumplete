#include "comandos.h"
#include "carregarjogo.h"

void Resolver(Tabuleiro_t *tabuleiro, Jogador_t *jogador, time_t tempo_ini)
{
    for(int i = 0; i < tabuleiro->tamanho; i++)
    {
        tabuleiro->somaLinhasUsuario[i] = 0;
        tabuleiro->somaColunasUsuario[i] = 0;
    }    
    // Igualando o gabarito com a matriz do usuario
    for(int i = 0; i < tabuleiro->tamanho; i++)
    {
        for(int j = 0; j < tabuleiro->tamanho; j++)
        {
            tabuleiro->tabela_usuario[i][j] = tabuleiro->gabarito[i][j];
            if(tabuleiro->gabarito[i][j] == 1)
            {
                tabuleiro->tabela_usuario[i][j] = 2;
                tabuleiro->somaLinhasUsuario[i] += tabuleiro->tabela_numeros[i][j];
                tabuleiro->somaColunasUsuario[j] += tabuleiro->tabela_numeros[i][j];
            }
        }
    }
    ExibirTabuleiro(tabuleiro);
    time_t tempo_fim = time(NULL);
    jogador->tempo = tempo_fim - tempo_ini;

    return;
}

void Dica(Tabuleiro_t *tabuleiro, int *contadicas)
{
    int linha, coluna;
    bool dica_encontrada = false; 

    if(*contadicas >= tabuleiro->max_dicas)
    {
        printf(RED("\nAs dicas acabaram!\n"));
        return;
    }
    else
    {
        // Enquanto não encontrar uma dica, sorteia uma dica aleatória
        while (dica_encontrada == false)
        {
            linha = rand() % tabuleiro->tamanho;
            coluna = rand() % tabuleiro->tamanho;
            // Se o elemento deve ser mantido, mas o jogador não manteve
            if(tabuleiro->gabarito[linha][coluna] == true && tabuleiro->tabela_usuario[linha][coluna] != 2)
            {
                if(tabuleiro->tabela_usuario[linha][coluna] == 0){
                    tabuleiro->somaLinhasUsuario[linha] += tabuleiro->tabela_numeros[linha][coluna];
                    tabuleiro->somaColunasUsuario[coluna] += tabuleiro->tabela_numeros[linha][coluna];
                }
                tabuleiro->tabela_usuario[linha][coluna] = 2;
                dica_encontrada = true;
                (*contadicas)++;
            }
        }
    }        
    // Imprime a dica revelada
    printf(RED("\n\nDICA REVELADA: "));
    printf("Linha: ");
    printf(GREEN("%d"), linha+1);
    printf(" Coluna: ");
    printf(GREEN("%d\n"), coluna+1);

    ExibirTabuleiro(tabuleiro);
}

//Função que salva o jogo atual e os dados do jogador
void Salvar(Tabuleiro_t *tabuleiro, Jogador_t *jogador, char *nome_do_save, time_t tempo_ini)
{
    
    // Validando o formato do texto

    int tam_nome = strlen(nome_do_save);
    if(nome_do_save[tam_nome-1] != 't' || nome_do_save[tam_nome-2] != 'x' || nome_do_save[tam_nome-3] != 't' || nome_do_save[tam_nome-4] != '.')
    {
        printError("\nFormato de nome de save inválido! O nome do save deve ser no formato \"nome_do_save.txt\".\n");
        return;
    }

    time_t tempo_fim = time(NULL);
    jogador->tempo = tempo_fim - tempo_ini;

    // String que conterá o nome do save do jogador
    char caminho_save[MAX_STRING] = CAMINHO_SAVES; 
    
    // Concatenando o caminho do save com o nome do save
    strcat(caminho_save, nome_do_save);

    int contadorManter = 0, contadorRemover = 0;

    // ========== Salvando o jogo em um arquivo de texto ========== //

    FILE *save = fopen(caminho_save, "w"); 

    // Tamanho do tabuleiro que o jogador escolheu
    fprintf(save, "%d\n", jogador->tamanho); 

    // Números gerados para o jogador naquela partida
    for(int i = 0; i < tabuleiro->tamanho; i++) 
    {
        for(int j = 0; j < tabuleiro->tamanho; j++)
            fprintf(save, "%d ", tabuleiro->tabela_numeros[i][j]);
        fprintf(save, "\n");
    }

    // Soma das linhas do tabuleiro
    for(int i = 0; i < tabuleiro->tamanho; i++) 
        fprintf(save, "%d ", tabuleiro->somaLinhasTabela[i]);
    fprintf(save, "\n");

    // Soma das colunas do tabuleiro
    for(int i = 0; i < tabuleiro->tamanho; i++) 
        fprintf(save, "%d ", tabuleiro->somaColunasTabela[i]);
    fprintf(save, "\n");

    // Contando quantos elementos o jogador manteve e removeu
    for(int i = 0; i < tabuleiro->tamanho; i++) 
    {
        for(int j = 0; j < tabuleiro->tamanho; j++)
        {
            if(tabuleiro->tabela_usuario[i][j] == 2)
                contadorManter++;
            else if(tabuleiro->tabela_usuario[i][j] == 0)
                contadorRemover++;
        }
    }

    // Numero de vezes que o jogador usou o comando manter
    fprintf(save, "%d\n", contadorManter); 

    // Numeros que o jogador escolheu manter
    for(int i = 0; i < tabuleiro->tamanho; i++) 
    {
        for(int j = 0; j < tabuleiro->tamanho; j++)
        if(tabuleiro->tabela_usuario[i][j] == 2)
            fprintf(save, "%d %d\n", i+1, j+1);
        
    }

    // Numero de vezes que o jogador usou o comando remover
    fprintf(save, "%d\n", contadorRemover); 

    // Elementos que o jogador esocolheu remover
    for(int i = 0; i < tabuleiro->tamanho; i++) 
    {
        for(int j = 0; j < tabuleiro->tamanho; j++)
        if(tabuleiro->tabela_usuario[i][j] == 0)
        {
            fprintf(save, "%d %d\n", i+1, j+1);
        }
    }

    // Nome do jogador
    fprintf(save, "%s\n", jogador->nome); 

    // Tempo gasto pelo jogador
    fprintf(save, "%ld\n", jogador->tempo); 

    // Dificuldade escolhida
    fprintf(save, "%c", tabuleiro->dificuldade); 

    // Fecha o arquivo
    fclose(save);

    // Imprime mensagem de sucesso
    printf(YELLOW("\nJogo salvo em %s como \"%s\"!\n\n"), CAMINHO_SAVES, nome_do_save);

    return;
}

void Remover(Tabuleiro_t *tabuleiro, char *elemento_removido, int *contadicas, int *acao)
{
    // Obtendo as posicoes de linha e coluna em inteiros
    int linha = (elemento_removido[0] - '0') - 1;
    int coluna = (elemento_removido[1] - '0') - 1;
    
    // Validacao se o elemento existe
    if(elemento_removido[2] != '\0' || linha+1 > tabuleiro->tamanho || linha+1 < 1 
        || coluna+1 > tabuleiro->tamanho || coluna+1 < 1)
    {
        printError("\nEsse elemento não existe! Remova um elemento váldo:\n");
        return;
    }

    // Se o elemento ja foi removido
    if(tabuleiro->tabela_usuario[linha][coluna] == 0)
    {
        ExibirTabuleiro(tabuleiro);
        printf(YELLOW("Esse elemento já foi removido!\n"));
        return;
    }

    // Atualizando a matriz do usuario, soma de linhas e colunas
    tabuleiro->tabela_usuario[linha][coluna] = 0;
    tabuleiro->somaLinhasUsuario[linha] -= tabuleiro->tabela_numeros[linha][coluna];
    tabuleiro->somaColunasUsuario[coluna] -= tabuleiro->tabela_numeros[linha][coluna];

    if(tabuleiro->tabela_usuario[linha][coluna] == 0 && tabuleiro->gabarito[linha][coluna] == 1)
        (*contadicas)--;
    
    // Confere se o jogador ganhou nessa jogada
    if(JogadorGanhou(tabuleiro) == false) 
    {
        ExibirTabuleiro(tabuleiro);
        *acao = 0;
        return;
    }
    // O jogador venceu, todos os elemtos mantidos serão imprimidos em verde
    else 
    {
        for(int i = 0; i < tabuleiro->tamanho; i++)
            for(int j = 0; j < tabuleiro->tamanho; j++)
            {
                if(tabuleiro->gabarito[i][j] == 1)
                    tabuleiro->tabela_usuario[i][j] = 2;
            }
        }

    ExibirTabuleiro(tabuleiro);
    return;
}

void Voltar(Tabuleiro_t *tabuleiro, int *acao)
{
    MenuVoltar();

    // Validação do comando
    while(scanf("%d", acao) == 0 || *acao < 0 || *acao > 4)
    {
        printError("\n\nComando inválido! Digite um número de 0 a 4: ");
        limpabuffer();
        
    }
    // Se a acao for imprimir o ranking
    if(*acao == 3)
    {
        printf("\n\n");
        ExibirRanking();
        ExibirTabuleiro(tabuleiro);
        printf("\n\n");
        return;
    }
    // Se a acao for voltar ao jogo
    else if(*acao == 4)
    {
        ExibirTabuleiro(tabuleiro);
        printf("\n");
        limpabuffer();
        return;
    }
    // Se a acao for sair do jogo ou começar novo jogo ou carregar jogo, desaloca o tabuleiro
    else{
        liberaTabuleiro(tabuleiro);
    }

    return;
}

void Manter(Tabuleiro_t *tabuleiro, char *elemento_mantido, int *contadicas)
{
    // Obtendo as posicoes de linha e coluna em inteiros
    int linha = (elemento_mantido[0] - '0') - 1; 
    int coluna = (elemento_mantido[1] - '0') - 1;

    // Mais uma validação de manter
    if(elemento_mantido[2] != '\0' || linha+1 > tabuleiro->tamanho || linha+1 < 1 || coluna+1 > tabuleiro->tamanho || coluna+1 < 1)
    {
        printError("\nEsse elemento não existe! Mantenha um elemento váldo.\n");
        return;
    }

    // Se o elemento ja foi mantido
    if(tabuleiro->tabela_usuario[linha][coluna] == 2)
    {
        ExibirTabuleiro(tabuleiro);
        printf(YELLOW("\nEsse elemento já foi mantido!\n"));
        return;
    }

    if(tabuleiro->tabela_usuario[linha][coluna] == 0)
    {
        tabuleiro->somaLinhasUsuario[linha] += tabuleiro->tabela_numeros[linha][coluna];
        tabuleiro->somaColunasUsuario[coluna] += tabuleiro->tabela_numeros[linha][coluna];
    }

    tabuleiro->tabela_usuario[linha][coluna] = 2;

    if(tabuleiro->tabela_usuario[linha][coluna] == 2 && tabuleiro->gabarito[linha][coluna] == 1)
        (*contadicas)++;

    ExibirTabuleiro(tabuleiro);
}
