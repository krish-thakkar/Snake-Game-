#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>
# define BUFFER_SIZE 5
sem_t full,empty,mutex;
int buffer[BUFFER_SIZE];
int index = 0;
int exit_flag = 0;
void *producer(void *arg){
    if (!exit_flag)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[BUFFER_SIZE] = index;
        printf("\n producing : %d",index);
        index =  (index +1 ) % BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }
    pthread_exit(NULL);
}
void *consumer(void *arg){
    if (!exit_flag)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        int item = buffer[index];
        printf("\nconsuming:%d",item);
        index = (index +1) % BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&empty);
        sleep(1);
    }
    pthread_exit(NULL);
}
void main(){
    int choice;
    pthread_t producer_thread,consumer_thread;
    sem_init(&full,0,0);
    sem_init(&empty,0,BUFFER_SIZE);
    sem_init(&mutex,0,1);
    do
    {
        printf("\nEnter your choice:");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            pthread_create(&producer_thread,NULL,producer,NULL);
            break;
        case 2:
            pthread_create(&consumer_thread,NULL,consumer,NULL);
            break;
        case 3:
            exit_flag = 1;
            break;
        default:
            printf("\nInvalid choice");
            break;
        }
    } while (choice != 3);
    pthread_join(producer_thread,NULL);
    pthread_join(consumer_thread,NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
}