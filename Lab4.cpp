#include <iostream>
#include <thread>
#include <chrono>

void printLines() {
    for (int i = 0; i < 10; ++i) {
        std::cout << "�������� �����: ������ " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    setlocale(LC_ALL, "");
    std::thread childThread(printLines);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // ����� �� ������ ��������� �����, ��������� detach ������ cancel
    if (childThread.joinable()) {
        std::cout << "������������ ����� ��������� �������� �����." << std::endl;
        childThread.detach();
    }
    return 0;
}
