  #include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];

void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        // Pick right fork
        sem_wait(&forks[(id + 1) % N]);
        printf("Philosopher %d picked up right fork %d.\n", id, (id + 1) % N);

        // Pick left fork
        sem_wait(&forks[id]);
        printf("Philosopher %d picked up left fork %d.\n", id, id);

        // Eat
        printf("Philosopher %d is eating.\n", id);
        sleep(2);

        // Put down forks
        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);
        printf("Philosopher %d put down forks %d and %d.\n", id, id, (id + 1) % N);
    }
}

int main() {
    pthread_t thread_id[N];
    int phil[N];

    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < N; i++) {
        phil[i] = i;
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }

    return 0;
}
