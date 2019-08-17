#include <semaphore.h>
#include <errno.h>
#include <string.h>
#include "../mylib.h"
#include <unistd.h>

/**
 * @brief Buffer item
 * 
 */
typedef int buffer_item;

/**
 * @brief size of buffer
 * 
 */
#define BUFFER_SIZE 5

/**
 * @brief Buffer
 * 
 */
buffer_item buffer[BUFFER_SIZE];

/**
 * @brief Counting semaphores 
 * 
 */
sem_t mutex, empty, full;

int insertItem(buffer_item, int *);

int removeItem(buffer_item*, int *);