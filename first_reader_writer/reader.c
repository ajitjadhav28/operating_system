/**
 * @file reader.c
 * @author Ajit Jadhav (mr.ajitjadhav@gmail.com)
 * @brief Reader process of *First Reader-Writer* problem.
 * @date 2019-08-17
 * 
 */

#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "../mylib.h"

sem_t *file_mutex, *reader_mutex;
static volatile unsigned int flag = 1;
void *ptr;
const char *cname = "frw_countr";

/**
 * @brief Handle Ctrl+c
 * 
 * @param idk 
 */
void handlerInterrupt(int idk){
    flag = 0;
    shm_unlink(cname);
}

/**
 * @brief Read counter value from shared memory
 * 
 * @return unsigned int 
 */
unsigned int readCount(){
    unsigned int c = 0;
    sscanf(ptr, "%u", &c);
    return c;
}

/**
 * @brief Update counter
 *      count = count + i
 * @param i 
 * @return unsigned int 
 */
unsigned int updateCount(int i){
    unsigned int c = readCount() + i;
    sprintf(ptr, "%u", c);
    return c;
}

/**
 * @brief Read contents of file in buffer
 * 
 * @param fname file name
 * @param buf buffer
 * @param buflen buffer length
 */
void readFile(const char *fname, char *buf, int buflen) {
    FILE *fp = fopen(fname, "r");
    if(fp == NULL) {
        printError("Error while opening file:");
        fprintf(stderr,"\t%s\n", strerror(errno));
        return;
    }
    *(buf++) = fgetc(fp);
    printf( Yellow "[Reader|%d]: " Reset, getpid());
    printf("%c", *(buf-1));
    buflen--;
    while(*(--buf) != '\n' && buflen) {
        *(buf++) = fgetc(fp);
        printf("%c", *(buf-1));
        buflen--;
    }
    if(buflen) *(buf++) = '\0';
    else *(buf--) = '\0';
    fclose(fp);
}

int main(int argc, char const *argv[])
{
    char READ_BUFF[50];
    const int SIZE = __getpagesize();
    int shm_fd;
    shm_fd = shm_open(cname, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
    sprintf(ptr, "%d", 0);
    file_mutex = sem_open("frw_sem", O_CREAT, 0666, 1);
    reader_mutex = sem_open("frw_reader_sem", O_CREAT, 0666, 1);

    signal(SIGINT, handlerInterrupt);
    if(argc != 2) {
        printError("Reader takes exactly one argument which is file name to write data.");
        exit(1);
    }

    while(flag) {

    /** Entry section begin */
    sem_wait(reader_mutex);
    updateCount(1);
    if(readCount() == 1)
        sem_wait(file_mutex);
    sem_post(reader_mutex);
    /** Entry section end */

    /** Critical Section begin */
    readFile(argv[1], READ_BUFF, 50);
    /** Critical section end */

    /** Exit section begin */
    sem_wait(reader_mutex);
    updateCount(-1);
    if(readCount() == 0)
        sem_post(file_mutex);
    sem_post(reader_mutex);
    /** Exit section end */

    sleep(rand() % 5);
    }
    return 0;
}
