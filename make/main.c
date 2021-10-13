#include <stdlib.h> // essas bibliotecas são arquivos do sistema
#include <stdio.h>
#include <pthread.h> // biblioteca para usar thread (rodar partes em paralelo)
#include <unistd.h> // para usar o sleep
#include <semaphore.h> // para usar semáforo
#include "sqr.h" // entre aspas porque tá no diretório local e não é um arquivo de sistema; inclui a declaração da função sqr
#include "mult_acc.h"

//#define OPTION2 # opção para definir a variável OPTION2
double x = 9; // não tem nada a ver com o x da função mult_acc
sem_t sem; // global pra ser visível dentro da thread

void * conta_a_toa(void * ptr) { // thread (sempre recebe e sempre retorna um ponteiro universal --> void)
  //register int j;
  int n = *(int *)ptr; // tem que converter para um ponteiro de inteiro
  //volatile unsigned int i;
  printf("Na thread nº %d\n", n);
  //for(i = 0; i < 0xffffffff; i++);
  sleep(3);
  sem_wait(&sem); // vai esperar se alguma thread estiver usando semáforo
  printf("Thread nº %d entrando en código crítico\n", n); // -> ninguém pode entrar aqui para evitar incoerências já que a thread vai estar alterando uma porção da memória que outras threads também têm acesso
  sleep(1);
  /* acessando recursos exclusivos (só uma pode acessar de cada vez aqui) */ 
  printf("Saindo do código crítico e finalizando a thread nº %d\n", n);
  sem_post(&sem);
  pthread_exit(NULL); // pra caso queira que a thread retorne algo (nesse caso não precisaria porque não está retornando nada)

  return NULL;
}

int main(void) {

  //register int j; // faz o compilador alocar essa variável num registrador da máquina p/ ficar mais rápido o processamento (não é muito utilizado hoje)
  double y;
  int z;

  pthread_t thr1, thr2, thr3; // descritores de thread
  sem_init(&sem, 0, 1); // inicializar o semáforo
  // 0 porque o processo é único e não shared
  // 1 --> valor inicial; só uma tarefa ou thread pode entrar no código crítico por vez

// Compilação condicional: -> compilar de um jeito ou de outro sem ficar alterando o código
#ifdef OPTION2
  y = 2;
#else
  y = 1.4142;
#endif

  // para cada thread criada, cria-se um novo stack, enquanto que o heap e o static data são compartilhados pelas threads
  int n1 = 1;
  int r = pthread_create(&thr1, NULL, conta_a_toa, &n1); // cria a pthread
  if (r == 0) { // se r for zero é porque deu certo
    printf("Ok criando a thread nº %d\n", n1);
  }
  else {
    perror("criando a thread");
    exit(1);
  }

  int n2 = 2;
  r = pthread_create(&thr2, NULL, conta_a_toa, &n2); // cria a pthread
  if (r == 0) { // se r for zero é porque deu certo
    printf("Ok criando a thread nº %d\n", n2);
  }
  else {
    perror("criando a thread");
    exit(1);
  }

  int n3 = 3;
  r = pthread_create(&thr3, NULL, conta_a_toa, &n3); // cria a pthread
  if (r == 0) { // se r for zero é porque deu certo
    printf("Ok criando a thread nº %d\n", n3);
  }
  else {
    perror("criando a thread");
    exit(1);
  }

  printf("O quadrado de %g é %g!\n", y, sqr(y));
  // Inicializar x no módulo mult_acc:
  //x = 1;
  mult_set_x(1);
  z = mult_acc(2);
  printf("mult_acc = %d\n", z);
  z = mult_acc(4);
  printf("mult_acc = %d\n", z);

  //volatile unsigned int i; // i está como unsigned para demorar mais no loop; volatile é muito usado em sistemas embarcados para registradores; são variáveis modificadas externamente ao programa (algum outro processo pode settar esse i); então o compilador não vai otimizar o loop abaixo; ele é o oposto do register -> não deixa o compilador armazenar a variável no registrador
  //for(i = 0; i < 0xffffffff; i++); 
  sleep(2); // faz a mesma coisa que o loop acima, mas consumindo menos processamento; o sleep é uma chamada de sistema que "fala" para o sistema operacional bloquear esse processo e só voltar a executá-lo daqui a 10 segundos

  printf("conta finalizou na main\n");

  pthread_join(thr1, NULL);
  pthread_join(thr2, NULL);
  pthread_join(thr3, NULL); // para juntar de volta a thread no programa principal, porque senão quando acabar o processo na main, ele vai interromper todos os outros --> mas se tiver certeza que a thread vai acabar antes da main, aí nem precisaria dessa função

  return 0;
}
