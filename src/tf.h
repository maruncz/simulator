#ifndef TF_H
#define TF_H

#include "base.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <execution>
#include <numeric>
#include <type_traits>

template<real T, uint8_t num_size, uint8_t den_size>
class TF_SISO : public base<T>
{
    static_assert(num_size > 0);
    static_assert(den_size > 0);

public:
    TF_SISO(T t_samp, std::array<T, num_size> t_num,
            std::array<T, den_size> t_den)
        : num(t_num), den(t_den), sampling_period(t_samp)
    {
        u.fill(T(0));
        y.fill(T(0));
    }

    void set_input(T in) { u[0] = in; }

    void update(T timepoint) override
    {
        if (timepoint < (last_time + sampling_period))
        {
            return;
        }

        last_time += sampling_period;

        std::rotate(std::execution::unseq, y.rbegin(), y.rbegin() + 1,
                    y.rend());

        y[0] = std::transform_reduce(std::execution::unseq, num.begin(),
                                     num.end(), u.begin(), T(0), std::plus<T>{},
                                     std::multiplies<T>{});

        y[0] += std::transform_reduce(std::execution::unseq, den.begin() + 1,
                                      den.end(), y.begin() + 1, T(0),
                                      std::minus<T>{}, std::multiplies<T>{});

        std::rotate(std::execution::unseq, u.rbegin(), u.rbegin() + 1,
                    u.rend());
    }

    auto get_output() const { return y[0]; }

private:
    const std::array<T, num_size> num;
    const std::array<T, den_size> den;
    const T sampling_period;

    std::array<T, num_size> u;
    std::array<T, den_size> y;

    T last_time{T(-1)};
};

#endif // TF_H
