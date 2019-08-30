/**
 * @file main.cpp
 * @author Ajit Jadhav (mr.ajitjadhav@gmail.com)
 * @brief Programming Project form O.S. Concepts: 
 *             Designing a Virtual Memory Manager
 *             (Physical Address Space = Virtual Address Space)
 * @date 2019-08-30
 */

#include <iostream>
#include <array>
#include <fstream>

#include "page_table.h"
#include "backing_store.h"
#include "tlb.h"

#define BACKING_STORE "BACKING_STORE.bin"
#define ADDR_FILE "input_addresses.txt"

#define ADDR_SPACE 16
#define PAGE_ADDR 8
#define PAGE_SIZE 256
#define OFFSET 8

// Virtual address
typedef struct v_addr{
    uint8_t p;
    uint8_t d;
}v_addr;

// Physical address
typedef struct p_addr{
    uint8_t f;
    uint8_t d;
}p_addr;

using namespace std;

PageTable page_table;
string store_name = BACKING_STORE;
BackingStore store(store_name, 0xffff);
TLB tlb;

// Byte addressable phy_memory with 256 frames
// size of frame is 256 Byte
array<array<char,256>, 256> phy_memory;
string page_buff;

bool prepare_logical_addresses(uint16_t n){
    FILE *fptr = fopen(ADDR_FILE, "w");
    if(fptr == NULL){
        cerr << "Error creating address file." << endl;
        exit(1);
    }
    while(n--){
        // randon 32 bit address
        fprintf(fptr, "%u\n", rand() % 0xffffffff);
    }
    fclose(fptr);
    return 0;
}

bool parseAddress(uint32_t addr, v_addr *v){
    if(v == NULL){
        cerr << "Null virtual address pointer.\n";
        return 1;
    }
    v->p = (0x0000FFFF & addr) >> OFFSET; // get page index/address
    v->d = (0x0000FFFF & addr) & (0xFFFF >> PAGE_ADDR); // get offset
    return 0;
}



int main(int argc, char const *argv[])
{
    uint32_t virtual_addr;
    char byte_buff;
    v_addr vadd;
    p_addr padd;
    fstream log_addr_file(ADDR_FILE);
    
    if(argc == 2)
        prepare_logical_addresses(atol(argv[1]));
    else
        prepare_logical_addresses(100);

    while(log_addr_file >> virtual_addr){
        if(parseAddress(virtual_addr, &vadd)){
            exit(1);
        }
        uint16_t v = virtual_addr & 0x0000ffff;
        int32_t t = tlb.getPhyAddr(v); // Query TLB
        if(t != -1){ // TLB hit
            // std::cout << "TLB hit for " << v << endl;
            if(parseAddress(t, &vadd)){
                cerr << "Invalid address!" << endl;
                exit(1);
            }
            byte_buff = phy_memory[vadd.p][vadd.d];
        }
        else { // TLB Miss
            // Find the page in page table
            // std::cout << "TLB miss for " << v << endl;
            padd.f = page_table[vadd.p]; // Query Page Table
            if(padd.f == -1) continue; // if invalid address continue
            if(padd.f == NULL){ // if page not present
                page_buff = store.readPageFrom(vadd.p, PAGE_SIZE); // read it from backing_store
                padd.f = vadd.p; // as V.A.S. = P.A.S

                for(auto pl = 0; pl < PAGE_SIZE; pl++){
                    phy_memory[padd.f][pl] = page_buff[pl]; // store it in memory
                }

                // Update Page tabe
                page_table.setPageAt(vadd.p, padd.f);

                // Update TLB----------
                uint16_t p = (padd.f << OFFSET) | vadd.d;
                tlb.setRecord(v,p);
                //------TLB Updated---------

                // Read byte
                byte_buff = page_buff[vadd.d];
            } else {    // if page present in memory
                padd.d = vadd.d;
                byte_buff = phy_memory[padd.f][padd.d]; // read byte from memory
            }
        }
        printf("Virtual Address: %u => p: %u, d: %u\n", v, vadd.p, vadd.d);
        printf("Byte stored at that address: %c\n", byte_buff);
    }
    std::cout << "TLB hit: " << tlb.getTlbHit() << endl;
    std::cout << "TLB miss: " << tlb.getTlbMiss() << endl;
    std::cout << "Page hits: " << page_table.getPageHitCount() << endl;
    std::cout << "Page faults: " << page_table.getPageFaultCount() << endl;
    return 0;
}
