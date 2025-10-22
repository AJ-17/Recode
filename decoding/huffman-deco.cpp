#include "huffman-deco.h"

// ====================== Build Huffman Tree ======================
Node* huffman(std::vector<char> &ch, std::vector<int> fq) {
    std::unordered_map<char, int> freq;
    for (size_t i = 0; i < ch.size(); ++i) {
        freq[ch[i]] = fq[i];
    }

    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (auto &p : freq) {
        pq.push(new Node(p.first, p.second));
    }

    if (pq.empty()) return nullptr;

    Node *root = pq.top();
    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();

        int fs = left->freq + right->freq;
        Node *tmp = new Node('\0', fs);
        tmp->left = left;
        tmp->right = right;
        pq.push(tmp);
        root = tmp;
    }
    return root;
}

// ====================== Decode Huffman Bits ======================
std::vector<char> decode(std::vector<bool> m, std::vector<char> &ch, std::vector<int> &fq) {
    Node* root = huffman(ch, fq);
    Node* tmp = root;
    std::vector<char> message;

    for (bool bit : m) {
        tmp = (bit == 0) ? tmp->left : tmp->right;

        if (tmp && tmp->ch != '\0') {
            message.push_back(tmp->ch);
            tmp = root; // reset to root after decoding one symbol
        }
    }

   
    return message;
}
