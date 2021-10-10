# ARQUIVO MAKEFILE
# É um arquivo de "receitas" de como compilar o programa
# Ele pode ter os targets ou regras alvos e podemos setar variáveis globais

# 1ª OPÇÃO:
#all:
#	gcc -Os main.c sqr.c -o main

# 2ª OPÇÃO: usando variáveis de compilação e linkagem
DEFFLAGS = $(patsubst %, -D%, OPTION1 OPTION2 OPTION3)
# define uma variável que chama a função patsubst
CFLAGS = -O2 -g $(DEFFLAGS) # CFLAGS são variáveis de compilação
# -Os: otimização em tamanho do código
# -02: otimização mais em tamanho do código e tempo de execução
# -g: p/ fazer depuração, colocar códigos de debug
# -DOPTION2: define OPTION2
LDFLAGS = -lm -lpthread # LDFLAGS são variáveis de linkagem
# -lm: libnet
GCC = gcc
ALL = main

all: $(ALL)
#main: main.c sqr.c	mult_acc.c

# dependências do target main
main: main.o sqr.o mult_acc.o # assim fica mais otimizado
	$(GCC) -o $@ $^ $(LDFLAGS)

# $() pra pegar o valor da variável
# $\^ todas as dependências
# $\@ é o nome do target
%.s: %.c # qualquer arquivo .s dependente do arquivo .c de mesmo nome
	$(GCC) $(CFLAGS) -S $<

clean:
	rm -f *.o *.s a.out
# para apagar todos os arquivos .o e .s e o executável a.out

distclean: clean # o distclean faz o clean primeiro
	rm -r $(ALL) # limpeza completa no diretório

# OBS. 1: QUANDO DÁ O COMANDO MAKE NO TERMINAL, ELE SEMPRE EXECUTA O PRIMEIRO TARGET (all, nesse caso)
# OBS. 2: POR CAUSA DA LINKAGEM DOS CÓDIGOS-FONTE, SÓ VÃO SER COMPILADOS OS CÓDIGOS QUE FOREM ALTERADOS
# OBS. 3: SE SÓ O MAKEFILE FOR ALTERADO, ELE NÃO VAI COMPILAR, PORQUE OS CÓDIGOS DE DEPENDÊNCIAS NÃO ESTÃO MODIFICADOS


