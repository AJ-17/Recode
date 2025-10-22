#ifndef GENERATOR_H_H
#define GENERATOR_H_H

#include <vector>

// Check if a number is power of 2
bool isPowerOfTwo(int x);

// Generate (63,57) Hamming Generator matrix
std::vector<std::vector<bool>> generate();

// Generate (63,57) Hamming Parity-Check matrix H
std::vector<std::vector<bool>> h();

#endif // GENERATOR_H_H
