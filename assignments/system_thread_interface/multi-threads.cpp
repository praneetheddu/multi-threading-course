#include <iostream>
#include <thread>

// Easy Function with a argument
void print_num(int n) {
    std::cout << "Num = " << n << std::endl;
}


int main() {

    std::thread t1(print_num, 1);
    std::thread t2(print_num, 2);
    std::thread t3(print_num, 3);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}