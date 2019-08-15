#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    pid = fork();
    if(pid < 0){
        fprintf(stderr, "[ERROR] Fork failed.\n");
        exit(1);
    } else if(pid == 0) {
        sleep(1);
        execlp("/bin/ls", "ls", NULL);
        sleep(1);
    } else {
        wait(NULL);
        printf("Child completed");
    }
    return 0;
}