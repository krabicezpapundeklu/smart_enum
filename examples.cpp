
//          Copyright Jarda Flieger 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

#include "smart_enum.hpp"


SMART_ENUM(e_1, (e_1_a, e_1_b, e_1_c))
SMART_ENUM(n_1, e_2, (e_2_a, (e_2_b, 10, (1, 2, "xxx")), e_2_c))

SMART_ENUM_CLASS((n_1, n_2), e_3, (e_3_a, e_3_b, e_3_c))
SMART_ENUM_CLASS((n_1, n_2), (e_4, short), (e_4_a, (e_4_b, 10), (e_4_c, (false))))

int main()
{
    using namespace smart_enum;

    std::cout << enum_traits<e_1>::name << std::endl;
    std::cout << enum_traits<e_1>::full_name << std::endl;

    std::cout << enum_traits<n_1::n_2::e_4>::name << std::endl;
    std::cout << enum_traits<n_1::n_2::e_4>::full_name << std::endl;

    return 0;
}
