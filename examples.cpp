
//          Copyright Jarda Flieger 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "smart_enum.hpp"

//SMART_ENUM_IMPL_ADDITIONAL_DATA(n_1::n_2::e_1_c, ((a), (b, 10), (c, (1, 2, 3)), (d, 20, (4, 5, 6))))

/*
SMART_ENUM_IMPL_MEMBER_DEFINITION((a))
SMART_ENUM_IMPL_MEMBER_DEFINITION((b, 10))
SMART_ENUM_IMPL_MEMBER_DEFINITION((c, (1, 2, 3)))
SMART_ENUM_IMPL_MEMBER_DEFINITION((d, 20, (4, 5, 6)))
*/

//SMART_ENUM_IMPL_MEMBER_DEFINITIONS(((a), (b, 10), (c, (1, 2, 3)), (d, 20, (4, 5, 6))))

/*
SMART_ENUM_IMPL_MEMBER_FROM_STRING(n_1::n_2::e_1_c, (a))
SMART_ENUM_IMPL_MEMBER_FROM_STRING(n_1::n_2::e_1_c, (b, 10))
SMART_ENUM_IMPL_MEMBER_FROM_STRING(n_1::n_2::e_1_c, (c, (1, 2, 3)))
SMART_ENUM_IMPL_MEMBER_FROM_STRING(n_1::n_2::e_1_c, (d, 20, (4, 5, 6)))
*/

//SMART_ENUM_IMPL_FROM_STRING(n_1::n_2::e_1_c, ((a), (b, 10), (c, (1, 2, 3)), (d, 20, (4, 5, 6))))

/*
SMART_ENUM_IMPL_MEMBER_TO_STRING(n_1::n_2::e_1_c, (a))
SMART_ENUM_IMPL_MEMBER_TO_STRING(n_1::n_2::e_1_c, (b, 10))
SMART_ENUM_IMPL_MEMBER_TO_STRING(n_1::n_2::e_1_c, (c, (1, 2, 3)))
SMART_ENUM_IMPL_MEMBER_TO_STRING(n_1::n_2::e_1_c, (d, 20, (4, 5, 6)))
*/

//SMART_ENUM_IMPL_TO_STRING(n_1::n_2::e_1_c, ((a), (b, 10), (c, (1, 2, 3)), (d, 20, (4, 5, 6))))

SMART_ENUM(e_1_a, (a, (b, 10), (c, (1, 2, 3)), (d, 20, (4, 5, 6))))
SMART_ENUM(n_1, (e_1_a, short), (a, (b, 10), (c, (1, 2, 3)), (d, 20, (4, 5, 6))))
SMART_ENUM((n_1, n_2), e_1_a, (a, (b, 10), (c, (1, 2, 3)), (d, 20, (4, 5, 6))))

int main()
{
    return 0;
}
