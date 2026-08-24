#include <iostream>

// Problem: fixed-size array-backed queue (capacity 5)
//
// Implement enqueue, dequeue and isEmpty. isFull is given to you as a hint --
// it tells you what convention rearIdx is expected to follow.
//
// Conventions to hold onto:
//   frontIdx = index of the first element
//   rearIdx  = index of the LAST element (not one past it)
//   an empty queue is frontIdx > rearIdx
class Queue {
public:
    static constexpr int CAPACITY = 5;

    Queue() = default;

    // Add value to the back of the queue.
    // On a full queue: print an error to std::cerr and discard the value.
    // Never write outside data[].
    void enqueue(int value) {
        // TODO
        (void)value;
    }

    // Remove AND return the front element.
    // On an empty queue: print an error to std::cerr and return -1,
    // leaving frontIdx and rearIdx untouched.
    int dequeue() {
        // TODO
        return -1;
    }

    bool isEmpty() const {
        // TODO
        return true;
    }

    bool isFull() const { return rearIdx == CAPACITY - 1; }

private:
    int data[CAPACITY];   // left uninitialized on purpose -- no slot is ever
                          // read before it has been written
    int frontIdx = 0;
    int rearIdx = -1;
};

int main() {
    std::cout << "--- Part 1: basics ---" << std::endl;

    Queue q;
    std::cout << "isEmpty: " << q.isEmpty() << "  (expect 1)" << std::endl;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    std::cout << "enqueued 10 20 30" << std::endl;
    std::cout << "isEmpty: " << q.isEmpty() << "  (expect 0)" << std::endl;

    std::cout << "dequeue: " << q.dequeue() << "  (expect 10)" << std::endl;
    std::cout << "dequeue: " << q.dequeue() << "  (expect 20)" << std::endl;
    std::cout << "dequeue: " << q.dequeue() << "  (expect 30)" << std::endl;
    std::cout << "isEmpty: " << q.isEmpty() << "  (expect 1)" << std::endl;

    std::cout << std::endl << "--- Part 2: the edge cases ---" << std::endl;
    std::cout << "dequeue on empty: " << q.dequeue() << "  (expect -1)" << std::endl;

    Queue q2;
    for (int i = 1; i <= 5; i++) {
        q2.enqueue(i);
    }
    std::cout << "filled with 1..5, isFull: " << q2.isFull() << "  (expect 1)" << std::endl;
    std::cout << "enqueue 6 on a full queue -- value is discarded" << std::endl;
    q2.enqueue(6);

    std::cout << std::endl << "--- Part 3: the flaw ---" << std::endl;
    std::cout << "dequeue: " << q2.dequeue() << "  (expect 1)" << std::endl;
    std::cout << "dequeue: " << q2.dequeue() << "  (expect 2)" << std::endl;
    std::cout << "two slots are free at the front, but enqueue 7 still fails:" << std::endl;
    q2.enqueue(7);
    std::cout << "isFull: " << q2.isFull() << "  (expect 1 -- and that is the flaw)" << std::endl;

    return 0;
}
