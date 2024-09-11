#include <iostream>
#include <thread>

void printLines() {
    for (int i = 0; i < 10; ++i) {
        std::cout << "Дочерний поток: строка " << i << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "");
    std::thread childThread(printLines);
    childThread.join();
    for (int i = 0; i < 10; ++i) {
        std::cout << "Родительский поток: строка " << i << std::endl;
    }
    return 0;
}
