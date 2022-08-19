#include "lti.h"
#include <iostream>

int main()
{
    {
        simulator::discrete::lti::SYS<float, 3, 1, 3> lti(
            1.0f, {{1, 0, 0, 1, 0, 0, 0, 1, 0}},
            simulator::algebra::mat<float, 3, 1>::col({1, 0, 0}),
            simulator::algebra::mat<float, 3, 3>::eye());
        for (int i = 0; i < 10; ++i)
        {
            lti.set_input(1.0f);
            lti.update(i);
            // std::cout << lti.get_output() << '\n';
        }
    }
    return 0;
}
