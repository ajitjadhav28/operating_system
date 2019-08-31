#ifndef PAGE_TABLE_GUARD
#define PAGE_TABLE_GUARD

#include <array>

using namespace std;

/**
 * @brief PageTable class
 * 
 */
class PageTable{
    private:
        // Page table with 256 entries
        array<int16_t, 256> page_table;
        uint64_t page_fault_count = 0;
        uint64_t page_hit_count = 0;
    public:
        PageTable();
        int16_t getPageAt(uint16_t page_addr);
        int16_t operator[](uint16_t page_addr);
        bool isValidAddress(uint16_t page_addr);
        int8_t setPageAt(uint16_t page_addr, uint8_t page);
        void printPageTableEntry(uint16_t page_addr);
        uint64_t getPageFaultCount();
        uint64_t getPageHitCount();
};

#endif