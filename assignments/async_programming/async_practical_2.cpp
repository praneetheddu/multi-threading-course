#include <future>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

const int NUM_IMAGES = 10;

using namespace std::chrono_literals;

float process_image(int i) {
  // std::lock_guard<std::mutex> lock(mtx);
  std::cout << "Processing Image " << i << " ... \n";
  thread_local std::mt19937 mt(std::random_device{}());
  std::uniform_real_distribution<float> dist(0.0, 1.0);

  // return processing score
  std::this_thread::sleep_for(300ms);
  return dist(mt);
}

float calculate_average_score(std::vector<std::future<float>> &futures) {

  float avg_score{0.0};
  int count = 0;
  for (auto &future : futures) {
    avg_score += future.get();
    count++;
  }

  return avg_score / static_cast<float>(count);
}

int main() {

  std::vector<std::future<float>> futures;
  for (int i = 0; i < NUM_IMAGES; i++) {
    futures.push_back(std::async(std::launch::async, process_image, i));
  }

  // calculate_average_score(futures);

  auto calc_average_score_future = std::async(
      std::launch::async, calculate_average_score, std::ref(futures));

    auto score = calc_average_score_future.get();
  std::cout << "Processing score = " << score
            << std::endl;

  return 0;
}
