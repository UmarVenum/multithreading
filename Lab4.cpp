#include <iostream>
#include <thread>
#include <chrono>

void printLines() {
    for (int i = 0; i < 10; ++i) {
        std::cout << "Дочерний поток: строка " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    setlocale(LC_ALL, "");
    std::thread childThread(printLines);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // Здесь мы просто завершаем поток, используя detach вместо cancel
    if (childThread.joinable()) {
        std::cout << "Родительский поток завершает дочерний поток." << std::endl;
        childThread.detach();
    }
    return 0;
}
