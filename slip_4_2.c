#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CHAIRS 3
#define NUM_STUDENTS 5

sem_t studentsSem;   // Students waiting
sem_t taSem;         // TA ready
pthread_mutex_t mutex;

int waiting = 0;     // Waiting students

void* student(void* arg) {
    int id = *(int*)arg;
    while (1) {
        sleep(rand() % 5 + 1); // Student programming

        pthread_mutex_lock(&mutex);
        if (waiting < NUM_CHAIRS) {
            waiting++;
            printf("Student %d is waiting. Waiting = %d\n", id, waiting);
            sem_post(&studentsSem); // Notify TA
            pthread_mutex_unlock(&mutex);

            sem_wait(&taSem);       // Wait for TA
            printf("Student %d is getting help from TA.\n", id);
        } else {
            pthread_mutex_unlock(&mutex);
            printf("No chair free. Student %d will come back later.\n", id);
        }
    }
    return NULL;
}

void* ta(void* arg) {
    while (1) {
        sem_wait(&studentsSem);   // Wait for a student

        pthread_mutex_lock(&mutex);
        waiting--;
        printf("TA is helping a student. Remaining = %d\n", waiting);
        pthread_mutex_unlock(&mutex);

        sem_post(&taSem);         // Let one student get help

        printf("TA is helping...\n");
        sleep(rand() % 3 + 1);    // Simulate help time
        printf("TA finished helping.\n");
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t taThread, studentThreads[NUM_STUDENTS];
    int ids[NUM_STUDENTS];

    sem_init(&studentsSem, 0, 0);
    sem_init(&taSem, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&taThread, NULL, ta, NULL);

    for (int i = 0; i < NUM_STUDENTS; i++) {
        ids[i] = i + 1;
        pthread_create(&studentThreads[i], NULL, student, &ids[i]);
    }

    pthread_join(taThread, NULL);
    for (int i = 0; i < NUM_STUDENTS; i++)
        pthread_join(studentThreads[i], NULL);

    sem_destroy(&studentsSem);
    sem_destroy(&taSem);
    pthread_mutex_destroy(&mutex);

    return 0;
}
