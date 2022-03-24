#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

pthread_mutex_t mut;
int v[10];

typedef struct{
        int nr;
        char* file_name;
}*p, P;

void* f(void* a){
        p pereche = (p)a;
        if (pereche->nr < 0 || pereche->nr > 9){
                free(pereche);
                return NULL;
        }
        FILE* file_name = fopen(pereche->file_name, "r");
        if (file_name == NULL){
                free(pereche);
                return NULL;
        }
        int c = 0;
        char line[1000];
        while (fgets(line, sizeof(line), file_name)){
                int i;
                for (i = 0; i < strlen(line); i++){
                        if (line[i] >= 'A' && line[i] <= 'Z'){
                                c++;
                        }
                }
        }
        pthread_mutex_lock(&mut);
        v[pereche->nr] += c;
        pthread_mutex_unlock(&mut);
        fclose(file_name);
        free(pereche);
        return NULL;
}

int main(int argc, char** argv){
        if (argc % 2 == 0 || argc == 1)
                return 1;
        pthread_mutex_init(&mut, NULL);
	 int i = 0;
        pthread_t t[(argc-1)/2];
        for (i = 0; i < (argc - 1)/2; i++){
                p pereche = malloc(sizeof(P));
                pereche->file_name = argv[2*i+1];
                pereche->nr = atoi(argv[2*i+2]);
                pthread_create(&t[i], NULL, f, (void*)pereche);
        }

        for (i = 0; i < (argc - 1)/2; i++)
                pthread_join(t[i], NULL);
        pthread_mutex_destroy(&mut);
        for (i = 0; i < 10; i++){
                printf("%d\n", v[i]);
        }
        return 0;
}
                               


