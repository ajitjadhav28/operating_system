#include <stdio.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

#include "../mylib.h"

int main()
{
    const int SIZE = 4096;
    const char *name = "OS";
    int shm_fd;
    void *ptr;
    shm_fd = shm_open(name, O_RDONLY, 0666);
    if(shm_fd == -1) {
        printError("Can't open shared memory.");
        fprintf(stderr, Yellow "\t%s\n" Reset, strerror(errno));
        return 1;
    }
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if(ptr == MAP_FAILED) {
        printError("Mapping failed.");
        fprintf(stderr, Yellow "\t%s\n" Reset, strerror(errno));
        return 1;
    }
    printf("%s\n", (char *)ptr);
    // unlink shared memory
    shm_unlink(name);
}