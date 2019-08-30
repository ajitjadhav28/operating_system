#include "page_table.h"
#include <iostream>

bool PageTable::isValidAddress(uint16_t page_addr){
    return (page_addr >= page_table.max_size()) ? false : true;
}

int16_t PageTable::getPageAt(uint16_t page_addr){
    uint8_t page;
    if(!isValidAddress(page_addr)){
        cerr << "Invalid page address!" << endl;
        return -1;        
    }
    if((page = page_table[page_addr]) == NULL){
        fprintf(stderr, "[%u] Page Fault.\n", page_addr);
        page_fault_count++;
        return NULL;
    }
    page_hit_count++;
    return page;
}

int16_t PageTable::operator[](uint16_t page_addr){
    return getPageAt(page_addr);
}

int8_t PageTable::setPageAt(uint16_t page_addr, uint8_t page){
    if(!isValidAddress(page_addr)){
        cerr << "Invalid page address!" << endl;
        return -1;        
    }
    page_table[page_addr] = page;
    return 0;
}

void PageTable::printPageTableEntry(uint16_t page_addr){
    uint8_t page = getPageAt(page_addr);
    printf("ADDR:%u, PAGE_DATA: %u\n", page_addr, page);
}

uint64_t PageTable::getPageFaultCount(){
    return page_fault_count; 
}

uint64_t PageTable::getPageHitCount(){
    return page_hit_count;
}