#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx1;
std::mutex mtx2;

void printFromChild() {
    for (int i = 0; i < 10; ++i) {
        std::lock_guard<std::mutex> lock(mtx2);
        std::cout << "ƒочерний поток: строка " << i << std::endl;
        // ѕопытка заставить родительский поток выполнить работу
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int main() {
    setlocale(LC_ALL, "");
    std::thread childThread(printFromChild);

    for (int i = 0; i < 10; ++i) {
        std::lock_guard<std::mutex> lock(mtx1);
        std::cout << "–одительский поток: строка " << i << std::endl;
        // ѕопытка заставить дочерний поток выполнить работу
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    childThread.join();
    return 0;
}
