#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define BUFFER_SIZE 5
sem_t full, empty, mutex;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
void *producer(void *arg) {
    while (1) {
        sem_wait(&empty);
        sem_wait(&mutex);

        printf("Producing item %d\n", in);
        buffer[in] = in;
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&full);

        sleep(1);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);

        printf("Consuming item %d\n", out);
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);

        sleep(2);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    int choice;
    do {
        printf("\n1. Start Producer\n2. Start Consumer\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: pthread_create(&producer_thread, NULL, producer, NULL); break;
            case 2: pthread_create(&consumer_thread, NULL, consumer, NULL); break;
            case 3:
                sem_destroy(&empty);
                sem_destroy(&full);
                sem_destroy(&mutex);
                pthread_cancel(producer_thread);
                pthread_cancel(consumer_thread);
                return 0;
            default: printf("Invalid choice\n");
        }
    } while (choice != 3);

    return 0;
}
