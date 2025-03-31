#include <future>
#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono_literals;

std::mutex m;

void publisher(std::promise<std::string> &prom) {

  std::cout << "[Publisher]: Publishing data \n";
  std::string msg = "This is a shared string \n";
  std::this_thread::sleep_for(2s);
  prom.set_value(msg);
  std::cout << "[Publisher]: Data published \n";
}

void subscriber(std::future<std::string> &fut) {

  std::cout << "[Subscriber]: Getting the future \n";
  auto res = fut.get();

  std::cout << "[Subscriber]: Wait complete.\n[Subscriber]: Result is: " << res
            << std::endl;
}

void subscriber_with_shared_future(std::shared_future<std::string> &fut) {

  std::lock_guard<std::mutex> lock(m);
  std::cout << "[Subscriber]: Thread ID =  " << std::this_thread::get_id()
            << std::endl;
  std::cout << "[Subscriber]: Getting the future \n";
  auto res = fut.get();

  std::cout << "[Subscriber]: Wait complete.\n[Subscriber]: Result is: " << res
            << std::endl;
}

int main() {

  std::promise<std::string> prom;
  // std::future<std::string> fut = prom.get_future();
  // std::thread pub(publisher, std::ref(prom));
  // std::thread sub(subscriber, std::ref(fut));

  // pub.join();
  // sub.join();

  // Shared future example
  std::shared_future<std::string> shared_1 = prom.get_future();
  std::shared_future<std::string> shared_2 = shared_1;

  std::thread pub(publisher, std::ref(prom));
  std::thread sub_1(subscriber_with_shared_future, std::ref(shared_1));
  std::thread sub_2(subscriber_with_shared_future, std::ref(shared_2));

  pub.join();
  sub_1.join();
  sub_2.join();

  return 0;
}