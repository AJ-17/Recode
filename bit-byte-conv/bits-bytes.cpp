// now we have the binary code that need to be transmitted 
//lets first convernt the bits to byte as computer send and recieves bytes
#include <cstddef>
#include <vector>
#include "bits-bytes.h"
#include <cstdint>
#include "bits-bytes.h"
std::vector<uint8_t> packBits(const std::vector<bool>& bits){
    size_t n=bits.size();
    size_t numBytes = (n+7)/8;
    std::vector<uint8_t> bytes(numBytes,0);
    for(size_t i=0;i<n;i++){
        if(bits[i]){
            bytes[i/8]|=(1<<(7-(i%8)));
        }
    }
    return bytes;
}


std::vector<bool> unpackBits(const std::vector<uint8_t>& bytes,int numBits){

    std::vector<bool> bits(numBits,0);
    for(int i =0;i<bits.size();i++){
        bits[i]= (bytes[i/8] >> (7 - (i % 8))) & 1;
    }

    return bits;
}
