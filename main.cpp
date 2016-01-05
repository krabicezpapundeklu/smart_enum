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
    static_assert(e_1::a ==  0, "");
    static_assert(e_1::b == 10, "");
    static_assert(e_1::c == 11, "");
    static_assert(e_1::d ==  1, "");
    static_assert(e_1::e ==  5, "");

    assert(!strcmp(enum_description(e_1::a), "a"));
    assert(!strcmp(enum_description(e_1::b), "b"));
    assert(!strcmp(enum_description(e_1::c), "ccc"));
    assert(!strcmp(enum_description(e_1::d), "ddd"));
    assert(!strcmp(enum_description(e_1::e), "eee"));

    static_assert(sizeof(e_2) == sizeof(short), "");

    return 0;
}
