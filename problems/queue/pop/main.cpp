#include <iostream>
#include <queue>

int main() {
    std::queue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);

    std::cout << "front before pop " << q.front() << std::endl;

    q.pop();

    std::cout << "front after pop " << q.front();

    return 0;
}

// Important to remember but it removes on pop, does not return on pop