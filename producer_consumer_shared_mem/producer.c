#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#include "../mylib.h"

int main()
{
    const int SIZE = 4096;
    const char *name = "OS";
    const char *msg_0 = "Hello";
    const char *msg_1 = "World!";
    int shm_fd;
    void *ptr;
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);    
    ftruncate(shm_fd, SIZE);
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    sprintf(ptr,"%s", msg_0);
    ptr += strlen(msg_0);
    sprintf(ptr,"%s", msg_1);
    ptr += strlen(msg_1);
    return 0;
}
