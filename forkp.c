/**
 * @file forkp.c
 * @author Ajit Jadhav (mr.ajitjadhav@gmail.com)
 * @brief Tracing fork() call
 * @date 2019-08-26
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

#define N 2

int main()
{
    int i;
    pid_t pid, pa[N];

    for (i = 0; i < N; i++){
        pa[i] = pid = fork();
        if(pid == 0){
            fprintf(stderr, "PID_actual: %d \tPID_in_child: %d \ti: %d\n", getpid(), pid, i);
            // return 0;    // Uncommenting this will generate only "n" childs
                            // Because child terminates here, so don't execute
                            // next cycle of for-loop.
        }
    }
    if(pid > 0){
        for(i = 0; i < N; i++)
            waitpid(pa[i], NULL, 0); // Waiting for childs to terminate
        fprintf(stderr, "PID_parent:%d\n", getpid());    // Printed after child is terminated
                                                // There can be more than one parent
                                                // parent => sub_parent => child
    }

}