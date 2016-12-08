#include <mtrace/mtrace.h>
#include <mtrace/malloc_chrono.h>

#include <unordered_map>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <iostream>

#include <malloc.h>

static constexpr const int Iterations = 4e6;

void benchmark()
{
    std::unordered_map<int, double> um;

    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < Iterations; ++i)
      um.emplace(i, i);
    auto end = std::chrono::system_clock::now();

    std::cout << "took " << (end - start).count() << "ns" << std::endl;
}

void other_benchmarks()
{
    std::map<int, double> m, m2;
    std::vector<std::string> vs, vs2;

    for (int i = 0; i < Iterations; ++i)
    {
      m.emplace(i, i);
      m2.emplace(i, i);
      vs.emplace_back('c', (i % 10000));
      vs2.emplace_back('c', (i % 10000));
    }
}

int main()
{
    benchmark();
    // std::cout << "after first benchmark:" << std::endl;
    // malloc_info(0, stdout);

    other_benchmarks();

    // std::cout << "after second benchmark:" << std::endl;
    // malloc_info(0, stdout);
    benchmark();

    return 0;
}
