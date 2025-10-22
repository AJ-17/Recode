#ifndef PARITY_CHECK_H
#define PARITY_CHECK_H

#include <vector>
#include <iostream>

// ---------------------------
// Function Declarations
// ---------------------------

// Multiply two matrices of bools in GF(2)
std::vector<std::vector<bool>> mul(std::vector<std::vector<bool>>& a, std::vector<std::vector<bool>>& b);



// Compute syndrome S = H * c^T
std::vector<std::vector<bool>> findS(std::vector<std::vector<bool>>& H, std::vector<bool>& c);

// Detect if there is an error in the received codeword
bool errdet(std::vector<std::vector<bool>>& H, std::vector<bool>& c);

// Optionally, find the position of single-bit error
int findErrorPos(std::vector<std::vector<bool>>& H, std::vector<bool>& c);

//fix 1 error max
void fix(std::vector<std::vector<bool>> &H,std::vector<std::vector<bool>> &s,std::vector<bool> &c);

#endif // PARITY_CHECK_H
