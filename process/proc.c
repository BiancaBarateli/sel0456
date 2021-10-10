// Processo é um programa novo, totalmente independente de outros
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  pid_t p;
  printf("Criando o processo\n");
  if ((p = fork()) == 0) { // cria um novo processo espelho (duplica o programa a partir do comando fork; pra um deles ele retorna 0, que é o filho, e para o outro ele retorna o PID do filho, que é o pai) pelo código de retorno ao invés do argumento
    printf("Processo filho\n");
    execl("/usr/bin/ls", "ls", NULL); // A função exec substitui o processo atual por um novo, nesse caso, o processo filho criado pelo fork() é substituído pelo processo ls, mas ele não volta mais para o processo pai de novo; o último argumento é sempre NULL
  }
  else { 
    printf("Processo pai e o PID do filho é: %d\n", p); // PID é um identificador que o sist. operacional usa p/ cada processo
    sleep(20); // o processo filho vai acabar primeiro e vai virar um "defunto"
  }  
  return 0; 
}

/* A thread fica dentro de um processo, ela duplica as variáveis globais. O processo não, ele é um outro programa */

