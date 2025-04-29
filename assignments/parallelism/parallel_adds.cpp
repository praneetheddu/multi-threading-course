#include <algorithm>
#include <chrono>
#include <ctime>
#include <future>
#include <iostream>
#include <numeric>
#include <random>

using namespace std::chrono_literals;

std::mt19937 mt_random;
std::uniform_real_distribution<float> dist(0, 1);

float accumulate(float *start, float *end) {
  return std::accumulate(start, end, 0.0);
}

float calc_sum(std::vector<float> &arr, const int num_jobs) {

  auto start_arr = &arr[0];
  const auto arr_size = arr.size();
  std::vector<std::future<float>> futures{};

  for (int i = 0; i < num_jobs; i++) {
    futures.push_back(std::async(
        std::launch::async, accumulate, start_arr + (i * (arr_size / num_jobs)),
        start_arr - 1 + ((i + 1) * (arr_size / num_jobs))));
  }

  float sum;
  for (auto &fut : futures) {
    sum += fut.get();
  }

  return sum;
}

int main() {

  auto start_time = std::chrono::steady_clock::now();

  mt_random.seed(time(nullptr));
  std::vector<float> randos(20'000);
  std::generate(randos.begin(), randos.end(),
                [&randos]() { return 25.0; });

  auto end_time = std::chrono::steady_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

  std::cout << "Sum of the randos are : " << calc_sum(randos, 200)
            << " , duration = " << duration.count() << " ms" << std::endl;

  return 0;
}
