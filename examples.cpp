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
        e_1_a, (e_1_b, 10), (e_1_c, "e_1::c"), (e_1_d, e_1_a + 1, "e_1::d"), (e_1_e, "e_1::e", 30)
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
    // e_1
    using e_1_traits = smart_enum::enum_traits<e_1>;

    static_assert(!e_1_traits::is_enum_class, "e_1 == enum class");

    static_assert(e_1::e_1_a ==  0, "e_1_a !=  0");
    static_assert(e_1::e_1_b == 10, "e_1_b != 10");
    static_assert(e_1::e_1_c == 11, "e_1_c != 11");
    static_assert(e_1::e_1_d ==  1, "e_1_d !=  1");
    static_assert(e_1::e_1_e == 30, "e_1_e != 30");

    static_assert(e_1_traits::count == 5, "e_1 count != 5");

    assert(!strcmp(e_1_traits::description(e_1::e_1_a), "e_1_a"));
    assert(!strcmp(e_1_traits::description(e_1::e_1_b), "e_1_b"));
    assert(!strcmp(e_1_traits::description(e_1::e_1_c), "e_1::c"));
    assert(!strcmp(e_1_traits::description(e_1::e_1_d), "e_1::d"));
    assert(!strcmp(e_1_traits::description(e_1::e_1_e), "e_1::e"));

    assert(!strcmp(e_1_traits::name, "e_1"));

    static_assert(e_1_traits::value(0) == e_1::e_1_a, "e_1 value[0] != e_1_a");
    static_assert(e_1_traits::value(1) == e_1::e_1_b, "e_1 value[1] != e_1_b");
    static_assert(e_1_traits::value(2) == e_1::e_1_c, "e_1 value[2] != e_1_c");
    static_assert(e_1_traits::value(3) == e_1::e_1_d, "e_1 value[3] != e_1_d");
    static_assert(e_1_traits::value(4) == e_1::e_1_e, "e_1 value[4] != e_1_e");

    // e_2
    static_assert(sizeof(e_2) == sizeof(short), "sizeof(e_2) != sizeof(short)");

    // e_c_1
    static_assert(smart_enum::enum_traits<e_c_1>::is_enum_class, "e_c_1 != enum class");

    // e_3
    static_assert(!smart_enum::enum_traits<e_3>::is_enum_class, "e_3 == enum class");

    // e_c_2
    static_assert(smart_enum::enum_traits<e_c_2>::is_enum_class, "e_c_2 != enum class");

    return 0;
}
