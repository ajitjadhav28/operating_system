/**
 * @file paging_performance.c
 * @author Ajit Jadhav (mr.ajitjadhav@gmail.com)
 * @brief  Checking performance of RMO and CMO access of 2-D array. 
 * 
 * @date 2019-08-27
 * 
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#include "mylib.h"

#define C (8*1024)
#define R 512
struct rlimit rlim;
MEM_LIMIT_128MB;

void paging_performance()
{
    long unsigned int arr[R][C];
    long int i,j,k;
    const int n = 10;
    time_t start, a, b;

    start = clock();
    for ( i = 0; i < R; i++){
        for ( j = 0; j < C; j++){
            arr[i][j] = 0;
        }
    }
    a = clock() - start;
    printf("Time for first loading[RMO]: %f seconds\n", (float)a/CLOCKS_PER_SEC);
    
    b = a = 0;
    for(k = 0; k < n; k++){
        start = clock();
        for ( i = 0; i < R; i++){
            for ( j = 0; j < C; j++){
                arr[i][j] = 0;
            }
        }
        a = a + (clock() - start);
    }
    printf("Average time for RMO access: %f seconds\n", ((float)a/10)/CLOCKS_PER_SEC);

    for(k = 0; k < n; k++){
        start = clock();
        for ( i = 0; i < C; i++){
            for ( j = 0; j < R; j++){
                arr[j][i] = 0;
            }
        }
        b = b + (clock() - start);
    }
    printf("Average time for CMO access: %f seconds\n", ((float)b/10)/CLOCKS_PER_SEC);

}

int main(int argc, char const *argv[])
{   
    long int sz;
    setrlimit(RLIMIT_AS, &r1);
    rlim.rlim_max = rlim.rlim_cur = 67108864; // 64MB stack
    if(setrlimit(RLIMIT_STACK, &rlim) == 0){
        getrlimit(RLIMIT_STACK, &rlim);
        printf("Current stack limit: %lu Bytes\n", rlim.rlim_cur);
    } else {
        printError("Can't set stack limit.");
        fprintf(stderr, "\t%s\n", strerror(errno));
    }
    sz = C * R * sizeof(long);
    printf("Size of long: %lu Bytes\n", sizeof(long));
    printf("Array size: %lu Bytes\n", sz);
    printf("Page size: %u Bytes\n", getpagesize());
    printf("Pages required for array: %.2f\n", ceil(sz/getpagesize()));
    paging_performance();
    return 0;
}
