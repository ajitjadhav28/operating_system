#include <semaphore.h>
#include <errno.h>
#include <string.h>
#include "../mylib.h"
#include <unistd.h>

typedef int buffer_item;
#define BUFFER_SIZE 5

buffer_item buffer[BUFFER_SIZE];
sem_t mutex, empty, full;

int insertItem(buffer_item, int *);
int removeItem(buffer_item*, int *);