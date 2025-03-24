#include <iostream>
#include <mutex>
#include <thread>


using namespace std::chrono_literals;
std::mutex mutex1;
std::mutex mutex2;

// Deadlock example w thread1
// void thread_1() {

//     mutex1.lock();
//     std::this_thread::sleep_for(100ms);
//     mutex2.lock();
//     mutex1.unlock();
//     mutex2.unlock();
//     std::cout << "Done with thread 1 \n";

    
// }

// // Deadlock example w thread2
// void thread_2() {

//     mutex2.lock();
//     std::this_thread::sleep_for(100ms);
//     mutex1.lock();
//     mutex2.unlock();
//     mutex1.unlock();
//     std::cout << "Done with thread 2 \n";
// }


// Avoiding Deadlock example w thread1
void avoid_deadlock_thread_1() {

    mutex1.lock();
    mutex2.lock();
    std::this_thread::sleep_for(100ms);
    mutex1.unlock();
    mutex2.unlock();
    std::cout << "Done with avoid_deadlock_thread_1 \n";

    
}

// Avoiding Deadlock example w thread1
void avoid_deadlock_thread_2() {

    mutex1.lock();
    mutex2.lock();
    std::this_thread::sleep_for(100ms);
    mutex2.unlock();
    mutex1.unlock();
    std::cout << "Done with avoid_deadlock_thread_2 \n";
}



// Scoped Lock  example w thread1
void scoped_lock_thread_1() {

    std::scoped_lock scoped_lock(mutex1, mutex2);
    std::this_thread::sleep_for(100ms);
    mutex1.unlock();
    mutex2.unlock();
    std::cout << "Done with avoid_deadlock_thread_1 \n";

    
}

// Avoiding Deadlock example w thread1
void scoped_lock_thread_2() {

    std::scoped_lock scoped_lock(mutex1, mutex2);
    mutex1.lock();
    mutex2.lock();
    std::this_thread::sleep_for(100ms);
    mutex2.unlock();
    mutex1.unlock();
    std::cout << "Done with avoid_deadlock_thread_2 \n";
}



int main() {

    // std::cout << "Deadlock example \n";

    // std::thread t1(thread_1);
    // std::thread t2(thread_2);

    // t1.join();
    // t2.join();


    std::cout << "Avoiding Deadlock example \n";

    std::thread t1(scoped_lock_thread_1);
    std::thread t2(scoped_lock_thread_2);

    t1.join();
    t2.join();

    return 0;
}