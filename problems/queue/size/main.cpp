#include <iostream>
#include <queue>

int main() {
    std::queue<int> q;

    q.push(1);
    q.push(5);
    q.push(7);

    std::cout << "size " << q.size() << std::endl;

    q.pop();

    std::cout << "size after pop " << q.size() << std::endl;

    return 0;
}