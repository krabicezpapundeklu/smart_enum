
//          Copyright Jarda Flieger 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <iostream>

#include "smart_enum.hpp"

SMART_ENUM
(
    e_1, (e_1_a, (e_1_b, 10), e_1_c)
)

SMART_ENUM_CLASS
(
    (e_c_1, short), (a, b, c)
)

using namespace smart_enum;

void examples_count()
{
    static_assert(count<e_1>() == 3, "count<e_1>() != 3");
}

void examples_enum_size()
{
    static_assert(sizeof(e_c_1) == sizeof(short), "sizeof(e_1_c) != sizeof(short)");
}

void examples_enum_values()
{
    static_assert(e_1::e_1_a ==  0, "e_1::e_1_a !=  0");
    static_assert(e_1::e_1_b == 10, "e_1::e_1_b != 10");
    static_assert(e_1::e_1_c == 11, "e_1::e_1_c != 11");
}

void examples_from_string()
{
    static_assert(from_string<e_1>("e_1_a") == e_1::e_1_a,
        "from_string<e_1>(\"e_1_a\") != e_1::e_1_a");

    static_assert(from_string<e_1>("e_1_b") == e_1::e_1_b,
        "from_string<e_1>(\"e_1_b\") != e_1::e_1_b");

    static_assert(from_string<e_1>("e_1_c") == e_1::e_1_c,
        "from_string<e_1>(\"e_1_c\") != e_1::e_1_c");

    try
    {
        from_string<e_1>("x");
        assert(false);
    }
    catch(const std::invalid_argument &)
    {
    }
}

void examples_index_of()
{
    static_assert(index_of(e_1::e_1_a) == 0, "index_of(e_1::e_1_a) != 0");
    static_assert(index_of(e_1::e_1_c) == 2, "index_of(e_1::e_1_c) != 2");
}

void examples_is_enum_class()
{
    static_assert(!is_enum_class<e_1>(), "e_1 == enum class");
    static_assert(is_enum_class<e_c_1>(), "e_c_1 != enum class");
}

void examples_iterators()
{
    using e_1_iterator = enum_iterator<e_1>;

    auto i = e_1_iterator{e_1::e_1_a};
    auto e = e_1_iterator{};

    assert(i[0] == e_1_a);
    assert(i[1] == e_1_b);

    assert(e - i == static_cast<std::ptrdiff_t>(count<e_1>()));

    for(; i != e; ++i)
    {
        std::cout << to_string(*i) << " = " << *i << std::endl;
    }
}

void examples_name()
{
    // WARNING: 'detail::equal' is implementation detail!
    static_assert(detail::equal(name<e_1>(), "e_1"), "name<e_1>() != \"e_1\"");
}

void examples_to_string()
{
    // WARNING: 'detail::equal' is implementation detail!
    static_assert(detail::equal(to_string(e_1::e_1_a), "e_1_a"), "to_string(e_1::e_1_a) != \"e_1_a\"");
}

void examples_value_of()
{
    static_assert(value_of<e_1>(0) == e_1::e_1_a, "value_of<e_1>(0) != e_1::e_1_a");
    static_assert(value_of<e_1>(2) == e_1::e_1_c, "value_of<e_1>(2) != e_1::e_1_c");

    try
    {
        value_of<e_1>(3);
        assert(false);
    }
    catch(const std::invalid_argument &)
    {
    }
}

int main()
{
    examples_count();
    examples_enum_size();
    examples_enum_values();
    examples_from_string();
    examples_index_of();
    examples_is_enum_class();
    examples_iterators();
    examples_name();
    examples_to_string();

    return 0;
}
