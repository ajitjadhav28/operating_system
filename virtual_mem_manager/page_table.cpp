#include "page_table.h"
#include <iostream>

/**
 * @brief Construct a new Page Table:: Page Table object
 * 
 */
PageTable::PageTable(){
    page_table.fill(-1);
}

/**
 * @brief Check if address is valid
 * 
 * @param page_addr address to check
 * @return true valid
 * @return false invalid
 */
bool PageTable::isValidAddress(uint16_t page_addr){
    return (page_addr >= page_table.max_size()) ? false : true;
}

/**
 * @brief Returns page at specified address
 * 
 * @param page_addr address of page 
 * @return int16_t page(frame_address)
 */
int16_t PageTable::getPageAt(uint16_t page_addr){
    int16_t page;
    if(!isValidAddress(page_addr)){
        cerr << "Invalid page address!" << endl;
        return -1;
    }
    if((page = page_table[page_addr]) == -1){
        fprintf(stderr, "[%u] Page Fault.\n", page_addr);
        page_fault_count++;
        return -2;
    }
    page_hit_count++;
    return page;
}

/**
 * @brief getPageAt with operator
 * 
 * @param page_addr 
 * @return int16_t 
 */
int16_t PageTable::operator[](uint16_t page_addr){
    return getPageAt(page_addr);
}

/**
 * @brief insert page in page table at address
 * 
 * @param page_addr 
 * @param page 
 * @return int8_t 
 */
int8_t PageTable::setPageAt(uint16_t page_addr, uint8_t page){
    if(!isValidAddress(page_addr)){
        cerr << "Invalid page address!" << endl;
        return -1;
    }
    page_table[page_addr] = page;
    return 0;
}

/**
 * @brief Print entry in page tabe at address
 * 
 * @param page_addr 
 */
void PageTable::printPageTableEntry(uint16_t page_addr){
    uint8_t page = getPageAt(page_addr);
    printf("ADDR:%u, PAGE_DATA: %u\n", page_addr, page);
}

/**
 * @brief Return page faut count
 * 
 * @return uint64_t 
 */
uint64_t PageTable::getPageFaultCount(){
    return page_fault_count;
}

/**
 * @brief Return page hit count
 * 
 * @return uint64_t 
 */
uint64_t PageTable::getPageHitCount(){
    return page_hit_count;
}
