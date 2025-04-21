#include <future>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

void hello_async() { std::cout << "Hello \n"; }

unsigned long long fib(int n) {
  if (n <= 1)
    return 1;
  return fib(n - 1) + fib(n - 2);
}

int main() {

  auto func_fut = std::async(fib, 50);

  while (func_fut.wait_for(1s) != std::future_status::ready) {
    std::this_thread::sleep_for(1ms);
    std::cout << "Waiting for result \n";
  }

  std::cout << "result = " << func_fut.get() << std::endl;

  return 0;
}