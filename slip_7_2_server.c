#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

#define SHM_SIZE 1024
#define SEM "/mysem"

int main() {
    // create shared memory
    int shmid = shmget(ftok(".", 'B'), SHM_SIZE, 0666 | IPC_CREAT);
    char *shm = (char*) shmat(shmid, NULL, 0);

    // create named semaphore
    sem_t *s = sem_open(SEM, O_CREAT, 0644, 0);

    while(1) {
        printf("Server: ");
        fgets(shm, SHM_SIZE, stdin);
        shm[strcspn(shm, "\n")] = 0; // remove newline

        sem_post(s);  // signal client

        if(strcmp(shm,"exit")==0) break;
    }

    // // cleanup
    // shmdt(shm);
    // shmctl(shmid, IPC_RMID, NULL);
    // sem_close(s);  
    // sem_unlink(SEM);

    return 0;
}
