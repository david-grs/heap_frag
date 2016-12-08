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
    mtrace<malloc_chrono> mt;

    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < Iterations; ++i)
      um.emplace(i, i);
    auto end = std::chrono::system_clock::now();

    malloc_chrono chr = std::get<0>(mt);

    std::cout << "took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
    std::cout << "time spent in malloc(): " << std::chrono::duration_cast<std::chrono::milliseconds>(chr.malloc_time()).count() << "ms" << std::endl;
    std::cout << "time spent in free(): " << std::chrono::duration_cast<std::chrono::milliseconds>(chr.free_time()).count() << "ms" << std::endl;
    std::cout << "time spent in realloc(): " << std::chrono::duration_cast<std::chrono::milliseconds>(chr.realloc_time()).count() << "ms" << std::endl;
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
    std::cout << "running benchmark first time... ";
    benchmark();
    // std::cout << "after first benchmark:" << std::endl;
    // malloc_info(0, stdout);

    std::cout << "running some other benchmarks...";
    other_benchmarks();
    std::cout << "OK" << std::endl;

    // std::cout << "after second benchmark:" << std::endl;
    // malloc_info(0, stdout);
    std::cout << "running first benchmark a second time... ";
    benchmark();

    return 0;
}
