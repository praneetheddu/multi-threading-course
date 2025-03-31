#include <condition_variable>
#include <iostream>
#include <shared_mutex>
#include <string>
#include <thread>

using namespace std;
using namespace std::chrono;

// Global variables
mutex mut;
string sdata{"Empty"};
bool is_write_complete{false};

// Waiting thread
void reader() {

  while (!is_write_complete) {
    std::cout << "Waiting for writer to complete \n";
    std::this_thread::sleep_for(500ms);
  }
  cout << "Data is " << sdata << endl; // Wake up and use the new value
}

// Modyifing thread
void writer() {
  cout << "Writing data..." << endl;
  {
    is_write_complete = false;
    lock_guard<std::mutex> lg(mut);  // Acquire lock
    std::this_thread::sleep_for(2s); // Pretend to be busy...
    sdata = "Populated";             // Modify the data
    is_write_complete = true;
    std::cout << "Write compelte \n";
  }
}

int main() {
  cout << "Data is " << sdata << endl;
  thread read{reader};
  thread write{writer};
  /*
  // If the writer thread finishes before the reader thread starts, the
  notification is lost thread write{writer}; std::this_thread::sleep_for(500ms);
  thread read{reader};
  */
  write.join();
  read.join();
}