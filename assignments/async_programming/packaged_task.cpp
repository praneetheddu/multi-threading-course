#include <future>
#include <iostream>
#include <thread>

using namespace std::literals;

int main() {

  std::packaged_task<int(int, int)> add_fn([](int a, int b) {
    std::this_thread::sleep_for(
        1s); // Demonstrate whether it's doing sync or async call
    int res = a + b;
    std::cout << "Result = " << res << std::endl;
    return res;
  });

  // Sync packaged task call
  std::cout << "Calling sync packaged task\n";
  auto future = add_fn.get_future();

  add_fn(2, 3); // Synchronous call
  std::cout << "I'm in main after the call\n";
  std::cout << "waiting for packaged_task : " << future.get() << std::endl;

  // Async packaged task call
  add_fn.reset(); // reset the future
  auto async_future = add_fn.get_future();
  std::thread thr(std::move(add_fn), 2, 3); // Async call

  std::cout << "I'm in main after the call\n";
  std::cout << "waiting for packaged_task : " << async_future.get()
            << std::endl;

  thr.join();
}
