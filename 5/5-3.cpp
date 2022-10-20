#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

using namespace std;

static bool stop = false;

// SIGTERM信号的处理函数，触发时结束主程序中的循环
static void handle_term(int sig){
    stop = true;
}

// 接收3个参数：IP地址、端口号、backlog值
// argv第一个参数一定会是程序的名称
int main(int argc, char* argv[]){
    signal(SIGTERM, handle_term); //收到kill信号时，执行handle函数
    if(argc <= 3){
        cout << "usage: " << argv[0] << "ip_address port_number backlog" << endl;
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);
    int backlog = atoi(argv[3]);

    // 创建socket
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0); //成功创建则返回一个socket文件描述符，失败则返回-1

    // 创建一个IPv4地址
    struct sockaddr_in my_sock_addr; // IPv4专用地址
    bzero(&my_sock_addr, sizeof(my_sock_addr)); //将socket套接字清零
    my_sock_addr.sin_family = AF_INET; // 地址族
    my_sock_addr.sin_port = htons(port); // 端口号,转化为网络字节序
    inet_pton(AF_INET, ip, &my_sock_addr.sin_addr); //将IP地址转化为网络地址，是大端的

    // 绑定socket
    int ret = bind(sock, (struct sockaddr *) &my_sock_addr, sizeof(my_sock_addr)); //第二项要强制转换通用sockaddr
    assert(ret != -1); // 绑定失败返回-1

    // 监听
    ret = listen(sock, backlog);
    assert(ret != -1);

    // 循环等待连接，直到有SIGTERM信号将其中断
    while(!stop){
        sleep(1); 
    }

    // 关闭socket
    close(sock);
    return 0;
}

