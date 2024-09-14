#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

// The tee command reads its standard input until end-of-file, writing a copy of the input to standard output and to the file named in its command-line argument. (We show an example of the use of this command when we discuss FIFOs in Section 44.7.)

// Implement tee using I/O system calls. By default, tee overwrites any existing file with the given name.

// Implement the –a command-line option (tee –a file), which causes tee to append text to the end of a file if it already exists. (Refer to Appendix B for a description of the getopt() function, which can be used to parse command-line options.)

#define MAX_READ 5
#define EXIT_FAILURE 1 /* Failing exit status.  */
#define EXIT_SUCCESS 0 /* Successful exit status.  */

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("error: usage tee output");
  }

  char buf[MAX_READ];
  if (read(STDIN_FILENO, &buf, MAX_READ) == -1)
  {
    printf("error reading stdin");
    exit(EXIT_FAILURE);
  }

  int openFlags = O_CREAT | O_WRONLY | O_APPEND;
  mode_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw- */

  int fd = open(argv[1], openFlags, filePerms);

  if (fd == -1)
    printf("error open file");

  if (write(fd, &buf, MAX_READ) == -1)
  {
    printf("error writing to file\n");
    exit(EXIT_FAILURE);
  }

  if (close(fd) == -1)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}