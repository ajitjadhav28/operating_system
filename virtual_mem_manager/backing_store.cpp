#include "backing_store.h"
#include <iostream>
#include <fstream>

BackingStore::BackingStore(string& file_name, uint32_t size){
    if(!prepare_backing_store(file_name, size)){
        STORE_NAME = file_name;
    }
}

bool BackingStore::prepare_backing_store(string& file_name, uint32_t size) {
    uint16_t c = 0;
    FILE *fptr = fopen(file_name.c_str() , "wb");
    rewind(fptr);
    if(fptr == NULL){
        cerr << "Can't create backing store." << endl;
        exit(1);
    }
    for(c=0; c < size; c++){
        char a = 32 + (c % 96);
        fwrite(&a, sizeof(char), 1, fptr);
    }
    fclose(fptr);
    return 0;
}

string BackingStore::readPageFrom(uint16_t page_addr, uint16_t page_size){
    char buff[page_size];
    ifstream store(STORE_NAME);
    store.seekg(page_addr*page_size);
    store.read(buff, page_size);
    return string(buff);
}
