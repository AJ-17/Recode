#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include "/home/ak/learn/DS_Project/decoding/parity-check.h"
#include "/home/ak/learn/DS_Project/std-matrix/generator-H.h"
#include "/home/ak/learn/DS_Project/bit-byte-conv/bits-bytes.h"
#include "/home/ak/learn/DS_Project/decoding/huffman-deco.h"
int main() {
    int serverSock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;
    std::cout<<"\nWaiting for connection . . . .\n";
    bind(serverSock, (struct sockaddr*)&addr, sizeof(addr));
    
    listen(serverSock, 1);


    int clientSock = accept(serverSock, nullptr, nullptr);
    std::cout<<"\n :: Connected to client :: \n\n";
    

    //connection done now lets send/recivev
    int rtdb;
    recv(clientSock, &rtdb, sizeof(rtdb), 0);
    // Convert back to host byte order
    rtdb = ntohl(rtdb);

    //now rtdb is the real no of data bits after huffman encoding 

    int pbits=63*((rtdb+56)/57);//no of bits after converting 57 to 63 bits by adding parity bits
    int numBits=pbits;
    int numBytes=((pbits+7)/8);
 
    

    std::vector<uint8_t> buffer(numBytes);
    ssize_t received = recv(clientSock, buffer.data(), buffer.size(), 0);

    std::cout << "\n\nReceived :" << received << " bytes\n\n";
    // now i need to convert the bytes to bits again
    
    
    int szch=0; 
    
    recv(clientSock,&szch,sizeof(szch),0);
    szch=ntohl(szch);
    std::vector<char> ch(szch);
    recv(clientSock,ch.data(),ch.size(),0);

    int szfr;
    recv(clientSock,&szfr,sizeof(szfr),0);
    szfr=ntohl(szfr);

    std::vector<int> freq(szfr);
    for(auto &i:freq){
        recv(clientSock,&i,sizeof(i),0);
        i=ntohl(i);
    }
    
    //now we need to now check if out message conatain any error or not then we need to convert the message usign huffman
    std::vector<std::vector<bool>> H=h();
    std::vector<bool> c=unpackBits(buffer,numBits);
    std::cout<<"Message including Parity Bits : ";
    for(auto i :c){std::cout<<i;}
    std::cout<<"\n\n\n\n";
    std::vector<char> message;


    for(int i=0;i<c.size()/63;i++){      
        std::vector<bool> tmp(c.begin()+i*(63),c.begin()+(i+1)*(63));
    errdet(H,tmp);
    for(int j =0;j<tmp.size();j++){
        c[(i*63)+j]=tmp[j];
    }
}



     for (int i = c.size() / 63 - 1; i >= 0; --i) {
    c.erase(c.begin() + i * 63 + 57, c.begin() + i * 63 + 63);
}

    c.erase(c.begin()+rtdb,c.end());
    std::cout<<"\n\nMessage excluding Parity Bits : ";

    for(auto i :c){std::cout<<i;}
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    
    message= decode(c, ch, freq);
        // message is the correct message
        
    

    std::cout<<"Possible Message : \n\n";
    for(auto i :message){
        std::cout<<i;
    }


    
    close(clientSock);
    close(serverSock);
    
}