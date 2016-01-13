
//          Copyright Jarda Flieger 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <cstring>

#include "smart_enum.hpp"

/*
    enum e_1
    {
        e_1_a,
        e_1_b = 10,
        e_1_c,
        e_1_d = e_1_a + 1,
        e_1_e = 30
    };
*/
SMART_ENUM
(
    e_1,
    (
        e_1_a, (e_1_b, 10), e_1_c, (e_1_d, e_1_a + 1), (e_1_e, 30)
    )
)

/*
    enum e_2 : short
    {
        e_2_a,
        e_2_b,
        e_2_c
    };
*/
SMART_ENUM
(
    (e_2, short),
    (
        e_2_a, e_2_b, e_2_c
    )
)

/*
    enum class e_c_1
    {
        a,
        b,
        c
    };
*/
SMART_ENUM_CLASS
(
    e_c_1,
    (
        a, b, c
    )
)

enum e_3
{
};

enum class e_c_2
{
};

int main()
{
    using namespace smart_enum;

    // e_1
    static_assert(!is_enum_class<e_1>(), "e_1 == enum class");

    static_assert(e_1::e_1_a ==  0, "e_1_a !=  0");
    static_assert(e_1::e_1_b == 10, "e_1_b != 10");
    static_assert(e_1::e_1_c == 11, "e_1_c != 11");
    static_assert(e_1::e_1_d ==  1, "e_1_d !=  1");
    static_assert(e_1::e_1_e == 30, "e_1_e != 30");

    static_assert(count<e_1>() == 5, "e_1 count != 5");

    static_assert(from_string<e_1>("e_1_a") == e_1::e_1_a, "!e_1_a");
    static_assert(from_string<e_1>("e_1_b") == e_1::e_1_b, "!e_1_b");
    static_assert(from_string<e_1>("e_1_c") == e_1::e_1_c, "!e_1_c");
    static_assert(from_string<e_1>("e_1_d") == e_1::e_1_d, "!e_1_d");
    static_assert(from_string<e_1>("e_1_e") == e_1::e_1_e, "!e_1_e");

    static_assert(index_of(e_1::e_1_a) == 0, "!0");
    static_assert(index_of(e_1::e_1_b) == 1, "!1");
    static_assert(index_of(e_1::e_1_c) == 2, "!2");
    static_assert(index_of(e_1::e_1_d) == 3, "!3");
    static_assert(index_of(e_1::e_1_e) == 4, "!4");

    assert(!strcmp(to_string(e_1::e_1_a), "e_1_a"));
    assert(!strcmp(to_string(e_1::e_1_b), "e_1_b"));
    assert(!strcmp(to_string(e_1::e_1_c), "e_1_c"));
    assert(!strcmp(to_string(e_1::e_1_d), "e_1_d"));
    assert(!strcmp(to_string(e_1::e_1_e), "e_1_e"));

    assert(!strcmp(name<e_1>(), "e_1"));

    static_assert(value_of<e_1>(0) == e_1::e_1_a, "e_1 value[0] != e_1_a");
    static_assert(value_of<e_1>(1) == e_1::e_1_b, "e_1 value[1] != e_1_b");
    static_assert(value_of<e_1>(2) == e_1::e_1_c, "e_1 value[2] != e_1_c");
    static_assert(value_of<e_1>(3) == e_1::e_1_d, "e_1 value[3] != e_1_d");
    static_assert(value_of<e_1>(4) == e_1::e_1_e, "e_1 value[4] != e_1_e");

    using e_1_iterator = smart_enum::enum_iterator<e_1>;

    //assert(e_1_iterator{} - e_1_iterator{e_1::e_1_a} == count<e_1>());

    // e_2
    static_assert(sizeof(e_2) == sizeof(short), "sizeof(e_2) != sizeof(short)");

    // e_c_1
    static_assert(is_enum_class<e_c_1>(), "e_c_1 != enum class");

    // e_3
    static_assert(!is_enum_class<e_3>(), "e_3 == enum class");

    // e_c_2
    static_assert(is_enum_class<e_c_2>(), "e_c_2 != enum class");

    return 0;
}
