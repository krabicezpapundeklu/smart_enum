#include <cassert>
#include <cstring>

#include "smart_enum.hpp"

SMART_ENUM
(
    e_1,
    (
        a,
        (b, 10),
        (c, "ccc"),
        (d, 1, "ddd"),
        (e, "eee", 5)
    )
)

SMART_ENUM_CLASS
(
    (e_2, short),
    (
        a,
        b,
        c
    )
)

int main()
{
    using smart_enum::enum_traits;

    static_assert(e_1::a ==  0, "");
    static_assert(e_1::b == 10, "");
    static_assert(e_1::c == 11, "");
    static_assert(e_1::d ==  1, "");
    static_assert(e_1::e ==  5, "");

    static_assert(enum_traits<e_1>::count == 5, "");
    static_assert(enum_traits<e_2>::count == 3, "");

    assert(!strcmp(enum_traits<e_1>::description(e_1::a), "a"));
    assert(!strcmp(enum_traits<e_1>::description(e_1::b), "b"));
    assert(!strcmp(enum_traits<e_1>::description(e_1::c), "ccc"));
    assert(!strcmp(enum_traits<e_1>::description(e_1::d), "ddd"));
    assert(!strcmp(enum_traits<e_1>::description(e_1::e), "eee"));

    static_assert(sizeof(e_2) == sizeof(short), "");

    return 0;
}
