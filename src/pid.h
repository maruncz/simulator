#ifndef PID_H
#define PID_H

#include "base.h"
#include <cmath>

namespace simulator
{

namespace discrete
{

template<real T> class PID
{
public:
    struct additive
    {
    };
    struct multiplicative
    {
    };

    using value_type = T;

    PID(multiplicative, T beta, T N, T K, T Ts, T Ti, T Td, T Ks, T satUp,
        T satDown)
        : beta(beta), Ts(Ts), Ks(Ks), satUp(satUp), satDown(satDown)
    {
        Kp  = K;
        Ki  = Ts * K / Ti;
        Kdf = std::exp((-Ts * N) / Td);
        Kd  = ((K * Td) / Ts) * (1 - Kdf);
    }

    PID(additive, T beta, T Kp, T Ki, T Kdf, T Kd, T Ks, T Ts, T satUp,
        T satDown)
        : beta(beta), Kp(Kp), Ki(Ki), Kdf(Kdf), Kd(Kd), Ks(Ks), Ts(Ts),
          satUp(satUp), satDown(satDown)
    {
    }

    T iterate(T w, T y)
    {
        T up      = calcP(w, y);
        T ud      = calcD(y);
        T u       = up + ud + i;
        T usat    = saturate(u);
        T satDiff = usat - u;
        i         = i + (Ks * satDiff) + (Ki * (w - y));
        return usat;
    }

private:
    T calcP(T w, T y) { return Kp * ((beta * w) - y); }
    T calcD(T y)
    {
        T ud = Kd * (-d + ((Kdf * d) - y));
        d    = (Kdf * d) - y;
        return ud;
    }

    T saturate(T u)
    {
        if (u > satUp)
        {
            return satUp;
        }
        if (u < satDown)
        {
            return satDown;
        }
        return u;
    }

    T i{0.0};
    T d{0.0};

    T beta;
    T Kp;
    T Ki;
    T Kdf;
    T Kd;
    T Ks;
    T Ts;

    T satUp;
    T satDown;
};

template<typename T>
requires std::is_floating_point_v<T>
class PID_const
{
public:
    struct additive
    {
    };
    struct multiplicative
    {
    };

    using value_type = T;

    PID_const(multiplicative, T beta, T N, T K, T Ts, T Ti, T Td, T Ks, T satUp,
              T satDown)
        : beta(beta), Ts(Ts), Ks(Ks), satUp(satUp), satDown(satDown)
    {
        Kp  = K;
        Ki  = Ts * K / Ti;
        Kdf = std::exp((-Ts * N) / Td);
        Kd  = ((K * Td) / Ts) * (1 - Kdf);
    }

    PID_const(additive, T beta, T Kp, T Ki, T Kdf, T Kd, T Ks, T Ts, T satUp,
              T satDown)
        : beta(beta), Kp(Kp), Ki(Ki), Kdf(Kdf), Kd(Kd), Ks(Ks), Ts(Ts),
          satUp(satUp), satDown(satDown)
    {
    }

    T iterate(T w, T y)
    {
        T up      = calcP(w, y);
        T ud      = calcD(y);
        T u       = up + ud + i;
        T usat    = saturate(u);
        T satDiff = usat - u;
        i         = i + (Ks * satDiff) + (Ki * (w - y));
        return usat;
    }

private:
    T calcP(T w, T y) { return Kp * ((beta * w) - y); }
    T calcD(T y)
    {
        T ud = Kd * (-d + ((Kdf * d) - y));
        d    = (Kdf * d) - y;
        return ud;
    }

    T saturate(T u)
    {
        if (u > satUp)
        {
            return satUp;
        }
        if (u < satDown)
        {
            return satDown;
        }
        return u;
    }

    T i{0.0};
    T d{0.0};

    const T beta;
    const T Kp;
    const T Ki;
    const T Kdf;
    const T Kd;
    const T Ks;
    const T Ts;

    const T satUp;
    const T satDown;
};

} // namespace discrete

} // namespace simulator

#endif // PID_H
