#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

std::atomic<bool> running(true);

void printLines() {
    for (int i = 0; i < 10; ++i) {
        if (!running) {
            std::cout << "Дочерний поток завершает работу." << std::endl;
            return;
        }
        std::cout << "Дочерний поток: строка " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    setlocale(LC_ALL, "");
    std::thread childThread(printLines);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Устанавливаем флаг для завершения потока
    running = false;
    childThread.join(); // Ожидаем завершения дочернего потока

    return 0;
}
