#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){

int n, a2b[2], b2c[2], c2a[2];
pipe(a2b); pipe(b2c); pipe(c2a);

//A
if (fork() == 0){
	close(a2b[0]); close(b2c[0]); close(b2c[1]); close(c2a[1]);	
	while(1){
		if (read(c2a[0], &n, sizeof(int)) <= 0)
			break;
		if (n <= 0)
                        break;
		printf("A: %d -> %d\n", n, n - 1);
		n--;
		write(a2b[1], &n, sizeof(int));
	}
close(c2a[0]);close(a2b[1]);
exit(0);
}

//B
if (fork() == 0){
        close(a2b[1]); close(b2c[0]); close(c2a[0]); close(c2a[1]);
        while(1){
                if (read(a2b[0], &n, sizeof(int)) <= 0)
                        break;
                if (n <= 0)
                        break;
		printf("B: %d -> %d\n", n, n - 1);
 		n--;
                write(b2c[1], &n, sizeof(int));
        }
close(a2b[0]);close(b2c[1]);
exit(0);
}


close(a2b[0]), close(a2b[1]), close(b2c[1]), close(c2a[0]);
n = 20;
write(c2a[1], &n, sizeof(int)); 
//C
while(1){
	if (read(b2c[0], &n, sizeof(int)) <= 0)
		break;
	if (n <= 0)
                break;
	printf("C: %d -> %d\n", n, n - 1);
	n--;
	write(c2a[1], &n, sizeof(int));
}
close(b2c[0]);close(c2a[1]);
wait(0);wait(0);
return 0;
}
