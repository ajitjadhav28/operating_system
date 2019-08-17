/**
 * @file writer.c
 * @author Ajit Jadhav (mr.ajitjadhav@gmail.com)
 * @brief Writer process of *First Reader-Writer* problem.
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

#include "../mylib.h"

sem_t *mutex;
static volatile unsigned int flag = 1;

/**
 * @brief Handle Ctrl+c
 * 
 * @param idk 
 */
void handlerInterrupt(int idk){
    // int i;
    // sem_getvalue(mutex, &i);
    // if(i == 0)
    //     sem_post(mutex);
    flag = 0;
}

/**
 * @brief Open file and write random data in it
 * 
 * @param fname name of file
 * @return int positive int on success. -1 on failure 
 */
int writeRandomDataInFile(const char *fname) {
    int char_written = 0, r;
    FILE *fp = fopen(fname, "w+");
    if(fp == NULL) {
        printError("Error while opening file:");
        fprintf(stderr,"\t%s\n", strerror(errno));
        return -1;
    }
    r = rand();
    char_written = fprintf(fp, "Random write: %u\n", r);
    printf( Green "[Writer|%d]:" Reset " Random write: %u\n", getpid(), r);
    fclose(fp);
    return char_written;
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, handlerInterrupt);
    if(argc != 2) {
        printError("Writer takes exactly one argument which is file name to write data.");
        exit(1);
    }
    mutex = sem_open("frw_sem", O_CREAT, 0666, 1);
    
    if(mutex == SEM_FAILED) {
        printError("Semaphore open error: \n");
        fprintf(stderr, "\t%s\n", strerror(errno));
        exit(errno);
    }
    
    while(flag) {
        sem_wait(mutex);
        writeRandomDataInFile(argv[1]); // Critical section
        sem_post(mutex);
        sleep(rand() % 5);     
    }
    return 0;
}
