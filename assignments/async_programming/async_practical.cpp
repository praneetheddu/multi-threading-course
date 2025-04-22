#include <chrono>
#include <future>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

const int SENSORS = 5;
const int CYCLES = 10;          // How many telemetry updates to simulate
const auto LOOP_INTERVAL = 100ms;

// Simulate a sensor polling delay and return float value
float poll_sensor_data() {
  static thread_local std::mt19937 gen(std::random_device{}());
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);
  std::this_thread::sleep_for(5ms);
  return dist(gen);
}

// Generate telemetry packet from sensor futures
std::string generate_packet(std::vector<std::future<float>>& futures) {
  std::string packet;
  for (auto& future : futures) {
    try {
      float value = future.get();
      packet += std::to_string(value) + ", ";
    } catch (...) {
      packet += "ERROR, ";
    }
  }
  return packet;
}

int main() {
  for (int cycle = 0; cycle < CYCLES; ++cycle) {
    auto cycle_start = std::chrono::steady_clock::now();

    // Launch sensor polling asynchronously
    std::vector<std::future<float>> futures;
    for (int i = 0; i < SENSORS; ++i) {
      futures.push_back(std::async(std::launch::async, poll_sensor_data));
    }

    // Assemble the telemetry packet asynchronously
    auto packet_future = std::async(std::launch::async, generate_packet, std::ref(futures));
    std::string packet = packet_future.get();

    // Print telemetry packet
    std::cout << "[Cycle " << cycle + 1 << "] Telemetry Packet: " << packet << std::endl;

    // Sleep to maintain consistent cycle rate (e.g., 100ms per loop)
    std::this_thread::sleep_until(cycle_start + LOOP_INTERVAL);
  }

  std::cout << "Telemetry loop complete." << std::endl;
  return 0;
}
