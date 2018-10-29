#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int randgen() {
  int fd = open("/dev/random", O_RDONLY);
  if (fd < 0)
    printf("Errno %d: %s\n", errno, strerror(errno));
  int randnum;
  read(fd, &randnum, sizeof(int));
  close(fd);
  return randnum;
}

int main() {
  int randarr[10];
  
  printf("Generating random numbers:\n");
  for(int i = 0; i < 10; i++) {
    randarr[i] = randgen();
    printf("Random number %d: %d\n", i, randarr[i]);
  }
  
  int out = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
  if (out < 0)
    printf("Errno %d: %s\n", errno, strerror(errno));
  printf("\nWriting numbers to file...\n" );
  write(out, randarr, 10 * sizeof(int));
  close(out);

  printf("\nReading numbers from file...\n" );
  int arr2[10];
  int in = open("file.txt", O_RDONLY, 0777);
  if (in < 0)
    printf("Errno %d: %s\n", errno, strerror(errno));
  read(in, &arr2, 10 * sizeof(int));
  close(in);

  printf("\nVerification that written values were the same:\n");
  for(int i = 0; i < 10; i++)
    printf("Random number %d: %d\n", i, arr2[i]);

  return 0;
}
