#include <iostream>

struct Node {
    int key;
    Node* next;
};

class HashTable {
private: 
    Node* table[10];
public: 
    HashTable() {
        for (int i = 0; i < 10; i++) {
            table[i] = nullptr;
        }
    }

    int hashFunction(int key) {
        return key % 10;
    }

    void insert(int key) {
        int index = hashFunction(key);

        Node* newNode = new Node;
        newNode->key = key;
        newNode->next = table[index];
        table[index] = newNode;
    }

    void display() {
        for (int i = 0; i < 10; i++) {
            Node* curr = table[i];
            while (curr != nullptr) {
                std::cout << curr->key;
                curr = curr->next;
            }
        }
    }

    bool search(int key) {
        int index = hashFunction(key);
        for (int i = 0; i < 10; i++) {
            Node* curr = table[index];

            while (curr != nullptr) {
                if (curr->key == key) {
                    return true;
                }
                curr = curr->next;
            }
            return false;
        }
    }

    bool remove(int key) {
        int index = hashFunction(key);
        Node* curr = table[index];
        Node* prev = nullptr;

        while (curr != nullptr) {
            if (curr->key = key) {
                if (prev == nullptr) {
                    table[index] = curr->next;
                } else {
                    prev->next = curr->next;
                }
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }
};

int main() {
    HashTable ht;

    // Part A: all three of these collide at index 2.
    ht.insert(12);
    ht.insert(22);
    ht.insert(32);

    std::cout << "--- after inserts ---\n";
    ht.display();

    // Part B: 22 should now be findable - the bug from Problem 02 is fixed.
    std::cout << "\nsearch(22): " << ht.search(22) << "  (expect 1)\n";
    std::cout << "search(99): " << ht.search(99) << "  (expect 0)\n";

    // Part C: remove from the middle of a chain, then from the head.
    ht.remove(22);
    ht.remove(99);   // not present - must be safe
    std::cout << "\n--- after remove(22) ---\n";
    ht.display();
    std::cout << "\nsearch(22): " << ht.search(22) << "  (expect 0)\n";

    // Part D: when ht goes out of scope here, its destructor must free
    // the nodes still holding 32 and 12.
    return 0;
}
