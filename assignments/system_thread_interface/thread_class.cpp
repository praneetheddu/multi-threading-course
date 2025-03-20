#include <chrono>
#include <csignal>
#include <exception>
#include <iostream>
#include <thread>

// Passing in thread as rvalue
void wait_for_thread_to_finish(std::thread &&thr) {

  if (thr.joinable()) {
    thr.join();
  }
  std::cout << "Thread has executed succesfully!";
}

// Exceptions should be handled inside the thread or else the program will terminate
void exception_handling_thread() {
    try {
        throw std::exception();
    }
    catch (std::exception& e) {
        std::cout << "\nHandle Exception Here \n";
    } 
}


int main() {
  std::thread thr([]() {
    const int sleep_seconds = 5;
    std::cout << "Sleeping for " << sleep_seconds << " seconds \n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Hello from lambda thread \n";
  });

  wait_for_thread_to_finish(std::move(thr));

  std::thread exception_thr(exception_handling_thread);
  exception_thr.join();


  return 0;
}