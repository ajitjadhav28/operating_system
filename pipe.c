/**
 * @file pipe.c
 * @author Ajit Jadhav (mr.ajitjadhav@gmail.com)
 * @brief Communication between parent and child process using pipe
 * @date 2019-08-14
 *  
 */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <time.h>
#include "mylib.h"

#define BUFFER_SZ 50
#define READ_END 0
#define WRITE_END 1

int main(void)
{
    char write_msg[BUFFER_SZ] = Green "Hello there. I travelled through pipe!" Reset ;
    char read_msg[BUFFER_SZ];
    int fd[2];
    pid_t pid;
    if(pipe(fd) == -1) {
        printError("Pipe creation failed!");
        return 1;
    }
    if((pid = fork()) < 0) {
        printError("Fork failed!");
        return 1;
    }
    
    // Parent
    if(pid > 0) {
        close(fd[READ_END]);
        if(write(fd[WRITE_END], write_msg, strlen(write_msg)+1 ) == -1)
            printError("Writing pipe failed.");
        close(fd[WRITE_END]);
        printf("[PID:%d][TIME: %ld] Sent message to child.\n", getpid(), time(NULL));
        wait(NULL);
    }
    else {  // Child
        sleep(1);
        close(fd[WRITE_END]);
        if(read(fd[READ_END], read_msg, BUFFER_SZ) < 0)
            printError("Reading pipe failed.");
        printf("[PID:%d][TIME: %ld] %s\n", getpid(), time(NULL), read_msg);
        close(fd[READ_END]);
    }
    return 0;
}