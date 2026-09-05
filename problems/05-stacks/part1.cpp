#include <iostream>
#include <string>

constexpr int CAPACITY = 5;

class Stack {
private:
    int data[CAPACITY];

    int top;

public:
    Stack() {
        top = -1;
    }

    bool push(int value) {
        
        if (top >= (CAPACITY - 1)) {
            return false;
        }
        
        top += 1;
        data[top] = value;
        return true;
    }

    int pop() {
        if (top < 0) {
            return;
        } 
        int poppedVal = data[top];

        top -= 1;
        return;
    }

    int peak() {
        if (top < 0) {
            return;
        }

        return data[top];
    }

    bool isEmpty() {
        return top < 0;
    }

    bool isFull() {
        return top == 4;
    }
};