// bits-bytes.h
#ifndef BITS_BYTES_H
#define BITS_BYTES_H

#include <vector>
#include <cstdint>

// Pack a vector of bits into bytes (MSB first)
std::vector<uint8_t> packBits(const std::vector<bool>& bits);

// Unpack a byte array into a vector of bits (requires number of bits to extract)
std::vector<bool> unpackBits(const std::vector<uint8_t>& bytes, int numBits);

#endif // BITS_BYTES_H
