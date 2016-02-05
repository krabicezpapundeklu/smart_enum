
//          Copyright Jarda Flieger 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "smart_enum.hpp"

#include <cassert>
#include <cstring>
#include <iostream>

using namespace smart_enum;

SMART_ENUM(e_1, (e_1_a, (e_1_b, 10), (e_1_c, (1, 2, "x")), (e_1_d, 20, (4, 5, "y"))))
SMART_ENUM(n_1, (e_2, short), (e_2_a, (e_2_b, 10), (e_2_c, (1, 2, "x")), (e_2_d, 20, (4, 5, "y"))))
SMART_ENUM((n_1, n_2), e_3, (e_3_a, (e_3_b, 10), (e_3_c, (1, 2, "x")), (e_3_d, 20, (4, 5, "y"))))

#define STATIC_ASSERT(EXPR) \
    static_assert(EXPR, "! " # EXPR)

constexpr bool equal(const char *x, const char *y);
constexpr bool equal_helper(const char *x, const char *y);

void test_additional_data();
void test_count();
void test_from_string();
void test_full_name();
void test_index_of();
void test_iterators();
void test_name();
void test_range();
void test_size();
void test_to_string();
void test_value_of();

constexpr bool equal(const char *x, const char *y)
{
    return (x == nullptr && y == nullptr) || (x && y && equal_helper(x, y));
}

constexpr bool equal_helper(const char *x, const char *y)
{
    return *x == *y && (*x == '\0' || equal_helper(x + 1, y + 1));
}

void test_count()
{
    STATIC_ASSERT(count<e_1>() == 4);
    STATIC_ASSERT(count<n_1::e_2>() == 4);
    STATIC_ASSERT(count<n_1::n_2::e_3>() == 4);
}

void test_from_string()
{
    assert(from_string<e_1>("e_1_a") == e_1::e_1_a);
    assert(from_string<n_1::e_2>("e_2_a") == n_1::e_2::e_2_a);
    assert(from_string<n_1::n_2::e_3>("e_3_a") == n_1::n_2::e_3::e_3_a);
}

void test_full_name()
{
    STATIC_ASSERT(equal(full_name<e_1>(), "e_1"));
    STATIC_ASSERT(equal(full_name<n_1::e_2>(), "n_1::e_2"));
    STATIC_ASSERT(equal(full_name<n_1::n_2::e_3>(), "n_1::n_2::e_3"));
}

void test_index_of()
{
    STATIC_ASSERT(index_of(e_1::e_1_a) == 0);
    STATIC_ASSERT(index_of(e_1::e_1_b) == 1);
    STATIC_ASSERT(index_of(e_1::e_1_c) == 2);
    STATIC_ASSERT(index_of(e_1::e_1_d) == 3);
}

void test_iterators()
{
    auto i = begin<e_1>();
    auto j = end<e_1>();

    assert(i[0] == e_1::e_1_a);
    assert(i[3] == e_1::e_1_d);

    assert(static_cast<std::size_t>(j - i) == count<e_1>());

    assert(*(j - 1) == e_1::e_1_d);

    for(; i != j; ++i)
    {
        std::cout << to_string(*i) << " = " << *i << std::endl;
    }
}

void test_name()
{
    STATIC_ASSERT(equal(name<e_1>(), "e_1"));
    STATIC_ASSERT(equal(name<n_1::e_2>(), "e_2"));
    STATIC_ASSERT(equal(name<n_1::n_2::e_3>(), "e_3"));
}

void test_range()
{
    for(auto e : range<e_1>())
    {
        std::cout << to_string(e) << " = " << e << std::endl;
    }
}

void test_size()
{
    STATIC_ASSERT(sizeof(n_1::e_2) == sizeof(short));
}

void test_to_string()
{
    STATIC_ASSERT(equal(to_string(e_1::e_1_a), "e_1_a"));
    STATIC_ASSERT(equal(to_string(n_1::e_2::e_2_a), "e_2_a"));
    STATIC_ASSERT(equal(to_string(n_1::n_2::e_3::e_3_a), "e_3_a"));
}

void test_value_of()
{
    STATIC_ASSERT(value_of<e_1>(0) == e_1::e_1_a);
    STATIC_ASSERT(value_of<e_1>(1) == e_1::e_1_b);
    STATIC_ASSERT(value_of<e_1>(2) == e_1::e_1_c);
    STATIC_ASSERT(value_of<e_1>(3) == e_1::e_1_d);
}

int main()
{
    test_count();
    test_from_string();
    test_full_name();
    test_index_of();
    test_iterators();
    test_name();
    test_range();
    test_size();
    test_to_string();
    test_value_of();

    return 0;
}
