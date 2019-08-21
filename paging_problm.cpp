/**
 * @file paging_problm.cpp
 * @author Ajit Jadhav (mr.ajitjadhav@gmail.com)
 * @brief Problem from Galvin - OS Concepts
 * @date 2019-08-21
 */
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

#define ADDR_LEN 32

int main(int argc, char const *argv[])
{
    if(argc != 2) {
        cerr << "This program takes one 32bit virtual address as argument.\n";
        exit(1);
    }
    unsigned int address = strtoul(argv[1], nullptr, 10);
    if(address > 0xffffffff){
        cerr << "Address in not 32bit.\n";
        exit(2);
    }
    unsigned int d = log2(4*1024) ; // for 4KB page size
    unsigned int no_of_pages = pow(2,32)/pow(2,12); // N
    unsigned int p = log2(no_of_pages);
    unsigned int addr_d = (0xffffffff >> p) & address;
    unsigned int addr_p =  ((0xffffffff << d) & address) >> d;
    cout << "The address " << address << " contains:" << endl;
    cout << "Page number: " << addr_p << endl;
    cout << "Offset: " << addr_d << endl;
    return 0;
}
