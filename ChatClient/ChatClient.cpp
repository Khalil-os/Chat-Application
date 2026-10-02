#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

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

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Socket failed!" << endl;
        WSACleanup();
        return 1;
    }
    cout << "socket initialized successfully!" << endl;
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    if (InetPtonA(AF_INET, "127.0.0.1", &serverAddr.sin_addr) != 1)
    {
        cout << "Inet Pton failed!" << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) != 0)
    {
        cout << "Connect failed!" << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    cout << "Connect initialized successfully!" << endl;

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}