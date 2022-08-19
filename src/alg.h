#ifndef ALG_H
#define ALG_H

#include "base.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <execution>
#include <iostream>

namespace simulator
{

namespace algebra
{

template<real T, uint8_t rows, uint8_t cols> class mat
{
public:
    using row_type  = std::array<T, cols>;
    using col_type  = std::array<T, rows>;
    using data_type = std::array<T, rows * cols>;

    constexpr mat() { data.fill(0); }

    constexpr mat(T value) { data.fill(value); }

    constexpr mat(data_type idata) : data(idata) {}

    constexpr static mat eye() requires(rows == cols)
    {
        mat out;
        for (int i = 0; i < rows; ++i)
        {
            out.at(i, i) = T(1);
        }
        return out;
    }

    constexpr static mat row(row_type irow) requires(rows == 1)
    {
        mat out;
        out.data = irow;
        return out;
    }

    constexpr static mat col(col_type icol) requires(cols == 1)
    {
        mat out;
        out.data = icol;
        return out;
    }

    auto transpose() const
    {
        mat<T, cols, rows> out;
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < cols; ++c)
            {
                out.at(c, r) = at(r, c);
            }
        }
        return out;
    }

    template<uint8_t irows, uint8_t icols>
    auto operator*(const mat<T, irows, icols> &imat) const
        requires(cols == irows)
    {
        mat<T, rows, icols> out;
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < icols; ++c)
            {
                for (int i = 0; i < cols; ++i)
                {
                    out.at(r, c) += at(r, i) * imat.at(i, c);
                }
            }
        }
        return out;
    }

    mat operator+(const mat &o) const
    {
        mat out = elementWiseBinaryOpLoop(o, std::plus<>{});
        return out;
    }

    mat operator-(const mat &o) const
    {
        mat out = elementWiseBinaryOpLoop(o, std::minus<>{});
        return out;
    }

    T norm() const
    {
        T out{0};
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < cols; ++c)
            {
                out += at(r, c) * at(r, c);
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
                output << in.at(r, c);
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

    const T &at(uint8_t row, uint8_t col) const
    {
        assert(row < rows);
        assert(col < cols);
        return data[row * cols + col];
    }

    T &at(uint8_t row, uint8_t col)
    {
        return const_cast<T &>(const_cast<const mat *>(this)->at(row, col));
    }

    template<typename binaryOp>
    mat elementWiseBinaryOpAlg(const mat &o, binaryOp op) const
    {
        mat out;
        std::transform(std::execution::unseq, data.begin(), data.end(),
                       o.data.begin(), out.data.begin(), op);
        return out;
    }

private:
    template<typename binaryOp>
    mat elementWiseBinaryOpLoop(const mat &o, binaryOp op) const
    {
        mat out;
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < cols; ++c)
            {
                out.at(r, c) = op(at(r, c), o.at(r, c));
            }
        }
        return out;
    }

    data_type data;
};

} // namespace algebra

} // namespace simulator

#endif // ALG_H
