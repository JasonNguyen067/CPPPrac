#include <iostream>

int main() {
    int hashTable[10];

    for (int i = 0; i < 10; i++) {
        hashTable[i] = -1;
    }

    int key;
    std::cout << "Input 5 keys";
    for (int i = 0; i < 5; i++) {
        std::cin >> key;
        int hash = key % 10;
        hashTable[hash] = key;
    }

    for (int i = 0; i < 10; i++) {
        std::cout << hashTable[i];
    }

    return 0;
}