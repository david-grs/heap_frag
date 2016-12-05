#include "chrono.h"
#include <mtrace>

#include <unordered_map>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <iostream>

#include <malloc.h>

int main()
{
  static constexpr const int Iterations = 4e6;

  {
    std::unordered_map<int, double> um;
    std::map<int, double> m, m2;
    std::vector<std::string> vs, vs2;

    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < Iterations; ++i)
      um.emplace(i, i);
    auto end = std::chrono::system_clock::now();

    for (int i = 0; i < Iterations; ++i)
    {
      m.emplace(i, i);
      m2.emplace(i, i);
      vs.emplace_back('c', (i % 10000));
      vs2.emplace_back('c', (i % 10000));
    }

    std::cout << (m.size() + m2.size() + um.size() + vs.size() + vs2.size()) << std::endl;
    std::cout << (end - start).count() << std::endl;
    //std::cout << "after use" << std::endl;
    //malloc_info(0, stdout);
  }

  //std::cout << "after free" << std::endl;
  //malloc_info(0, stdout);

  {
    std::unordered_map<int, double> um;

    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < Iterations; ++i)
      um.emplace(i, i);
    auto end = std::chrono::system_clock::now();

    std::cout << um.size() << std::endl;
    std::cout << (end - start).count() << std::endl;
   // std::cout << "after use" << std::endl;
   // malloc_info(0, stdout);
  }
}
