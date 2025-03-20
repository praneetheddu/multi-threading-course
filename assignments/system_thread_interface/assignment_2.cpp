#include <iostream>
#include <thread>

int value = 0;

void increment_value() {
    for (int i = 0; i < 100000; i++) {
        value++;
    }
}

int main() {

    std::thread t1(increment_value);
    std::thread t2(increment_value);
    std::thread t3(increment_value);


    t1.join();
    t2.join();
    t3.join();
    std::cout << "Final Value = " << value << std::endl;

    return 0;

}