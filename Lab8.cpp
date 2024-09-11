#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>
#include <conio.h>

#pragma comment(lib, "ws2_32.lib")

void error(const std::string& msg) {
    std::cerr << msg << ": " << WSAGetLastError() << std::endl;
    exit(EXIT_FAILURE);
}

void scrollOutput(const std::string& data) {
    int lines = 0;
    for (char c : data) {
        std::cout << c;
        if (c == '\n') {
            lines++;
            if (lines >= 25) {
                std::cout << "Press space to scroll down..." << std::endl;
                while (true) {
                    if (_kbhit() && _getch() == ' ') {
                        break;
                    }
                }
                lines = 0;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <URL>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string url = argv[1];
    std::string host, path;

    // Разбор URL
    size_t pos = url.find("://");
    if (pos != std::string::npos) {
        url = url.substr(pos + 3);
    }

    pos = url.find('/');
    if (pos != std::string::npos) {
        host = url.substr(0, pos);
        path = url.substr(pos);
    }
    else {
        host = url;
        path = "/";
    }

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        error("WSAStartup failed");
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        error("Socket creation failed");
    }

    struct addrinfo hints = {};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo* result;
    if (getaddrinfo(host.c_str(), "80", &hints, &result) != 0) {
        error("getaddrinfo failed");
    }

    if (connect(sock, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        freeaddrinfo(result);
        error("Connection failed");
    }
    freeaddrinfo(result);

    std::string request = "GET " + path + " HTTP/1.1\r\nHost: " + host + "\r\nConnection: close\r\n\r\n";
    send(sock, request.c_str(), request.size(), 0);

    char buffer[4096];
    std::string response;
    fd_set readfds;

    while (true) {
        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);

        // Ожидаем данных
        int activity = select(sock + 1, &readfds, nullptr, nullptr, nullptr);
        if (activity < 0) {
            error("Select error");
        }

        if (FD_ISSET(sock, &readfds)) {
            int bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
            if (bytes_received <= 0) {
                break; // Соединение закрыто или ошибка
            }
            buffer[bytes_received] = '\0';
            response.append(buffer);

            // Печатаем данные с учетом ограничения по строкам
            scrollOutput(std::string(buffer, bytes_received));
        }
    }

    closesocket(sock);
    WSACleanup();
    return EXIT_SUCCESS;
}
