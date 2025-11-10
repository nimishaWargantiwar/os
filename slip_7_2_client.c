#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

#define SHM_SIZE 1024
#define SEM_NAME "/mysem"

int main() {
    int shmid = shmget(ftok(".", 'B'), SHM_SIZE, 0666);
    char *shm = (char*) shmat(shmid, NULL, 0);

    // open named semaphore
    sem_t *s = sem_open(SEM_NAME, 0);

    while (1) {
        sem_wait(s); // wait for server

        printf("Client read: %s\n", shm);
        if (strcmp(shm, "exit") == 0) break;
    }

    // shmdt(shm);
    // sem_close(sem);

    return 0;
}
