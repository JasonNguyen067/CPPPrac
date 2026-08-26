#include <iostream>
#include <queue>

int main() {
    std::queue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);

    // lets look at the back so rn it looks like [1, 2, 3]

    std::cout << "This is the back value " << q.back() << std::endl;
    // expected 3
    
    return 0;
}

// o(1) looking at back cuz theres a pointer there