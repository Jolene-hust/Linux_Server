// 修改TCP发送缓冲区的客户端程序
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define BUFFER_SIZE 512

int main(int argc, char* argv[]){
    if (argc <= 2)
    {
        cout << "usage:" << argv[0] << "ip_address, port_number, send_bufer_size" << endl;
        return 1;
    }

    const char* ip = argv[1];
    int port = atoi(argv[2]);

    // 创建客户端socket套接字
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    // 创建socket地址
    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_address.sin_addr);

    int sendbuf = atoi(argv[3]);
    int len = sizeof(sendbuf);

    // 先设置TCP发送缓冲区的大小，然后立即读取
    setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, sizeof(sendbuf));
    getsockopt(sock ,SOL_SOCKET, SO_SNDBUF, &sendbuf, (socklen_t*)&len);
    cout << "the TCP send buffer size after setting is " << sendbuf << endl;
    
}