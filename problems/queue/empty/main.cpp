#include <iostream>
#include <queue>

int main() {
    std::queue<int> q;

    if (q.empty()) {
        std::cout << "Queue is empty " << std::endl;
    }

    q.push(2);

    if (!q.empty()) {
        std::cout << "Queue not empty cuh " << std::endl;
    }

    return 0;
}