#include "tf.h"
#include <iostream>

int main()
{
    {
        TF_SISO<float, 2, 2> lti(1.0f, {0.0f, 0.5f}, {1, -0.5f});
        for (int i = 0; i < 10; ++i)
        {
            lti.set_input(1.0f);
            lti.update(i);
            std::cout << lti.get_output() << '\n';
        }
    }
    return 0;
}
