#ifndef TLB_GUARD
#define TLB_GUARD

#include<unordered_map>
#include <random>

using namespace std;

class TLB {
    private:
        unordered_map<uint16_t,uint16_t> tlb;
        uint64_t tlb_hit = 0, tlb_miss = 0;
        const uint16_t max_size;
    public:
        TLB(uint16_t size);
        TLB();
        int32_t getPhyAddr(uint16_t va);
        int8_t setRecord(uint16_t va, uint16_t pa);
        uint64_t getTlbHit();
        uint64_t getTlbMiss();
};

#endif