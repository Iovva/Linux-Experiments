#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char** argv)
{
  // Procesul B
  if(argc < 2)
  {
    perror("Nu sunt destule argumente!\n");
    return 2;
  }
  int p[2];
  pipe(p);

  if(fork() == 0)
  {
      close(p[0]);
      int s = 0, nr;
      int f = open(argv[1], O_RDONLY);
      while(read(f, &nr, sizeof(int)) >  0) {
       s+=nr;   
     }
	printf("%d\n", s);
     write(p[1], &s, sizeof(int));
     close(p[1]);
     exit(0);
  }
  if(fork() == 0)
  {
    close(p[1]);
    int nr, i;
    read(p[0], &nr, sizeof(int));
    for(i = 1; i <= nr; i++)
      if(nr%i == 0)
        printf("%d ", i);
    close(p[0]);
    exit(0);
  }
  close(p[0]); close(p[1]);
  wait(0);
  wait(0);
  unlink(argv[1]);
  return 0;
}
