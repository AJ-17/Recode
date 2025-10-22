#include <iostream>
#include <string>
#include <vector>
#include "/home/ak/learn/DS_Project/bit-byte-conv/bits-bytes.h"
#include "/home/ak/learn/DS_Project/enoding/hamming.h"
#include "/home/ak/learn/DS_Project/enoding/huffman.h"
#include "/home/ak/learn/DS_Project/std-matrix/generator-H.h"
#include "/home/ak/learn/DS_Project/network/sender-client.h"
#include "/home/ak/learn/DS_Project/noise/noise.h"


int main(){
    int n; std::cout<<"Enter no of lines :  "; 
    std::cin>>n; std::cin.ignore(); 
    std::string para,line;
    std::cout<<"\nEnter Orignal Data : \n\n";
     for(int i =0;i<n;i++)
     { std::getline(std::cin,line); 
        para+=line;
        if(i != n-1) para += "\n"; 
    } 

    std::unordered_map<char,int> freq;
    for(char c : para){ freq[c]++; }
    std::vector<char> ch;
    std::vector<int> fq;

    for(auto i:freq){
        ch.push_back(i.first);
        fq.push_back(i.second);
    }
    Node * root=huffman(ch, fq);
    std::unordered_map<char, std::vector<bool>> codes;
    getcodes(codes,root);
    std::vector<bool> msg=encode(para,codes);
    int rtdb=msg.size();
    std::cout<<"\n\n\n\nMessage after HUffman encoding  : ";
    for(auto i:msg){
        
        std::cout<<i;
    }

    std::cout<<"\n\n\n\n\n";

    std::vector<std::vector<bool>> G=generate();
    msg=breakcodes(msg,G);
    

    std::cout<<"Message after adding parity btis   : ";
    
    for(auto i:msg){
        std::cout<<i;
    }
        std::cout<<"\n\n\n\n\n";
    sendMessage(msg,rtdb,ch,fq);

}