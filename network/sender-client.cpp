#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <cstdint>

#include "/home/ak/learn/DS_Project/noise/noise.h"
#include "/home/ak/learn/DS_Project/bit-byte-conv/bits-bytes.h"

int sendMessage( std::vector<bool>& bits, int rtdb,
                const std::vector<char>& ch, const std::vector<int>& freq) {

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return -1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    //inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        perror("Invalid address");
        close(sock);
        return -1;
    }

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connect failed");
        close(sock);
        return -1;
    }

    // ---------------------- Step 1: Send number of data bits ----------------------
    int rtdb_net = htonl(rtdb);
    if (::send(sock, &rtdb_net, sizeof(rtdb_net), 0) < 0) {
        perror("Send rtdb failed");
        close(sock);
        return -1;
    }

    // ---------------------- Step 2: Send data bytes ----------------------
    ::addnoise(bits);
    std::vector<uint8_t> data = packBits(bits);
    if (::send(sock, data.data(), data.size(), 0) < 0) {
        perror("Send data failed");
        close(sock);
        return -1;
    }

    // ---------------------- Step 3: Send Huffman chars ----------------------
    int szch_net = htonl(ch.size());
    ::send(sock, &szch_net, sizeof(szch_net), 0);
    ::send(sock, ch.data(), ch.size(), 0);

    // ---------------------- Step 4: Send Huffman frequencies ----------------------
    int szfr_net = htonl(freq.size());
    ::send(sock, &szfr_net, sizeof(szfr_net), 0);

    for (int val : freq) {
        int val_net = htonl(val);
        ::send(sock, &val_net, sizeof(val_net), 0);
    }

    close(sock);
    return 0;
}
