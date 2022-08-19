#include "lti.h"
#include <gtest/gtest.h>
#include <limits>

TEST(lti_SYS, integrator_delay)
{
    simulator::discrete::lti::SYS<float, 3, 1, 3> lti(
        1.0f, {{1, 0, 0, 1, 0, 0, 0, 1, 0}},
        simulator::algebra::mat<float, 3, 1>::col({1, 0, 0}),
        simulator::algebra::mat<float, 3, 3>::eye());

    std::array<simulator::algebra::mat<float, 1, 3>, 11> x{
        simulator::algebra::mat<float, 1, 3>::row({0, 0, 0}),
        simulator::algebra::mat<float, 1, 3>::row({1, 0, 0}),
        simulator::algebra::mat<float, 1, 3>::row({2, 1, 0}),
        simulator::algebra::mat<float, 1, 3>::row({3, 2, 1}),
        simulator::algebra::mat<float, 1, 3>::row({4, 3, 2}),
        simulator::algebra::mat<float, 1, 3>::row({5, 4, 3}),
        simulator::algebra::mat<float, 1, 3>::row({6, 5, 4}),
        simulator::algebra::mat<float, 1, 3>::row({7, 6, 5}),
        simulator::algebra::mat<float, 1, 3>::row({8, 7, 6}),
        simulator::algebra::mat<float, 1, 3>::row({9, 8, 7}),
        simulator::algebra::mat<float, 1, 3>::row({10, 9, 8})};

    std::array<simulator::algebra::mat<float, 1, 3>, 11> y{
        simulator::algebra::mat<float, 1, 3>::row({0, 0, 0}),
        simulator::algebra::mat<float, 1, 3>::row({1, 0, 0}),
        simulator::algebra::mat<float, 1, 3>::row({2, 1, 0}),
        simulator::algebra::mat<float, 1, 3>::row({3, 2, 1}),
        simulator::algebra::mat<float, 1, 3>::row({4, 3, 2}),
        simulator::algebra::mat<float, 1, 3>::row({5, 4, 3}),
        simulator::algebra::mat<float, 1, 3>::row({6, 5, 4}),
        simulator::algebra::mat<float, 1, 3>::row({7, 6, 5}),
        simulator::algebra::mat<float, 1, 3>::row({8, 7, 6}),
        simulator::algebra::mat<float, 1, 3>::row({9, 8, 7}),
        simulator::algebra::mat<float, 1, 3>::row({10, 9, 8})};

    ASSERT_NEAR(lti.get_output().norm(), y[0].norm(), 1e-10);
    for (int i = 0; i < 10; ++i)
    {
        lti.set_input(1.0f);
        lti.update(i);
        ASSERT_NEAR(lti.get_output().norm(), y[i + 1].norm(), 1e-10);
    }
}
