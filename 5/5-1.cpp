#include <iostream>
// #include <stdio.h>
#include <netinet/in.h>
#include <bits/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>

using namespace std;

// union TESTU
// {
//     short value;
//     char union_types[2];
// };

// 判断字节序是大端还是小端
void byteorder(){
    union TESTU{
        short value;
        char union_types[2];
    };
    
    TESTU test_byteorder;
    test_byteorder.value = 0x0102;
    cout << test_byteorder.union_types[0] << endl;
    if (test_byteorder.union_types[0] == 1 && test_byteorder.union_types[1] == 2)
    {
        // 低地址存1，高地址存2
        cout << "低字节对应高地址，这是大端字" << endl;
    }
    else if (test_byteorder.union_types[0] == 2 && test_byteorder.union_types[1] == 1)
    {
        // 低地址存2，高地址存1
        cout << "低字节对应低地址，这是小端字" << endl;
    }
    else
        cout << "Error!" << endl;
}
