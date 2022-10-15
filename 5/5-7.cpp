// server receive message
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <errno.h>

using namespace std;

const int BUF_SIZE = 1024;

int main(int argc, char* argv[]){
    if (argc <= 2)
    {
        cout << "usage: " << argv[0] << "server ip_address and port_number" << endl;
        return 1;
    }
    const char* server_ip = argv[1];
    int port = atoi(argv[2]);

    // create server socket
    int server_socket = socket(PF_INET, SOCK_STREAM, 0);
    assert(server_socket >= 0);

    // create server socket address
    struct sockaddr_in server_sock_addr;
    bzero(&server_sock_addr, sizeof(server_sock_addr));
    server_sock_addr.sin_family = AF_INET;
    server_sock_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &server_sock_addr.sin_addr);

    // bind
    int ret = bind(server_socket, (struct sockaddr *)&server_sock_addr, sizeof(server_sock_addr));
    assert(ret != -1);

    // listen
    ret = listen(server_socket, 5);
    assert(ret != -1);;

    // accept client connect
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int connect_sock = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    if (connect_sock < 0){
        cout << "errno is " << errno << endl;
    }
    else{
        char* buffer = new char[BUF_SIZE];
        memset(buffer, '\0', BUF_SIZE);
        ret = recv(connect_sock, buffer, BUF_SIZE-1, 0);
        cout << "got " << ret << "bytes of normal data " << buffer << endl;

        memset(buffer, '\0', BUF_SIZE);
        ret = recv(connect_sock, buffer, BUF_SIZE-1, MSG_OOB);
        cout << "got " << ret << "bytes of oob data " << buffer << endl;

        memset(buffer, '\0', BUF_SIZE);
        ret = recv(connect_sock, buffer, BUF_SIZE-1, 0);
        cout << "got " << ret << "bytes of normal data " << buffer << endl;

        close(connect_sock);
    }
    close(server_socket);
    return 0;
    
}