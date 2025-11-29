#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int idx;
    int *potato;
    pthread_mutex_t *mtx;

} data;

pthread_barrier_t barrier;
pthread_cond_t cond_reset, cond_play;
int ready_for_reset = 0, ready_for_playing = 1;
int potato, players_alive;

void *f(void *arg) {
    data *d = (data*) arg;
    pthread_barrier_wait(&barrier);
    while(1) {
        pthread_mutex_lock(d->mtx);
        while(!ready_for_playing){
            pthread_cond_wait(&cond_play, d->mtx);
        }

        if (players_alive == 1){
            printf("Thread %d is the winner!\n", d->idx);
            pthread_mutex_unlock(d->mtx);
            break;
        }

        int sub = rand() % 91 + 1000;
        printf("Thread with id %d has subtracted %d from %d\n", d->idx, sub, *(d->potato));

        *(d->potato) -= sub;
        if(*(d->potato) < 0) {
            printf("Thread with id %d has exploded!\n", d->idx);

            ready_for_reset = 1;
            ready_for_playing = 0;
            pthread_cond_signal(&cond_reset);
            pthread_mutex_unlock(d->mtx);
            break;
        }

        pthread_mutex_unlock(d->mtx);
        int sleep = rand() % 101 + 100;
        usleep(sleep * 1000);
    }

    return NULL;

}

void *monitor(void* arg) {
    data *d = (data*) arg;
    pthread_barrier_wait(&barrier);
    while(1){
        pthread_mutex_lock(d->mtx);
        while(!ready_for_reset){
            pthread_cond_wait(&cond_reset, d->mtx);
        }

        potato = rand() % 9001 + 1000;
        --players_alive;
        ready_for_playing = 1;
        ready_for_reset = 0;
        pthread_cond_broadcast(&cond_play);

        if(players_alive == 1){
            break;
        }

         pthread_mutex_unlock(d->mtx);
    }

    pthread_mutex_unlock(d->mtx);
    return NULL;
}

int main(int argc, char *argv[]){

    if(argc != 2) {
        perror("Please provide exactly one argument!\n");
        exit(0);
    }

    int n = atoi(argv[1]);
    srand(getpid());
    potato = rand() % 9001 + 1000;
    printf("Main has generated %d\n", potato);
    players_alive = n;

    pthread_t th[n+1];

    data *args = malloc(sizeof(data) * (n+1));
    pthread_mutex_t mtx;
    pthread_mutex_init(&mtx, NULL);
    
    pthread_barrier_init(&barrier, NULL, n+1);
    pthread_cond_init(&cond_reset, NULL);
    pthread_cond_init(&cond_play, NULL);

    for(int i = 0; i < n+1; i++) {
        args[i].idx = i + 1;
        args[i].potato = &potato;
        args[i].mtx = &mtx;

        if(i == n) {
            pthread_create(&th[i], NULL, monitor, (void *) &args[i]);
        } else {
            pthread_create(&th[i], NULL, f, (void *) &args[i]);
        }
    }

    for(int i = 0; i < n+1; i++) {
        pthread_join(th[i], NULL);
    }

    pthread_mutex_destroy(&mtx);
    pthread_barrier_destroy(&barrier);
    pthread_cond_destroy(&cond_reset);
    pthread_cond_destroy(&cond_play);
    free(args);
    return 0;
}
