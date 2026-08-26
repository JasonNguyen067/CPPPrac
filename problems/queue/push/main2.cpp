#include <iostream>
#include <queue>

int main() {
    std::queue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);

    const std::size_t queueSize = q.size();

    for (int i = 0; i < queueSize; i++) {
        std::cout << q.front();
        q.pop();
    }

    return 0;
}

// We have to do this method because a queue doesn't let you access
// or have implementation to just print the q under the hood 