#ifndef HUFFMAN_DECO_H
#define HUFFMAN_DECO_H

#include <vector>
#include <unordered_map>
#include <queue>

// ====================== Node Definition ======================
struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// ====================== Compare Struct ======================
struct Compare {
    bool operator()(Node* a, Node* b) const {
        return a->freq > b->freq;
    }
};

// ====================== Function Declarations ======================
Node* huffman(std::vector<char> &ch, std::vector<int> fq);
std::vector<char> decode(std::vector<bool> m, std::vector<char> &ch, std::vector<int> &fq);

#endif // HUFFMAN_DECO_H
