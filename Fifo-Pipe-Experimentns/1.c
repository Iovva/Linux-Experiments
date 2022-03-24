#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>      
#include <fcntl.h>


int main(int argc, char** argv)
{
  // Procesul A
  int nr;
  if(argc < 2)
  {
    perror("Nu sunt destule argumente!\n");
    return 2;
  }
  if(mkfifo(argv[1], 0600) < 0)
  {
    perror("Nu s-a putut crea fisierul fifo!\n");
    return 2;
  }
  int f = open(argv[1], O_WRONLY);
  if(f < 0)
  {
    perror("Nu s-a putut deschide fisierul fifo!\n");
    return 2;
  }
  char file_name[30];
  scanf("%s", file_name);
  FILE* file = fopen(file_name, "r");
  while(fscanf(file, "%d", &nr) > 0)
  {
    write(f, &nr, sizeof(int));
  }
  close(f);
  fclose(file);
  return 0;
}
