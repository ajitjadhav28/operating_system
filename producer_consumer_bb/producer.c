#include "producer.h"
#include "limits.h"

void *producer(void *param) {
    buffer_item item;
    int i = 0;
    while(1) {
        sleep(rand() % 5);
        item = rand() % INT_MAX;
        if(insertItem(item, &i))
            printf(Bold_Red"Producer error!\n"Reset);
        else
            printf(Green"Producer produced item %d.\n"Reset, item); 
    }
}