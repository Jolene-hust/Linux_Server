#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

using namespace std;

int main(int argc, char* argv[]){
    if (argc <= 2)
    {
        cout << "usage: " << argv[0] << "ip_address and port_number" << endl;
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    int server_sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(server_sock >= 0);

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    int ret = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    assert(ret != -1);

    ret = listen(server_sock, 5);
    assert(ret != -1);

    struct sockaddr_in  client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int connect_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_len);
    
    if(connect_sock < 0){
        cout << "errno is " << errno << endl;
    }
    else{
        close(STDOUT_FILENO); //关闭标准输出，文件描述符为1
        dup(connect_sock); //也就是说将标准输出变成了connect_sock这一网络连接
        cout << "This is STDOUT!" << endl;
        close(connect_sock);
    }
    close(server_sock);
    return 0;
}