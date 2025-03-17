#include <thread>
#include <iostream>



// Standard callable function
void hello() {

    std::cout <<  "Hello! \n";
}

// Functor example

class Func {
    public:
    void operator()() {
        std::cout << "Hello From () operator \n";
    }
};

int main() {

    std::thread t1(hello);
    
    // Wait to finish
    t1.join();

    // Functor example
    Func func;
    
    std::thread t2(func);
    t2.join();

    // Lambda expression example
    int k = 0;
    std::thread t3([&]() {
        std::cout << "Hello from lambda \n";
        for (int i = 0; i < 20; i++) {
            k++;
        }
    });
    t3.join();
    std::cout << "Value of k " << k << "\n";
    return 0;
}