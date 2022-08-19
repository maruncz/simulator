#include "alg.h"
#include <cmath>
#include <gtest/gtest.h>
#include <limits>
#include <random>
#include <sstream>

TEST(matrix, ctor_empty)
{
    simulator::algebra::mat<float, 5, 6> tmp;
    for (int r = 0; r < 5; ++r)
    {
        for (int c = 0; c < 6; ++c)
        {
            ASSERT_NEAR(tmp.at(r, c), 0.0f,
                        std::numeric_limits<float>::epsilon());
        }
    }
}

TEST(matrix, ctor)
{
    simulator::algebra::mat<float, 3, 3> A{{1, 1, 1, 0, 0, 0, 0, 0, 0}};
    for (int c = 0; c < 3; ++c)
    {
        ASSERT_NEAR(A.at(0, c), 1.0f, std::numeric_limits<float>::epsilon());
    }

    for (int r = 1; r < 3; ++r)
    {
        for (int c = 0; c < 3; ++c)
        {
            ASSERT_NEAR(A.at(r, c), 0.0f,
                        std::numeric_limits<float>::epsilon());
        }
    }
}

TEST(matrix, iterate)
{
    simulator::algebra::mat<float, 2, 3> A({1, 1, 1, 0, 0, 0});
    for (int c = 0; c < 3; ++c)
    {
        ASSERT_NEAR(A.at(0, c), 1, 10e-10);
    }
    for (int c = 0; c < 3; ++c)
    {
        ASSERT_NEAR(A.at(1, c), 0, 10e-10);
    }
}

TEST(matrix, factory_eye)
{
    constexpr uint8_t size{4};
    auto tmp = simulator::algebra::mat<float, size, size>::eye();
    for (int r = 0; r < size; ++r)
    {
        for (int c = 0; c < size; ++c)
        {
            if (r == c)
            {
                ASSERT_NEAR(tmp.at(c, r), 1.0f,
                            std::numeric_limits<float>::epsilon());
            }
            else
            {
                ASSERT_NEAR(tmp.at(c, r), 0.0f,
                            std::numeric_limits<float>::epsilon());
            }
        }
    }
}

TEST(matrix, transpose)
{
    {
        simulator::algebra::mat<float, 3, 3> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
        auto B = A.transpose();
        for (int r = 0; r < 3; ++r)
        {
            for (int c = 0; c < 3; ++c)
            {
                ASSERT_NEAR(A.at(r, c), B.at(c, r), 10e-10);
            }
        }
    }
    {
        simulator::algebra::mat<float, 2, 3> A({1, 2, 3, 4, 5, 6});
        auto B = A.transpose();
        for (int r = 0; r < 2; ++r)
        {
            for (int c = 0; c < 3; ++c)
            {
                ASSERT_NEAR(A.at(r, c), B.at(c, r), 10e-10);
            }
        }
    }
}

TEST(matrix, multiply_by_eye)
{
    simulator::algebra::mat<float, 3, 3> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
    auto e   = simulator::algebra::mat<float, 3, 3>::eye();
    auto res = A * e;
    for (int r = 0; r < 3; ++r)
    {
        for (int c = 0; c < 3; ++c)
        {
            ASSERT_NEAR(A.at(c, r), res.at(c, r), 10e-10);
        }
    }
}

TEST(matrix, multiply_square)
{
    constexpr uint8_t size{3};
    constexpr float err{10e-10};
    {
        simulator::algebra::mat<float, size, size> A(
            {1, 2, 3, 4, 5, 6, 7, 8, 9});
        simulator::algebra::mat<float, size, size> B(
            {7, 8, 9, 4, 5, 6, 1, 2, 3});
        simulator::algebra::mat<float, size, size> C(
            {18, 24, 30, 54, 69, 84, 90, 114, 138});
        simulator::algebra::mat<float, size, size> D(
            {102, 126, 150, 66, 81, 96, 30, 36, 42});

        {
            auto res  = A * B;
            auto diff = C - res;
            for (int r = 0; r < size; ++r)
            {
                for (int c = 0; c < size; ++c)
                {
                    ASSERT_NEAR(diff.at(c, r), 0, 10e-10);
                }
            }
        }
        {
            auto res  = B * A;
            auto diff = D - res;
            for (int r = 0; r < size; ++r)
            {
                for (int c = 0; c < size; ++c)
                {
                    ASSERT_NEAR(diff.at(c, r), 0, 10e-10);
                }
            }
        }
    }
    {
        simulator::algebra::mat<float, size, size> A(
            {1, 1, 1, 0, 0, 0, 0, 0, 0});
        simulator::algebra::mat<float, size, size> B(
            {0, 1, 0, 0, 1, 0, 0, 1, 0});
        simulator::algebra::mat<float, size, size> C(
            {0, 3, 0, 0, 0, 0, 0, 0, 0});
        {
            auto res  = A * B;
            auto diff = C - res;
            for (int r = 0; r < size; ++r)
            {
                for (int c = 0; c < size; ++c)
                {
                    ASSERT_NEAR(diff.at(c, r), 0, 10e-10);
                }
            }
        }
    }
}

TEST(matrix, multiply_gen)
{
    constexpr float err{10e-10};
    simulator::algebra::mat<float, 3, 3> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
    auto B = simulator::algebra::mat<float, 1, 3>::row({1, 2, 3});
    auto C = simulator::algebra::mat<float, 1, 3>::row({30, 36, 42});
    auto D = simulator::algebra::mat<float, 3, 1>::col({14, 32, 50});

    {
        auto res  = B * A;
        auto diff = C - res;
        for (int r = 0; r < 1; ++r)
        {
            for (int c = 0; c < 3; ++c)
            {
                ASSERT_NEAR(diff.at(r, c), 0, 10e-10);
            }
        }
    }
    {
        auto res  = A * B.transpose();
        auto diff = D - res;
        for (int r = 0; r < 3; ++r)
        {
            for (int c = 0; c < 1; ++c)
            {
                ASSERT_NEAR(diff.at(r, c), 0, 10e-10);
            }
        }
    }
}

TEST(matrix, print)
{
    constexpr float err{10e-10};
    simulator::algebra::mat<float, 3, 3> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
    auto B = simulator::algebra::mat<float, 1, 3>::row({1, 2, 3});
    auto C = simulator::algebra::mat<float, 3, 1>::col({1, 2, 3});

    {
        std::stringstream Astr;
        Astr << A;
        EXPECT_EQ(Astr.str(), "[1 2 3;4 5 6;7 8 9]");
    }

    {
        std::stringstream Bstr;
        Bstr << B;
        EXPECT_EQ(Bstr.str(), "[1 2 3]");
    }

    {
        std::stringstream Cstr;
        Cstr << C;
        EXPECT_EQ(Cstr.str(), "[1;2;3]");
    }
}

class normTest : public testing::TestWithParam<
                     std::pair<simulator::algebra::mat<float, 3, 3>, float>>
{
};

TEST_P(normTest, norm33)
{
    auto norm = GetParam().first.norm();
    EXPECT_NEAR(norm, GetParam().second, 10e-10);
}

INSTANTIATE_TEST_SUITE_P(
    matrix, normTest,
    testing::Values(std::make_pair(simulator::algebra::mat<float, 3, 3>(
                                       {1, 2, 3, 4, 5, 6, 7, 8, 9}),
                                   16.88194301613413),
                    std::make_pair(simulator::algebra::mat<float, 3, 3>::eye(),
                                   1.732050807568877)));

TEST(matrix, DISABLED_norm)
{
    constexpr float err{10e-10};
    simulator::algebra::mat<float, 3, 3> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
    auto B = simulator::algebra::mat<float, 1, 3>::row({1, 2, 3});
    auto C = simulator::algebra::mat<float, 3, 1>::col({1, 2, 3});

    {
        EXPECT_NEAR(A.norm(), 16.88194301613413, err);
    }

    {
        EXPECT_NEAR(B.norm(), 3.741657386773941, err);
    }

    {
        EXPECT_NEAR(C.norm(), 3.741657386773941, err);
    }
}
