#include <cassert>
#include <cstring>
#include <iostream>

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

template
<
    typename T
>
void print(std::ostream &stream)
{
    using enum_traits = smart_enum::enum_traits<T>;

    stream << enum_traits::name << " = {";

    for(auto i = 0u; i < enum_traits::count; ++i)
    {
        if(i > 0)
        {
            stream << ", ";
        }

        auto v = enum_traits::value(i);
        auto d = enum_traits::description(v);

        stream << static_cast<typename std::underlying_type<T>::type>(v) << ": \"" << d << '"';
    }

    stream << '}' << std::endl;
}

int main()
{
    using e1_enum_traits = smart_enum::enum_traits<e_1>;
    using e2_enum_traits = smart_enum::enum_traits<e_2>;

    static_assert(e_1::a ==  0, "");
    static_assert(e_1::b == 10, "");
    static_assert(e_1::c == 11, "");
    static_assert(e_1::d ==  1, "");
    static_assert(e_1::e ==  5, "");

    static_assert(e1_enum_traits::count == 5, "");
    static_assert(e2_enum_traits::count == 3, "");

    assert(!strcmp(e1_enum_traits::description(e_1::a), "a"));
    assert(!strcmp(e1_enum_traits::description(e_1::b), "b"));
    assert(!strcmp(e1_enum_traits::description(e_1::c), "ccc"));
    assert(!strcmp(e1_enum_traits::description(e_1::d), "ddd"));
    assert(!strcmp(e1_enum_traits::description(e_1::e), "eee"));

    static_assert(sizeof(e_2) == sizeof(short), "");

    print<e_1>(std::cout);
    print<e_2>(std::cout);

    return 0;
}
