#ifndef SYS_H
#define SYS_H

#include "base.h"
#include <cstdint>
#include <type_traits>

template<real T, uint8_t in_size, uint8_t out_size>
class SYS : public base
{
    static_assert(in_size > 0);
    static_assert(out_size > 0);

public:

private:

};

#endif // SYS_H
