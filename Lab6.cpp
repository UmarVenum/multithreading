#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool parentTurn = true;

void printLines() {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !parentTurn; });
        std::cout << "Дочерний поток: строка " << i << std::endl;
        parentTurn = true;
        cv.notify_one();
    }
}

int main() {
    setlocale(LC_ALL, "");
    std::thread childThread(printLines);

    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return parentTurn; });
        std::cout << "Родительский поток: строка " << i << std::endl;
        parentTurn = false;
        cv.notify_one();
    }

    childThread.join();
    return 0;
}
