# Compilador e flags
CC = gcc
CFLAGS = -g -Wall -Wextra -O2 -Isrc/include

# Diretórios fonte e binario
DIR_FONTE = src
DIR_BIN   = bin

# Arquivos fonte e alvo
FONTE = $(DIR_FONTE)/*.c
EXECUTAVEL = $(DIR_BIN)/tp.exe


# ============== Regras para compilar e executar o projeto ==============
compile: $(EXECUTAVEL)

$(EXECUTAVEL): $(FONTE)
	@mkdir -p $(DIR_BIN)
	$(CC) $(CFLAGS) $(FONTE) -o $@ -lm

run: $(EXECUTAVEL)
	@./$(EXECUTAVEL) 

runval:
	@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(EXECUTAVEL)

clean:
	@rm -f $(EXECUTAVEL)
