#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>

std::string firstNonRepeatingStream(std::string& stream) {
    std::queue<char> q;
    std::unordered_map<char, int> charTracker;
    std::string result = "";

    for (char letter : stream) {
        charTracker[letter] += 1;

        q.push(letter);

        while (!q.empty() && charTracker[letter] > 1) {
            q.pop();
        }

        if (!q.empty()) {
            result += q.front();
        } else {
            result += "#";
        }

        result += " ";

        if (!result.empty()) {
            result.pop_back();
        }

        return result;

        
    }
}


int main() {
    // Scenario 2 stream that produces your exact expected output
    std::string stream = "acdabc"; 
    std::cout << "Input:  " << stream << std::endl;
    std::cout << "Output: " << firstNonRepeatingStream(stream) << std::endl;
    
    return 0;
}

// output for aabbcd would be
// a # b # c c