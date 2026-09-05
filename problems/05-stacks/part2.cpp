#include <iostream>
#include <stack>
#include <string>

std::string stackReverser(std::string reverseVictim) {
    std::stack<char> OriginalValue;
    std::string result = "";
    for (int i = 0; i < reverseVictim.length(); i++) {
        OriginalValue.push(reverseVictim[i]);
    }

    while (!OriginalValue.empty()) {
        result.push_back(OriginalValue.top());
        OriginalValue.pop();
    }

    return result;
}

int main() {}