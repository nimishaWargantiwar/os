#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define FILE_NAME "shared_buffer.txt"

pthread_mutex_t mutex;
sem_t dataReady;   // Signals producer has written
sem_t spaceReady;  // Signals consumer has read

void* producer(void* arg) {
    FILE* fp;
    int value;

    while (1) {
        value = rand() % 10; // Produce 0–9

        sem_wait(&spaceReady); // Wait until buffer/file is empty
        pthread_mutex_lock(&mutex);

        fp = fopen(FILE_NAME, "w");
        if (fp == NULL) { perror("fopen"); exit(1); }
        fprintf(fp, "%d\n", value);
        fclose(fp);

        printf("Producer: Produced %d\n", value);

        pthread_mutex_unlock(&mutex);
        sem_post(&dataReady); // Signal consumer

       usleep((rand() % 101) * 1000); // 0–100ms
    }
    return NULL;
}

void* consumer(void* arg) {
    FILE* fp;
    int value;

    while (1) {
        sem_wait(&dataReady); // Wait for producer
        pthread_mutex_lock(&mutex);

        fp = fopen(FILE_NAME, "r");
        if (fp == NULL) { perror("fopen"); exit(1); }
        fscanf(fp, "%d", &value);
        fclose(fp);

        printf("Consumer: Consumed %d\n", value);

        // Clear file (simulate consuming the buffer)
        fp = fopen(FILE_NAME, "w");
        fclose(fp);

        pthread_mutex_unlock(&mutex);
        sem_post(&spaceReady); // Signal producer

        usleep(50000); // 50ms
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t prod, cons;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&dataReady, 0, 0);
    sem_init(&spaceReady, 0, 1);

    // Clear file initially
    FILE* fp = fopen(FILE_NAME, "w");
    fclose(fp);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);
    // sem_destroy() warnings on MacOS can be ignored

    return 0;
}
