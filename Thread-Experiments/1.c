#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int n = 0;

void* f(void *a) {
	int i;
	printf("%d", *(int*)a);  
	return NULL;
}

int main(int argc, char** argv){
	int i;
	pthread_t t[100];

	for (i = 0; i < 100; i++){
		pthread_create(&t[i], NULL, f, NULL);
	}
	for (i = 0; i < 100; i++){
		pthread_join(t[i], NULL);
}
printf("%d\n", n);
return 0;
}
