


#include <benchmark/benchmark.h>

#include "bench_containers.h"



template <typename Container>
void bench_container_insert(benchmark::State& state) {
    for (auto _ : state) {
        Container c;
        for (int64_t i = 0; i < state.range(0); ++i) {
            push(c, i);
        }
        benchmark::ClobberMemory();
        benchmark::DoNotOptimize(c);
    }
}



BENCHMARK_TEMPLATE(bench_container_insert, StdVec) -> Arg(256);
BENCHMARK_TEMPLATE(bench_container_insert, StdFList) -> Arg(256);
BENCHMARK_TEMPLATE(bench_container_insert, StdList) -> Arg(256);
BENCHMARK_TEMPLATE(bench_container_insert, StdDeque) -> Arg(256);
BENCHMARK_TEMPLATE(bench_container_insert, StdSet) -> Arg(256);
BENCHMARK_TEMPLATE(bench_container_insert, StdUSet) -> Arg(256);
BENCHMARK_TEMPLATE(bench_container_insert, AbslBTreeSet) -> Arg(256);
BENCHMARK_TEMPLATE(bench_container_insert, AbslFlatHashSet) -> Arg(256);
BENCHMARK_TEMPLATE(bench_container_insert, AbslNodeHashSet) -> Arg(256);
BENCHMARK_TEMPLATE(bench_container_insert, BoostVec) -> Arg(256);
BENCHMARK_TEMPLATE(bench_container_insert, BoostFlatSet) -> Arg(256);
BENCHMARK_TEMPLATE(bench_container_insert, BoostStableVec) -> Arg(256);



BENCHMARK_MAIN();