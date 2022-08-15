#include "lti.h"
#include "pid.h"
#include <benchmark/benchmark.h>

static void iterate_algo_unseq(benchmark::State &state)
{
    for (auto _ : state)
    {
        TF_SISO<float, 4, 4> lti(1.0f, {0, 0, 0, 0.125f},
                                 {1, -1.5f, 0.75f, -0.125f});
        for (int i = 0; i < 10; ++i)
        {
            lti.set_input(1.0f);
            lti.update(i);
            auto ret = lti.get_output();
            benchmark::DoNotOptimize(ret);
        }
    }
}

BENCHMARK(iterate_algo_unseq);

static void pid(benchmark::State &state)
{
    PID<double> pid(PID<double>::additive{}, 1, 2, 0.4739336492890995,
                    0.04978706836786394, 1.135145158787298, 1, 0.01, 100, -100);
    double prevU{0};
    for (auto _ : state)
    {
        for (int i = 0; i < 30; ++i)
        {
            auto ret = pid.iterate(1, prevU);
            prevU    = 100 * ret;
            benchmark::DoNotOptimize(prevU);
        }
    }
}

BENCHMARK(pid);

static void pid_const(benchmark::State &state)
{
    PID_const<double> pid(PID_const<double>::additive{}, 1, 2,
                          0.4739336492890995, 0.04978706836786394,
                          1.135145158787298, 1, 0.01, 100, -100);
    double prevU{0};
    for (auto _ : state)
    {
        for (int i = 0; i < 30; ++i)
        {
            auto ret = pid.iterate(1, prevU);
            prevU    = 100 * ret;
            benchmark::DoNotOptimize(prevU);
        }
    }
}

BENCHMARK(pid_const);
