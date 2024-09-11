#include <iostream>
#include <thread>
#include <vector>

void printLines(int id) {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Поток " << id << ": строка " << i << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "");
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(printLines, i);
    }
    for (auto& t : threads) {
        t.join();
    }
    return 0;
}
