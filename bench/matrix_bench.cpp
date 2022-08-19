#include "alg.h"
#include <benchmark/benchmark.h>

static void matrix_ctor_empty(benchmark::State &state)
{
    for (auto _ : state)
    {
        simulator::algebra::mat<float, 10, 10> tmp;
        benchmark::DoNotOptimize(tmp);
    }
}

BENCHMARK(matrix_ctor_empty);

static void matrix_factory_eye(benchmark::State &state)
{
    for (auto _ : state)
    {
        auto tmp = simulator::algebra::mat<float, 10, 10>::eye();
        benchmark::DoNotOptimize(tmp);
    }
}

BENCHMARK(matrix_factory_eye);

static void matrix_transpose(benchmark::State &state)
{
    simulator::algebra::mat<float, 10, 10> start;
    benchmark::DoNotOptimize(start);
    for (auto _ : state)
    {
        auto tmp = start.transpose();
        benchmark::DoNotOptimize(tmp);
    }
}

BENCHMARK(matrix_transpose);

static void matrix_multiply(benchmark::State &state)
{
    simulator::algebra::mat<float, 10, 10> start;
    benchmark::DoNotOptimize(start);
    for (auto _ : state)
    {
        auto tmp = start * start;
        benchmark::DoNotOptimize(tmp);
    }
}

BENCHMARK(matrix_multiply);

static void matrix_add(benchmark::State &state)
{
    simulator::algebra::mat<float, 10, 10> start;
    benchmark::DoNotOptimize(start);
    for (auto _ : state)
    {
        auto tmp = start + start;
        benchmark::DoNotOptimize(tmp);
    }
}

BENCHMARK(matrix_add);

static void matrix_add_alg(benchmark::State &state)
{
    simulator::algebra::mat<float, 10, 10> start;
    benchmark::DoNotOptimize(start);
    for (auto _ : state)
    {
        auto tmp = start.elementWiseBinaryOpAlg(start, std::plus<>{});
        benchmark::DoNotOptimize(tmp);
    }
}

BENCHMARK(matrix_add_alg);
