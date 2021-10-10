// Função multiplicador acumulador
#include "mult_acc.h"
static int x = 2; // cria essa variável x localmente nesse módulo; fica disponível somente dentro desse módulo, de modo que o mesmo nome da variável pode ser utilizado em outros módulos sem influenciar nesse valor
//int x;

void mult_set_x(int _x) { // função setter; vai atribuir um novo valor pra x toda vez que chamar essa função em outro módulo
  x = _x;
}

int mult_acc(int y) {
  //  x += x * y;
  static int z = 2; // só na 1ª vez que chamar a função que o z será 2
  char a[512]; // criou uma variável 'a' temporária no stack pointer de 512 bytes
  x += z + x * y;
  z += x;
  return x;
}

