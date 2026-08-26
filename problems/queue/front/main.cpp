#include <iostream>
#include <queue>

int main() {
    std::queue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);

    std::cout << "front element" << q.front() << std::endl;

    return 0;
}

// no note needed