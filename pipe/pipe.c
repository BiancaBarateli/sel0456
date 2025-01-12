
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Read characters from the pipe and echo them to stdout. */

void
read_from_pipe (int file) {
  FILE *stream;
  int c;
  printf("Child reading from pipe\n");
  stream = fdopen(file, "r");
  while ((c = fgetc(stream)) != EOF)
    putchar(c);
  fclose(stream);
}

/* Write some random text to the pipe. */

void write_to_pipe (int file) {
  FILE *stream;
  stream = fdopen (file, "w");
  fprintf(stream, "hello, world!\n");
  fprintf(stream, "goodbye, world!\n");
  fclose(stream);
}

int main (void) {
  pid_t pid;
  int mypipe[2];

  /* Create the pipe. */
  if (pipe(mypipe)) {
      fprintf (stderr, "Pipe failed.\n");
      return EXIT_FAILURE;
    }

  /* Create the child process. */
  pid = fork(); // pipe é bom quando tem processo escrito por fork
  if (pid == (pid_t) 0) {
      /* This is the child process.
         Close other end first. */
      close(mypipe[1]);
      pid = getpid();
      printf("My child pid=%d\n", pid);
      read_from_pipe(mypipe[0]);
      return EXIT_SUCCESS;
  }
  else if (pid < (pid_t) 0) {
      /* The fork failed. */
      fprintf (stderr, "Fork failed.\n");
      return EXIT_FAILURE;
    }
  else {
    /* This is the parent process.
       Close other end first. */
    close(mypipe[0]);
    printf("Parent pid=%d\n", getpid());
    printf("Child pid=%d\n", pid);
    printf("Waiting 5 seconds to write to pipe\n");
    sleep(5);
    write_to_pipe(mypipe[1]);
    return EXIT_SUCCESS;
  }
}
