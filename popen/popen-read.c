#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define SSIZE 1024

int main (void) {
  FILE *in;
  size_t n = SSIZE;
  char * s = malloc(n); // aloca dinamicamente no heap e não no stack (cria de cima pra baixo)
  int r;

  in = popen("ls -la", "r"); // r: read
  if (!in) {
    fprintf (stderr, "incorrect parameters or too many files.\n");
    return EXIT_FAILURE;
  }
  while ((r = getline(&s, &n, in)) > 0) { // essa função lê uma linha até o \n
    printf("%s", s);
  }
  free(s); // não precisaria dar um free no s
  return EXIT_SUCCESS;
}
