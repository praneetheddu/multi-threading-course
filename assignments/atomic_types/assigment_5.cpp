#include <atomic>
#include <iostream>
#include <mutex>

class some_type {
  // ...
public:
  void do_it() { std::cout << "Do it \n"; }
};

// some_type *ptr{nullptr};            // Variable to be lazily initialized
std::atomic<some_type *> ptr = nullptr;
some_type *ptr_copy = nullptr;
std::mutex process_mutex;

void process() {
  if (!ptr) { // First check of ptr
    std::lock_guard<std::mutex> lk(process_mutex);

    if (!ptr) {
      some_type *ptr_copy = ptr;
    }
  }
  ptr_copy->do_it();
}

int main() {
  process();

  return 0;
}