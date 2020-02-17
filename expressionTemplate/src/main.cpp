#include <iostream>
#include <chrono>

#include "Matrix.hpp"

// void benchmark01(const size_t& iter = 1000000);
// void benchmark02(const size_t& iter = 1000000);

int main(int argc, char const *argv[]) {

  std::cout << "----- Matrix class Tests -----" << std::endl;

  constexpr Matrix<int, 3, 3> md33;

  std::cout << md33 << std::endl;

  constexpr Matrix<int, 3, 3> md33_2 = md33.fill(10);

  std::cout << md33_2 << std::endl;

  constexpr auto id5 = Matrix<double, 5, 5>::Identity(); // not compile as constexpr

  std::cout << id5 << std::endl;
  
  // auto t1 = std::chrono::high_resolution_clock::now();
  // benchmark01();
  // auto t2 = std::chrono::high_resolution_clock::now();
  // benchmark02();
  // auto t3 = std::chrono::high_resolution_clock::now();

  // auto duration01 = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  // auto duration02 = std::chrono::duration_cast<std::chrono::microseconds>( t3 - t2 ).count();

  // std::cout << "benchmark 01 : " << duration01 << std::endl;
  // std::cout << "benchmark 02 : " << duration02 << std::endl;
  return 0;
}

// void benchmark01(const size_t& iter) {
//     int number = 0;
//     for(size_t i = 0; i < iter; ++i ) {
//       number = number * 45 + 2 / 8;  
//     }
// }

// void benchmark02(const size_t& iter) {
//     int number = 0;
//     for(size_t i = 0; i < iter; ++i ) {
//       number = number * number + 2 / number * 42;  
//     }
// }