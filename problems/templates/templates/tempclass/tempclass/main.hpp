#include <iostream>
#include <string>


template <typename T>
class Box {

private:
    int data;
public:
    Box(T value) : data(value) {}

    void displayData() const {
        std::cout << "Data is " << data;
    }

    T getData() const;

};

template <typename T>
T Box<T>::getData() const {
    return data;
}



int main() {
    Box<int> Box1(500);

    Box1.displayData();

    Box<std::string> StringBox("Salutations");
    StringBox.displayData();


    return 0;

}