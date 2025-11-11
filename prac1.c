#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


#define chairs 3
#define student 2

sem_t st,ta;
pthread_mutex_t mutex;
int waiting=0;

void *s(void *args)
{
    int id=*(int*)args;
    while(1)
    {
        sleep(rand()%5+1);
        pthread_mutex_lock(&mutex);
        if(waiting<chairs)
        {
            waiting++;
            printf("students %d are waiting %d\n",id,waiting);
            sem_post(&st);
            pthread_mutex_unlock(&mutex);
            sem_post(&ta);
            printf("student %d getting help\n",id);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            printf("no chairs getting help\n",id);
        }
    }

}



void *t(void *args)
{
    while(1)
    {
       
        
            sem_wait(&st);
            pthread_mutex_lock(&mutex);
            waiting--;
            printf("ta helping %d\n",waiting);
            pthread_mutex_unlock(&mutex);
            sem_post(&ta);

            sleep(rand()%3+1);
            printf("done\n");
        }
}


int main()
{
    srand(time(NULL));
    pthread_t ss[student],tt;
    int id[student];

    sem_init(&st,0,0);
    sem_init(&t,0,0);
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&tt,NULL,t,NULL);

    for(int i=0;i<student;i++)
    {
        id[i]=i+1;

        pthread_create(&ss[i],NULL,s,&id[i]);
    }
    
    pthread_join(tt,NULL);
for(int i=0;i<student;i++)
    {

     pthread_join(ss[i],NULL);
    }

    sem_destroy(&st);
    sem_destroy(&t);
    pthread_mutex_destroy(&mutex);



}