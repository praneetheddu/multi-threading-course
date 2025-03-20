#include <iostream>
#include <vector>
#include <thread>

const int COUNT = 100;

void fizzbuzz() {
    std::vector<std::string> kids{"Abdul", "Bart", "Claudia", "Divya"};

    for (int i = 1; i <= COUNT; i++) {
        std::cout << kids[(i - 1) % 4] << " says ";
        if (i % 3 == 0 && i % 5 == 0) {
            std::cout << "fizzbuzz!\n";
        } else if (i % 3 == 0) {
            std::cout << "fizz!\n";
        } else if (i % 5 == 0) {
            std::cout << "buzz!\n";
        } else {
            std::cout << i << "\n";
        }
    }
}


int main() {

    std::thread fizz_buzz_thread(fizzbuzz);
    fizz_buzz_thread.join();

    return 0;
}