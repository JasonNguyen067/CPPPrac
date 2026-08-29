#include <queue>
#include <iostream>
#include <string>

std::queue<std::string> binaryCreator(int& n) {
    std::queue<std::string> tempQueue;
    std::queue<std::string> results;

    tempQueue.push("1");

    for (int i = 0; i < n; i++) {
        std::string current = tempQueue.front();
        tempQueue.pop();

        results.push(current);

        tempQueue.push(current + "0");
        tempQueue.push(current + "1");
    }

    return results;
    
}

int main() {
    int numbers = 5;
    std::queue<std::string> answer = binaryCreator(numbers);

    while (!answer.empty()) {
        std::cout << answer.front();
        answer.pop();
    }

    return 0;

}

// look back at this soon