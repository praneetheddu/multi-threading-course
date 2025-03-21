#include <exception>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex m;

// Bad function example since it will throw an exception without unlocking the mutex
void throw_exception() {

    try {
        m.lock();
        throw std::exception();
        m.unlock();
    } catch (std::exception e) {
        std::cout << "Exception";
    }
}

void mutex_lock_func() {

    try {
        std::cout << "Locking Mutex \n";
        std::lock_guard<std::mutex> lock(m);
        std::cout << "Throwing Exception\n";
        throw std::exception();
    } catch (...) {
        std::cout << "Exception caught\n";
    }
}

int main() {

    // std::thread t(throw_exception);
    // std::thread t2(throw_exception);
    // std::thread t3(throw_exception);

    std::thread t(mutex_lock_func);
    std::thread t2(mutex_lock_func);
    std::thread t3(mutex_lock_func);


    t.join();
    t2.join();
    t3.join();

    return 0;
}