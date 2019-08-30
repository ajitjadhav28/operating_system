#include "tlb.h"

TLB::TLB(): max_size(16){

}

TLB::TLB(uint16_t size) : max_size(size){

}

int32_t TLB::getPhyAddr(uint16_t va){
    if(tlb.find(va) == tlb.end()){
        tlb_miss++;
        return -1;
    }
    tlb_hit++;
    return tlb.find(va)->second;
}

int8_t TLB::setRecord(uint16_t va, uint16_t pa){
    if(tlb.size() == max_size){ // If TLB full remove random element
        unordered_map<uint16_t,uint16_t>::iterator it = tlb.begin();
        advance(it, rand()%tlb.size());
        tlb.erase(it);
    }
    tlb.insert(
        pair<uint16_t, uint16_t>(va, pa)
    );
    return 0;
}

uint64_t TLB::getTlbHit(){
    return tlb_hit;
}

uint64_t TLB::getTlbMiss(){
    return tlb_miss;
}
