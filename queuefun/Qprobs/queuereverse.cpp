#include <queue>
#include <iostream>
#include <stack>

void reverseQueue(std::queue<int>& q) {
    std::stack<int> stack;

    while (!q.empty()) {
        stack.push(q.front());
        q.pop();
    }

    while (!stack.empty()) {
        q.push(stack.top());
        stack.pop();
    }

}

int main() {
    std::queue<int> queueHolder;

    queueHolder.push(1);
    queueHolder.push(2);
    queueHolder.push(3);
    queueHolder.push(4);
    queueHolder.push(5);

    reverseQueue(queueHolder);

    for (int i = 0; i < queueHolder.size(); i++) {
        std::cout << queueHolder.front() << std::endl;
        queueHolder.pop();
    }

    return 0;
}