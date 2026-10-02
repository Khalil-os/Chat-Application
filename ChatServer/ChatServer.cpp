#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")
#define backlog 5

using namespace std;

int main()
{
    WSADATA wsaData;

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0)
    {
        cout << "WSAStartup failed!" << endl;
        return 1;
    }
    cout << "Winsock initialized successfully!" << endl;

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET)
    {
        cout << "Socket failed!" << endl;
        WSACleanup();
        return 1;
    }
    cout << "socket initialized successfully!" << endl;
    
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    
    if (bind(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        cout << "Bind failed !" << endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    cout << "Bind initialized successfully!" << endl;

    if (listen(sock, backlog) == SOCKET_ERROR)
    {
        cout << "Listen failed !" << endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    cout << "Listen initialized successfully!" << endl;

    sockaddr_in clientAddr{};

    int clientAddrSize = sizeof(clientAddr);
    SOCKET clientSocket = accept(sock, (sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Client Socket failed!" << endl;
        WSACleanup();
        closesocket(sock);
        return 1;
    }

    closesocket(sock);
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}