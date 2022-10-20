#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

using namespace std;

int main(int argc, char* argv[]){
    if (argc <= 2){
        // 输入参数是ip地址和端口号
        cout << "usage: " << argv[0] << "ip_address and port_number" << endl;
        return 1;
    }
    const char *ip = argv[1]; // ip地址
    int port = atoi(argv[2]); // 端口号

    // 创建服务器的套接字
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    // 创建socket地址
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, ip, &address.sin_addr);

    // 绑定套接字
    int ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
    // cout << errno << endl;
    assert(ret != -1);

    // 监听
    ret = listen(sock, 5);
    assert(ret != -1);

    // 暂停20s以等待客户端连接和相关操作完成
    sleep(20);

    // 新建与客户端通信的socket地址
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // 从listen监听队列中接受一个连接
    int connect_sockfd = accept(sock, (struct sockaddr*)&client_addr, &client_addr_len);
    // assert(connect_sockfd != -1);
    if (connect_sockfd < 0)
        cout << "errno is: " << errno << endl;
    else{
        // 接受连接成功则打印出客户端的IP地址和端口号
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        string ip_str = client_ip;
        int port = ntohs(client_addr.sin_port);
        cout << "connected with ip: " << ip_str << " and port is " << port << endl;
        close(connect_sockfd); // 关闭连接套接字
    }

    close(sock);
    return 0;
}

