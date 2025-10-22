#ifndef SENDER_H
#define SENDER_H

#include <vector>

// Send Huffman-encoded bits over TCP
int sendMessage( std::vector<bool> &bits, int rtdb,
                const std::vector<char>& ch, const std::vector<int>& freq);

#endif // SENDER_H
