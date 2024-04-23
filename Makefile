all: jogo.o auxiliares.o main.o tabuleiro.o comandos.o
	@gcc main.o auxiliares.o tabuleiro.o jogo.o comandos.o -g -Wall -o exe
	@rm main.o auxiliares.o tabuleiro.o jogo.o
main.o: main.c
	@gcc main.c -c
auxiliares.o: auxiliares.c
	@gcc auxiliares.c -c
tabuleiro.o: tabuleiro.c
	@gcc tabuleiro.c -c
jogo.o: jogo.c
	@gcc jogo.c -c
comandos.o: comandos.c
	@gcc comandos.c -c
run:
	@./exe
