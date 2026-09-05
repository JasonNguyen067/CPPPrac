#include <iostream>
#include <string>

template <typename T>
T findMax(T val1, T val2) {
    if (val1 > val2) {
        return val1;
    } 

    return val2;
}

int main() {
    int val2 = 3;
    int val5 = 6;

    std::string answer = std::to_string(findMax(val2, val5));
    std::cout << "Larger val is " << answer << std::endl;

    std::string interesting = "hello";
    std::string bruh = "letter";
    std::string hello = findMax(interesting, bruh);
    std::cout << "higher lexicograph word is " << hello << std::endl;

    return 0;
}

// lexicographic order aka word / letter comparison, works like this internally
// if first char match go onto next char
// larger letter higher value than the smaller letteres

