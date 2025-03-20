#include <exception>
#include <iostream>
#include <thread>

class ThreadWrapper {

public:
  std::thread thr;
  explicit ThreadWrapper(std::thread &&thr) : thr(std::move(thr)) {};
  ThreadWrapper(const ThreadWrapper &other) = delete;
  ThreadWrapper &operator=(const ThreadWrapper &other) = delete;

  ~ThreadWrapper() {
    std::cout << "Destructing the thread \n";
    if (thr.joinable()) {
      thr.join();
    }
    std::cout << "Thread destructed \n";
  }
};

void hello() {
  std::this_thread::sleep_for(std::chrono::seconds(4));
  std::cout << "Slept for 5 seconds \n";
}

int main() {
  std::thread thr(hello);

  ThreadWrapper tw(std::move(thr));
  try {
    throw std::exception();
  } catch (std::exception &e) {
    std::cout << "Exception caught, Exiting ...\n";
  }

  return 0;
}
