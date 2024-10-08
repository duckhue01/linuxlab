#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

// Write a program that opens an existing file for writing with the O_APPEND flag, and
// then seeks to the beginning of the file before writing some data. Where does the
// data appear in the file? Why?

int main(char *argv[], int argc)
{
  int fd = open("text", O_APPEND | O_WRONLY);
  if (fd == -1)
  {
    perror("open");
    _exit(1);
  }

  char str[] = "this is content";

  off_t of = lseek(fd, 0, SEEK_SET);
  if (of == -1)
  {
    perror("lseek");
    _exit(1);
  }

  int c = write(fd, str, sizeof(str) -1);
  if (c == -1)
  {
    perror("write");
    _exit(1);
  }

  return 0;
}