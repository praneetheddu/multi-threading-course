#include <future>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;


void add_fn(int a, int b, std::promise<int>& result) {
    std::cout << "Adding operation pending ... \n";
    std::this_thread::sleep_for(5s);
    std::cout << "Setting the Result ... \n";
    result.set_value(a + b);
    std::cout << "Result set \n";
}


void print_result(std::future<int>& res) {

    std::cout << "Waiting for result ... \n";
    int res_int = res.get();
    std::cout << "Result acquired, value = " << res_int << std::endl;
}


int main() {

    std::promise<int> result;

    std::future<int> fut = result.get_future();

    std::thread add_thread(add_fn, 2 ,3 , std::ref(result));

    std::thread print_thread(print_result, std::ref(fut));

    add_thread.join();
    print_thread.join();
 
    return 0;
}