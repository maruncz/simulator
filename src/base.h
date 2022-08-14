#ifndef BASE_H
#define BASE_H

#include <array>
#include <concepts>
#include <cstdint>
#include <type_traits>

template<typename T> concept real = std::is_floating_point<T>::value;

template<real T>
class base
{
public:
    virtual void update(T timepoint) = 0;
};

template<real T, uint8_t len> struct sample
{
    T timepoint{T(0)};
    std::array<T, len> sample;
};

#endif // BASE_H
