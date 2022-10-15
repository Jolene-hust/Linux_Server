// client send message

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv){
    if (argc <= 2){
        cout << "usage: " << argv[0] << "server ip_address and port_number" << endl;
        return 1;
    }

    // connect socked
    int connect_sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(connect_sock >= 0);

    const char* server_ip = argv[1];
    int port = atoi(argv[2]);

    //server socket addr
    struct sockaddr_in server_sock_addr;
    bzero(&server_sock_addr, sizeof(server_sock_addr));
    server_sock_addr.sin_family = AF_INET;
    server_sock_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &server_sock_addr.sin_addr);

    // connect 
    int ret = connect(connect_sock, (struct sockaddr *)&server_sock_addr, sizeof(server_sock_addr));
    if (ret < 0)
        cout << "connect failed" << endl;
    else{
        const char* oob_data = "abc";
        const char* normal_data = "123";
        send(connect_sock, normal_data, strlen(normal_data), 0);
        send(connect_sock, oob_data, strlen(oob_data), MSG_OOB);
        send(connect_sock, normal_data, strlen(normal_data), 0);
    }
    close(connect_sock);
    return 0;
}