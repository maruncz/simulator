#include "alg.h"
#include <cmath>
#include <gtest/gtest.h>
#include <limits>
#include <random>

TEST(matrix, ctor_empty)
{
    mat<float, 5, 6> tmp;
    for (const auto &e : tmp.data)
    {
        for (auto i : e)
        {
            ASSERT_NEAR(i, 0.0f, std::numeric_limits<float>::epsilon());
        }
    }
}

TEST(matrix, ctor)
{
    mat<float, 3, 3> A({{{{1, 1, 1}}, {{0, 0, 0}}, {{0, 0, 0}}}});
    for (auto i : A.data[0])
    {
        ASSERT_NEAR(i, 1, 10e-10);
    }
}

TEST(matrix, iterate)
{
    mat<float, 2, 3> A({{{{1, 1, 1}}, {{0, 0, 0}}}});
    for (int r = 0; r < 2; ++r)
    {
        for (int c = 0; c < 3; ++c)
        {
            if (r == 0)
            {
                ASSERT_NEAR(A.data[r][c], 1, 10e-10);
            }
            else
            {
                ASSERT_NEAR(A.data[r][c], 0, 10e-10);
            }
        }
    }
}

TEST(matrix, factory_eye)
{
    constexpr uint8_t size{4};
    auto tmp = mat<float, size, size>::eye();
    for (int r = 0; r < size; ++r)
    {
        for (int c = 0; c < size; ++c)
        {
            if (r == c)
            {
                ASSERT_NEAR(tmp.data[r][c], 1.0f,
                            std::numeric_limits<float>::epsilon());
            }
            else
            {
                ASSERT_NEAR(tmp.data[r][c], 0.0f,
                            std::numeric_limits<float>::epsilon());
            }
        }
    }
}

TEST(matrix, transpose)
{
    {
        mat<float, 3, 3> A({{{{1, 2, 3}}, {{4, 5, 6}}, {{7, 8, 9}}}});
        auto B = A.transpose();
        for (int r = 0; r < 3; ++r)
        {
            for (int c = 0; c < 3; ++c)
            {
                ASSERT_NEAR(A.data[r][c], B.data[c][r], 10e-10);
            }
        }
    }
    {
        mat<float, 2, 3> A({{{{1, 2, 3}}, {{4, 5, 6}}}});
        auto B = A.transpose();
        for (int r = 0; r < 2; ++r)
        {
            for (int c = 0; c < 3; ++c)
            {
                ASSERT_NEAR(A.data[r][c], B.data[c][r], 10e-10);
            }
        }
    }
}

TEST(matrix, multiply_by_eye)
{
    constexpr uint8_t size{4};
    auto eye = mat<float, size, size>::eye();

    std::default_random_engine generator;
    std::uniform_real_distribution<float> dist(-100.0f, 100.0f);

    for (int s = 0; s < 1000; ++s)
    {
        mat<float, size, size> tmp;
        for (int r = 0; r < size; ++r)
        {
            for (int c = 0; c < size; ++c)
            {
                tmp.data[r][c] = dist(generator);
            }
        }

        auto result = tmp * eye;

        for (int r = 0; r < size; ++r)
        {
            for (int c = 0; c < size; ++c)
            {
                ASSERT_NEAR(result.data[r][c], tmp.data[r][c],
                            std::numeric_limits<float>::epsilon());
            }
        }
    }
}

TEST(matrix, multiply_square)
{
    constexpr uint8_t size{3};
    constexpr float err{10e-10};
    {
        mat<float, size, size> A({{{{1, 2, 3}}, {{4, 5, 6}}, {{7, 8, 9}}}});
        mat<float, size, size> B({{{{7, 8, 9}}, {{4, 5, 6}}, {{1, 2, 3}}}});
        mat<float, size, size> C(
            {{{{18, 24, 30}}, {{54, 69, 84}}, {{90, 114, 138}}}});
        mat<float, size, size> D(
            {{{{102, 126, 150}}, {{66, 81, 96}}, {{30, 36, 42}}}});

        {
            auto res  = A * B;
            auto diff = C - res;
            for (const auto &c : diff.data)
            {
                for (auto i : c)
                {
                    ASSERT_NEAR(i, 0, err);
                }
            }
        }
        {
            auto res  = B * A;
            auto diff = D - res;
            for (const auto &c : diff.data)
            {
                for (auto i : c)
                {
                    ASSERT_NEAR(i, 0, err);
                }
            }
        }
    }
    {
        mat<float, size, size> A({{{{1, 1, 1}}, {{0, 0, 0}}, {{0, 0, 0}}}});
        mat<float, size, size> B({{{{0, 1, 0}}, {{0, 1, 0}}, {{0, 1, 0}}}});
        mat<float, size, size> C({{{{0, 3, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}});
        {
            auto res  = A * B;
            auto diff = C - res;
            for (const auto &c : diff.data)
            {
                for (auto i : c)
                {
                    ASSERT_NEAR(i, 0, err);
                }
            }
        }
    }
}

TEST(matrix, multiply_gen)
{
    constexpr float err{10e-10};
    mat<float, 3, 3> A({{{{1, 2, 3}}, {{4, 5, 6}}, {{7, 8, 9}}}});
    auto B = mat<float, 1, 3>::row({1, 2, 3});
    auto C = mat<float, 1, 3>::row({30, 36, 42});
    auto D = mat<float, 3, 1>::col({14, 32, 50});

    {
        auto res  = B * A;
        auto diff = C - res;
        for (const auto &c : diff.data)
        {
            for (auto i : c)
            {
                ASSERT_NEAR(i, 0, err);
            }
        }
    }
    {
        auto res  = A * B.transpose();
        auto diff = D - res;
        for (const auto &c : diff.data)
        {
            for (auto i : c)
            {
                ASSERT_NEAR(i, 0, err);
            }
        }
    }
}
