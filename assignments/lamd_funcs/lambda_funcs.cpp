#include <iostream>
#include <vector>

void sample_lambda_func() {

  std::vector<int> vec(5, 10);

  // print each element
  for (const auto &elem : vec) {
    std::cout << elem << ", ";
  }
  std::cout << "\n";

  // Create an inline lambda to display size
  auto show_size = [&]() {
    std::cout << "Size of vec from show_size function = " << vec.size() << "\n";
  };

  // Invoke
  show_size();

  // Create lambda with move
  auto move_vec_and_disp_size = [vec_int = std::move(vec)]() {
    std::cout << "Size of vec from move_vec_and_disp_size function = "
              << vec_int.size() << "\n";
  };

  // Invoke
  move_vec_and_disp_size();

  // Check the original size of the vector after moving
  show_size();
}

int main() {
  sample_lambda_func();
  return 0;
}