#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main()
{
    int i;
    pid_t pid;

    for (i=0; i < 4; i++)
        pid = fork();
    if(pid == 0){
        printf("PID: %d\n", getpid());
        return 0;
    }
    if(pid > 0)
        wait(NULL);

}