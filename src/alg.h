#ifndef ALG_H
#define ALG_H

#include "base.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>

namespace simulator
{

namespace algebra
{

template<real T, uint8_t rows, uint8_t cols> struct mat
{
    using row_type  = std::array<T, cols>;
    using col_type  = std::array<T, rows>;
    using data_type = std::array<row_type, rows>;

    constexpr mat()
    {
        for (auto &r : data)
        {
            r.fill(0);
        }
    }

    constexpr mat(T value)
    {
        for (auto &r : data)
        {
            r.fill(value);
        }
    }

    constexpr mat(data_type idata) : data(idata) {}

    constexpr static mat eye() requires(rows == cols)
    {
        mat out;
        for (int i = 0; i < rows; ++i)
        {
            out.data[i][i] = T(1);
        }
        return out;
    }

    constexpr static mat row(row_type irow) requires(rows == 1)
    {
        mat out;
        out.data[0] = irow;
        return out;
    }

    constexpr static mat col(col_type icol) requires(cols == 1)
    {
        mat out;
        for (int r = 0; r < rows; ++r)
        {
            out.data[r][0] = icol[r];
        }
        return out;
    }

    auto transpose() const
    {
        mat<T, cols, rows> out;
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < cols; ++c)
            {
                out.data[c][r] = data[r][c];
            }
        }
        return out;
    }

    template<uint8_t irows, uint8_t icols>
    auto operator*(mat<T, irows, icols> imat) const requires(cols == irows)
    {
        mat<T, rows, icols> out;
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < icols; ++c)
            {
                for (int i = 0; i < cols; ++i)
                {
                    out.data[r][c] += data[r][i] * imat.data[i][c];
                }
            }
        }
        return out;
    }

    mat operator+(mat o) const
    {
        mat out;
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < cols; ++c)
            {
                out.data[r][c] = data[r][c] + o.data[r][c];
            }
        }
        return out;
    }

    mat operator-(mat o) const
    {
        mat out;
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < cols; ++c)
            {
                out.data[r][c] = data[r][c] - o.data[r][c];
            }
        }
        return out;
    }

    T norm() const
    {
        T out{0};
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < cols; ++c)
            {
                out += data[r][c] * data[r][c];
            }
        }
        return std::sqrt(out);
    }

    friend std::ostream &operator<<(std::ostream &output, const mat &in)
    {
        output << '[';
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < cols; ++c)
            {
                output << in.data[r][c];
                if (c < (cols - 1))
                {
                    output << ' ';
                }
            }
            if (r < (rows - 1))
            {
                output << ';';
            }
        }
        output << ']';

        return output;
    }

    data_type data;
};

} // namespace algebra

} // namespace simulator

#endif // ALG_H
