#ifndef BACKING_STORE_GUARD
#define BACKING_STORE_GUARD

#include <string>

using namespace std;

/**
 * @brief Backing Store class
 * 
 */
class BackingStore
{
private:
    string STORE_NAME;    
public:
    BackingStore(string &file_name, uint32_t size);
    string readPageFrom(uint16_t page_addr, uint16_t page_size);
    bool prepare_backing_store(string& file_name, uint32_t size);
};


#endif