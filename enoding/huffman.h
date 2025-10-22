#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <vector>
#include <unordered_map>
#include <string>

// Huffman tree node
struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Comparator for priority queue
struct Compare {
    bool operator()(Node* a, Node* b);
};

// Function declarations
Node* huffman(std::vector<char> &ch, std::vector<int> fq);
void getcodes(std::unordered_map<char, std::vector<bool>> &codes, Node *root, std::vector<bool> tmp={});
std::vector<bool> encode(std::string &para, std::unordered_map<char, std::vector<bool>> &codes);

#endif // HUFFMAN_H
