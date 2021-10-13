#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// o programa escreve ou manda uma mensagem para outro programa
// gnuplot é um programa que plota funções

void
write_data (FILE * stream)
{
  fprintf(stream, "plot [0:2*pi] sin(x)\n");
  if (ferror (stream))
    {
      fprintf (stderr, "Output to stream failed.\n");
      exit (EXIT_FAILURE);
    }
}

int
main (void)
{
  FILE *output; // FILE é um string de dados

  output = popen ("gnuplot --persist", "w");
  if (!output)
    {
      fprintf (stderr,
               "incorrect parameters or too many files.\n");
      return EXIT_FAILURE;
    }
  write_data (output); // linka o string output com o standard input do gnuplot
  if (pclose (output) != 0)
    {
      fprintf (stderr,
               "Could not run more or other error.\n");
    }
  return EXIT_SUCCESS;
}
