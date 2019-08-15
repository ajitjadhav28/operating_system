#include "buffer.h"

int insertItem(buffer_item item, int *i) {
    if(sem_wait(&empty) == -1) {
        printError("Down on `empty` in insertion unsuccessful.");
        fprintf(stderr, "\t%s\n", strerror(errno));
        return 1;
    }
    if(sem_wait(&mutex) == -1){
        printError("Down on `mutex` in insertion unsuccessful.");
        fprintf(stderr, "\t%s\n", strerror(errno));
        return 1;
    }
    buffer[*i] = item;
    *i = (*i+1) % BUFFER_SIZE;
    sem_post(&mutex);
    sem_post(&full);
    return 0;
}

int removeItem(buffer_item *item, int *i) {
    if(sem_wait(&full) == -1) {
        printError("Down on `empty` in insertion unsuccessful.");
        fprintf(stderr, "\t%s\n", strerror(errno));
        return 1;
    }
    if(sem_wait(&mutex) == -1){
        printError("Down on `mutex` in insertion unsuccessful.");
        fprintf(stderr, "\t%s\n", strerror(errno));
        return 1;
    }
    *item = buffer[*i];
    buffer[*i] = 0;
    *i = (*i+1) % BUFFER_SIZE;
    sem_post(&mutex);
    sem_post(&empty);
    return 0;
}