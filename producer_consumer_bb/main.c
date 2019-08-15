#include <pthread.h>
#include "buffer.h"
#include "producer.h"
#include "consumer.h"

int main(int argc, char const *argv[])
{
    int i = 0;
    pthread_attr_t attr[2];
    pthread_t tid[2];

    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&mutex, 0, 1);
    
    for(i=0; i < BUFFER_SIZE; i++)
        buffer[i] = 0;
    
    pthread_attr_init(&attr[0]);
    pthread_attr_init(&attr[1]);
    pthread_create(&tid[0], &attr[0], producer, NULL);
    pthread_create(&tid[1], &attr[1], consumer, NULL);
    printf("Two threads with ID's %lu & %lu created.\n", tid[0], tid[1]);
    sleep(30);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    return 0;
}
