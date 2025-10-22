#ifndef HAMMING_H
#define HAMMING_H

#include <vector>

// ---------------------------
// Function Declarations
// ---------------------------

// Multiply two matrices of bools (binary multiplication with XOR)
std::vector<std::vector<bool>> mul(std::vector<std::vector<bool>>& a, std::vector<std::vector<bool>>& b);

// Convert 57-bit block to 63-bit by adding parity bits using generator matrix G
std::vector<bool> conv(std::vector<bool>& w, std::vector<std::vector<bool>>& G);

// Break full message into 57-bit chunks, pad remainder with 0s, and convert each to 63-bit
std::vector<bool> breakcodes(std::vector<bool> data, std::vector<std::vector<bool>>& G);

#endif // HAMMING_H
