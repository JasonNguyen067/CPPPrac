#include <stack>
#include <iostream>

class myQueue {
    std::stack<int> s1, s2;
public:
    void enqueue(int val) {
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }

        s1.push(val);

        while (!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }

    }

    void dequeue() {
        if (s1.empty()) {
            return;
        }

        s1.pop();
        
    }

    int front() {
        if (s1.empty()) {
            return -1;
        }

        return s1.top();
    }

    int size() const {
        return s1.size();
    }



};

int main() {

    myQueue Bruh;

    Bruh.enqueue(1);
    Bruh.enqueue(2);
    Bruh.enqueue(3);

    std::cout << Bruh.front() << std::endl;

    std::cout << Bruh.size() << std::endl;

    Bruh.dequeue();
    
    std::cout << Bruh.front() << std::endl;
    std::cout << Bruh.size() << std::endl;

    return 0;
}