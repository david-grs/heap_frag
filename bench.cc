#include <mtrace/mtrace.h>
#include <mtrace/malloc_chrono.h>

#include <papipp.h>

#include <unordered_map>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <iostream>

#include <malloc.h>

static constexpr const int Iterations = 4e6;

void benchmark_unordered_map_emplace(papi::event_set<PAPI_TOT_INS, PAPI_TOT_CYC>& events)
{
    std::unordered_map<int, int> um;
    mtrace<malloc_chrono> mt;

    auto start = std::chrono::system_clock::now();
    events.reset_counters();
    for (int i = 0; i < Iterations; ++i)
      um.emplace(i, i);
    events.reset_counters();
    auto end = std::chrono::system_clock::now();

    malloc_chrono chr = std::get<0>(mt);

    std::cout << Iterations << " iterations of unordered_map<int, int>::emplace took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
    std::cout << events.at<0>().counter() << " instructions, " << events.at<0>().counter() << " cycles" << std::endl;
    std::cout << "time spent in malloc(): " << std::chrono::duration_cast<std::chrono::milliseconds>(chr.malloc_time()).count() << "ms" << std::endl;
    std::cout << "time spent in free(): " << std::chrono::duration_cast<std::chrono::milliseconds>(chr.free_time()).count() << "ms" << std::endl;
    std::cout << "time spent in realloc(): " << std::chrono::duration_cast<std::chrono::milliseconds>(chr.realloc_time()).count() << "ms" << std::endl;
}

void other_benchmarks()
{
    std::map<int, int> m, m2;
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
    papi::event_set<PAPI_TOT_INS, PAPI_TOT_CYC> events;
    events.start_counters(); // start_counters() is more expensive, we call it once, then reset_counters

    benchmark_unordered_map_emplace(events);
    // std::cout << "after first benchmark:" << std::endl;
    // malloc_info(0, stdout);

    other_benchmarks();

    // std::cout << "after second benchmark:" << std::endl;
     malloc_info(0, stdout);
    benchmark_unordered_map_emplace(events);

    return 0;
}
