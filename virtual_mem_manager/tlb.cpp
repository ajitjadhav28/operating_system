#include "tlb.h"

/**
 * @brief Construct a new TLB::TLB object
 *  Set default max_size = 16
 * 
 */
TLB::TLB(): max_size(16){

}

/**
 * @brief Construct a new TLB::TLB object
 * 
 * @param size initiate max_size = size
 */
TLB::TLB(uint16_t size) : max_size(size){

}

/**
 * @brief Returns currosponding Physical address if present
 * 
 * @param va Virtual Address
 * @return int32_t Physical address if present else -1
 */
int32_t TLB::getPhyAddr(uint16_t va){
    if(tlb.find(va) == tlb.end()){
        tlb_miss++;
        return -1;
    }
    tlb_hit++;
    return tlb.find(va)->second;
}

/**
 * @brief Insert record in TLB
 * 
 * @param va Virtual Address
 * @param pa Physical Address
 * @return int8_t 
 */
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

/**
 * @brief Return TLB hit count
 * 
 * @return uint64_t 
 */
uint64_t TLB::getTlbHit(){
    return tlb_hit;
}

/**
 * @brief Return TLB miss count
 * 
 * @return uint64_t 
 */
uint64_t TLB::getTlbMiss(){
    return tlb_miss;
}
