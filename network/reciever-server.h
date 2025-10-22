#ifndef RECEIVER_H
#define RECEIVER_H

#include <vector>

// Receives a message over TCP, checks parity, and decodes using Huffman
std::vector<char> receive();

#endif // RECEIVER_H
