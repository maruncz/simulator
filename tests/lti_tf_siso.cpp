#include "lti.h"
#include <gtest/gtest.h>
#include <limits>

TEST(lti_tf_siso, integrator_delay)
{
    simulator::discrete::lti::SYS<float, 3, 1, 3> lti(
        1.0f, {{{{{1, 0, 0}}, {{1, 0, 0}}, {{0, 1, 0}}}}},
        simulator::algebra::mat<float, 3, 1>::col({1, 0, 0}),
        simulator::algebra::mat<float, 3, 3>::eye());
    simulator::algebra::mat<float, 11, 3> x({{
        {{0, 0, 0}},
        {{1, 0, 0}},
        {{2, 1, 0}},
        {{3, 2, 1}},
        {{4, 3, 2}},
        {{5, 4, 3}},
        {{6, 5, 4}},
        {{7, 6, 5}},
        {{8, 7, 6}},
        {{9, 8, 7}},
        {{10, 9, 8}},
    }});

    simulator::algebra::mat<float, 11, 3> y({{
        {{0, 0, 0}},
        {{1, 0, 0}},
        {{2, 1, 0}},
        {{3, 2, 1}},
        {{4, 3, 2}},
        {{5, 4, 3}},
        {{6, 5, 4}},
        {{7, 6, 5}},
        {{8, 7, 6}},
        {{9, 8, 7}},
        {{10, 9, 8}},
    }});

    for(int i=0;i<10;++i)
    {
        lti.set_input(1.0f);
        lti.update(i);

    }
}
