#include "consumer.h"

void *consumer(void *param) {
    buffer_item item;
    int i = 0;
    while(1) {
        sleep(rand() % 5);
        if(removeItem(&item, &i))
            printf(Bold_Red"Consumer error!\n"Reset);
        else
            printf(Green"Consumer consumed item %d.\n"Reset, item);
    }
    
}