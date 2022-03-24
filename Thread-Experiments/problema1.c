#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t mut;
int nr_cifre = 0;

typedef struct{
	int nr; // poz in vector
	int n;	
	char* file_name;
	int* v; // vectorul
}*s, S;

void* f (void* a){
	s strct = (s)a;
	FILE* file_name = fopen(strct->file_name, "r");
	if (file_name == NULL){
		free(strct);
		return NULL;
}
	int count_litere = 0, count_cifre = 0;
	int n = 0;
	char line[1024];
	while (fgets(line, sizeof(line), file_name)){
		int i;
		for (i = 0; i < strlen(line); i++){
			n++;
			if (line[i] >= 'A' && line[i] <= 'Z')
				count_litere++;
			if (line[i] >= '0' && line[i] <= '9' && n - 1 < strct->n)
				count_cifre++;
		}
		n--;
	}
	pthread_mutex_lock(&mut);
	strct->v[strct->nr] += count_litere;
	pthread_mutex_unlock(&mut);

	pthread_mutex_lock(&mut);
	nr_cifre += count_cifre;
	pthread_mutex_unlock(&mut);
	fclose(file_name);
	free(strct);
	return NULL;
}

int main(int argc, char** argv){

	if (argc % 2 == 0 || argc == 1)
		printf("Numar invalid de parametrii!\n");
	pthread_mutex_init(&mut, NULL);
	pthread_t t[(argc-1) / 2];
	int i;
	int* v;
	v = malloc((argc / 2) * sizeof(int));
	for (i = 0; i < (argc - 1) / 2; i++){
		s strct = malloc(sizeof(S));
		strct->file_name = argv[2 * i + 1];
		strct->n = atoi(argv[2 * i + 2]);
		strct->nr = i;
		strct->v = v;
		pthread_create(&t[i], NULL, f,(void*)strct);
	}
	for (i = 0; i < (argc - 1)/2; i++){
		pthread_join(t[i], NULL);	
	}
	for (i = 0; i < (argc - 1) / 2; i++){
		printf("Fisierul %d are %d majuscule\n", i + 1, v[i]);
	}
	printf("Sunt %d cifre\n.", nr_cifre);	 
	pthread_mutex_destroy(&mut);	
	free(v);
	return 0;
}
