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

    int hash_key;
    std::cout << "Key";
    std::cin >> hash_key;
    int index;
    for (int i = 0; i < 10; i++) {
        if (hashTable[i] == hash_key) {
            index = i;
        }
    }   

    if (index) {
        std::cout << "Key " << hash_key << " found at index " << index; 
    }

    return 0;
}