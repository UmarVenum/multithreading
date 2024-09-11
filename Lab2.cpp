#include <iostream>
#include <thread>

void printLines() {
    for (int i = 0; i < 10; ++i) {
        std::cout << "�������� �����: ������ " << i << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "");
    std::thread childThread(printLines);
    childThread.join();
    for (int i = 0; i < 10; ++i) {
        std::cout << "������������ �����: ������ " << i << std::endl;
    }
    return 0;
}
