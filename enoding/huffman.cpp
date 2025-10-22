#include "huffman.h"
#include <queue>

bool Compare::operator()(Node* a, Node* b) {
    return a->freq > b->freq;
}

Node* huffman(std::vector<char> &ch, std::vector<int> fq) {
    std::unordered_map<char, int> freq;
    for (size_t i = 0; i < ch.size(); ++i) {
        freq[ch[i]] = fq[i];
    }

    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for(auto &p : freq) pq.push(new Node(p.first, p.second));
    if (pq.empty()) return nullptr;

    Node *root = pq.top();
    while(pq.size() > 1){
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        Node *tmp = new Node('\0', left->freq + right->freq);
        tmp->left = left;
        tmp->right = right;
        pq.push(tmp);
        root = tmp;
    }
    return root;
}

void getcodes(std::unordered_map<char, std::vector<bool>> &codes, Node *root, std::vector<bool> tmp) {
    if(!root) return;
    if(root->ch != '\0') codes[root->ch] = tmp;
    else {
        tmp.push_back(0);
        getcodes(codes, root->left, tmp);
        tmp.back() = 1;
        getcodes(codes, root->right, tmp);
    }
}

std::vector<bool> encode(std::string &para, std::unordered_map<char, std::vector<bool>> &codes) {
    std::vector<bool> encoded;
    for(char &c : para) {
        encoded.insert(encoded.end(), codes[c].begin(), codes[c].end());
    }
    return encoded;
}



