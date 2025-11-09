#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define READERS 5
#define WRITERS 2

int data = 100;           // Shared resource
int readCount = 0;        

pthread_mutex_t mutex;    // Protect readCount
sem_t db;                 // Controls access to shared data

void* reader(void* arg) {
    int id = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&mutex);
        readCount++;
        if (readCount == 1) sem_wait(&db); // First reader locks db
        pthread_mutex_unlock(&mutex);

        printf("Reader %d reads data = %d\n", id, data);

        pthread_mutex_lock(&mutex);
        readCount--;
        if (readCount == 0) sem_post(&db); // Last reader unlocks db
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    while (1) {
        sem_wait(&db);
        data += 10;
        printf("Writer %d updates data = %d\n", id, data);
        sem_post(&db);
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t r[READERS], w[WRITERS];
    int idsR[READERS], idsW[WRITERS];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&db, 0, 1);

    for (int i = 0; i < READERS; i++) {
        idsR[i] = i + 1;
        pthread_create(&r[i], NULL, reader, &idsR[i]);
    }

    for (int i = 0; i < WRITERS; i++) {
        idsW[i] = i + 1;
        pthread_create(&w[i], NULL, writer, &idsW[i]);
    }

    for (int i = 0; i < READERS; i++) pthread_join(r[i], NULL);
    for (int i = 0; i < WRITERS; i++) pthread_join(w[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&db);
    return 0;
}
