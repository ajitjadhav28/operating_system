#include "backing_store.h"
#include <iostream>
#include <fstream>

/**
 * @brief Construct a new Backing Store:: Backing Store object
 * 
 * @param file_name Name of file
 * @param size size of file in bytes
 */
BackingStore::BackingStore(string& file_name, uint32_t size){
    if(!prepare_backing_store(file_name, size)){
        STORE_NAME = file_name;
    }
}

/**
 * @brief Create file and fill data in it.
 * 
 * @param file_name Name of file to create
 * @param size size of fie in bytes
 * @return true error 
 * @return false success
 */
bool BackingStore::prepare_backing_store(string& file_name, uint32_t size) {
    uint16_t c = 0;
    FILE *fptr = fopen(file_name.c_str() , "wb");
    rewind(fptr);
    if(fptr == NULL){
        cerr << "Can't create backing store." << endl;
        exit(1);
    }
    for(c=0; c < size; c++){
        char a = 32 + (c % 96); // ASCII char's from 32 to 128
        fwrite(&a, sizeof(char), 1, fptr);
    }
    fclose(fptr);
    return 0;
}

/**
 * @brief Read page from backing_store file.
 * 
 * @param page_addr Address of page
 * @param page_size size of page
 * @return string page string
 */
string BackingStore::readPageFrom(uint16_t page_addr, uint16_t page_size){
    char buff[page_size];
    ifstream store(STORE_NAME);
    store.seekg(page_addr*page_size);
    store.read(buff, page_size);
    return string(buff);
}
