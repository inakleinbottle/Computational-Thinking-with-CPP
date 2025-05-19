#include <random>
#include <benchmark/benchmark.h>

#include "bench_containers.h"


template<template <typename, typename> class Map>
Map<int64_t, int64_t> make_map(int64_t size) {
    Map<int64_t, int64_t> m;
    for (int64_t i = 0; i < size; ++i) {
        m[i] = i;
    }
    return m;
}


template<template <typename, typename> class Map>
void bench_map_random_access(benchmark::State &state) {
    auto m = make_map<Map>(state.range(0));

    std::mt19937_64 rng(std::random_device{}());
    std::uniform_int_distribution<int64_t> dist(0, m.size() - 1);

    for (auto _: state) {
        int64_t i = dist(rng);
        auto &value = m[i];
        benchmark::DoNotOptimize(value);
    }
}


BENCHMARK_TEMPLATE(bench_map_random_access, std::map)->Arg(256)->Arg(1024);
BENCHMARK_TEMPLATE(bench_map_random_access, std::unordered_map)->Arg(256)->Arg(1024);

BENCHMARK_TEMPLATE(bench_map_random_access, absl::btree_map)->Arg(256)->Arg(1024);
BENCHMARK_TEMPLATE(bench_map_random_access, absl::flat_hash_map)->Arg(256)->Arg(1024);
BENCHMARK_TEMPLATE(bench_map_random_access, absl::node_hash_map)->Arg(256)->Arg(1024);


BENCHMARK_TEMPLATE(bench_map_random_access, boost::container::flat_map)->Arg(256)->Arg(1024);
BENCHMARK_TEMPLATE(bench_map_random_access, boost::unordered_map)->Arg(256)->Arg(1024);
BENCHMARK_TEMPLATE(bench_map_random_access, boost::unordered_flat_map)->Arg(256)->Arg(1024);



BENCHMARK_MAIN();