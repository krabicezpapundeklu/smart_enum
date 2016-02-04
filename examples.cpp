
//          Copyright Jarda Flieger 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "smart_enum.hpp"

// SMART_ENUM_IMPL_ADDITIONAL_DATA(n_1::n_2::e_1_c, ((a), (b, 10), (c, (1, 2, 3)), (d, 20, (4, 5, 6))))

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

// SMART_ENUM_IMPL_FROM_STRING(n_1::n_2::e_1_c, ((a), (b, 10), (c, (1, 2, 3)), (d, 20, (4, 5, 6))))

/*
SMART_ENUM_IMPL_MEMBER_TO_STRING(n_1::n_2::e_1_c, (a))
SMART_ENUM_IMPL_MEMBER_TO_STRING(n_1::n_2::e_1_c, (b, 10))
SMART_ENUM_IMPL_MEMBER_TO_STRING(n_1::n_2::e_1_c, (c, (1, 2, 3)))
SMART_ENUM_IMPL_MEMBER_TO_STRING(n_1::n_2::e_1_c, (d, 20, (4, 5, 6)))
*/

// SMART_ENUM_IMPL_TO_STRING(n_1::n_2::e_1_c, ((a), (b, 10), (c, (1, 2, 3)), (d, 20, (4, 5, 6))))

/*
SMART_ENUM(e_1, (e_1_a, (e_1_b, 10), (e_1_c, (1, 2, 3)), (e_1_d, 20, (4, 5, 6))))
SMART_ENUM(n_1, (e_2, short), (e_2_a, (e_2_b, 10), (e_2_c, (1, 2, 3)), (e_2_d, 20, (4, 5, 6))))
SMART_ENUM((n_1, n_2), e_3, (e_3_a, (e_3_b, 10), (e_3_c, (1, 2, 3)), (e_3_d, 20, (4, 5, 6))))
*/

/*
SMART_ENUM_IMPL_FULL_NAME(_, e_1)
SMART_ENUM_IMPL_FULL_NAME((n_1), e_1)
SMART_ENUM_IMPL_FULL_NAME((n_1, n_2), e_1)
*/

SMART_ENUM_IMPL_FULL_NAME_STRING(_, e_1)
SMART_ENUM_IMPL_FULL_NAME_STRING((n_1), e_1)
SMART_ENUM_IMPL_FULL_NAME_STRING((n_1, n_2), e_1)

int main()
{
    return 0;
}
