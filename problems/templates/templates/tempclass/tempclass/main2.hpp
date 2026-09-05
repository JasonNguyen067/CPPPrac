#include <iostream>
#include <string>


template<typename T>
class SweInternship {
private:
    T internships;
    T pay;
public:
    SweInternship(T number, T hourly) : internships(number), pay(hourly) {}

    void displayInternshipAmount() const {
        std::cout << "You've done a total of " << internships << " internships!" << std::endl;
    }

    T displayPay() const;
};

template<typename T>
T SweInternship<T>::displayPay() const {
    return pay;
}

int main() {
    SweInternship<int> yuh(5, 60);
    yuh.displayPay();
}