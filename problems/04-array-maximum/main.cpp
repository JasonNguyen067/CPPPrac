#include <iostream>

int main() {
    int array[4];

    int key;
    std::cout << "Enter 4 values";
    for (int i = 0; i < 4; i++) {
        std::cin >> key;
        array[i] = key;
    }

    int maximum = 0;
    for (int i = 0; i < 4; i++) {
        if (array[i] > maximum) {
            maximum = array[i];
        }        
    }

    std::cout << maximum;
    return 0;
}