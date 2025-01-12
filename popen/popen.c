#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void
write_data (FILE * stream)
{
  int i;
  for (i = 0; i < 100; i++)
    fprintf (stream, "%d\n", i); // o programa criou uma string e é o standard input do less
  if (ferror (stream))
    {
      fprintf (stderr, "Output to stream failed.\n");
      exit (EXIT_FAILURE);
    }
}

int
main (void)
{
  FILE *output;
  /* exemplo de gravação em arquivo por stream (FILE) */
  output = fopen("texto.txt", "w");
  fprintf(output, "teste blablabla\n");
  printf("file descriptor output = %d\n", fileno(output));
  printf("stdin=%d, stdout=%d, stderr=%d\n", fileno(stdin), fileno(stdout), fileno(stderr));

  /* exemplo de gravação em arquivo por file descriptor -> mais baixo nível */
  int fd;
  fd = open("texto2.txt", O_CREAT | O_WRONLY, 0666);
  printf("file descriptor fd = %d\n", fd);
  char *s = "bla bla bla bla \nbla bla bla";
  write(fd, s, strlen(s));
  close(fd);

  fclose(output);

  output = popen ("less", "w");
  if (!output)
    {
      fprintf (stderr,
               "incorrect parameters or too many files.\n");
      return EXIT_FAILURE;
    }
  write_data (output);
  if (pclose (output) != 0)
    {
      fprintf (stderr,
               "Could not run more or other error.\n");
    }
  return EXIT_SUCCESS;
}

