
//          Copyright Jarda Flieger 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SMART_ENUM_HEADER_INCLUDED
#define SMART_ENUM_HEADER_INCLUDED

#include <type_traits>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/pop_front.hpp>
#include <boost/preprocessor/tuple/replace.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/vmd/is_tuple.hpp>

#define SMART_ENUM(NAME, VALUES) \
    SMART_ENUM_IMPL(, NAME, VALUES)

#define SMART_ENUM_CLASS(NAME, VALUES) \
    SMART_ENUM_IMPL(class, NAME, VALUES)

#define SMART_ENUM_IMPL(CLASS, NAME, VALUES) \
    SMART_ENUM_IMPL_WITH_VALUE_TUPLES(CLASS, NAME, SMART_ENUM_IMPL_ARGS_TO_TUPLES(VALUES))

#define SMART_ENUM_IMPL_WITH_VALUE_TUPLES(CLASS, NAME, VALUES) \
    enum CLASS \
        BOOST_PP_IIF(BOOST_VMD_IS_TUPLE(NAME), SMART_ENUM_IMPL_NAME_SIZE(NAME), NAME) \
    { \
        SMART_ENUM_IMPL_ENUM_VALUES(VALUES) \
    }; \
    \
    SMART_ENUM_IMPL_TRAITS(NAME, VALUES)

//     a  => (a)
// (a, b) => (a, b)
#define SMART_ENUM_IMPL_ARG_TO_TUPLE(ARG) \
    BOOST_PP_IIF(BOOST_VMD_IS_TUPLE(ARG), ARG, (ARG))

// (a, (b, 1), c) => ((a), (b, 1), (c))
#define SMART_ENUM_IMPL_ARGS_TO_TUPLES(ARGS) \
    (BOOST_PP_ENUM(BOOST_PP_TUPLE_SIZE(ARGS), SMART_ENUM_IMPL_ARGS_TO_TUPLES_1, ARGS))

#define SMART_ENUM_IMPL_ARGS_TO_TUPLES_1(_, INDEX, ARGS) \
    SMART_ENUM_IMPL_ARG_TO_TUPLE(BOOST_PP_TUPLE_ELEM(INDEX, ARGS))

// (a, (b, 1), (c, 2)) =>
//  a = smart_enum::detail::get_value_or_default(0),
//  b = smart_enum::detail::get_value_or_default(a + 1, 1),
//  c = smart_enum::detail::get_value_or_default(b + 1, 2)
#define SMART_ENUM_IMPL_ENUM_VALUES(VALUES) \
    BOOST_PP_ENUM( \
        BOOST_PP_TUPLE_SIZE(VALUES), \
        SMART_ENUM_IMPL_ENUM_VALUES_1, \
        VALUES \
    )

#define SMART_ENUM_IMPL_ENUM_VALUES_1(_, INDEX, VALUES) \
    SMART_ENUM_IMPL_VALUE_HEAD(INDEX, VALUES) = \
        smart_enum::detail::get_value_or_default \
            BOOST_PP_IF(INDEX, \
                BOOST_PP_TUPLE_REPLACE( \
                    BOOST_PP_TUPLE_ELEM(INDEX, VALUES), \
                    0, \
                    SMART_ENUM_IMPL_VALUE_HEAD(BOOST_PP_DEC(INDEX), VALUES) + 1 \
                ), \
                BOOST_PP_TUPLE_REPLACE(BOOST_PP_TUPLE_ELEM(INDEX, VALUES), 0, 0) \
            )

#define SMART_ENUM_IMPL_FROM_STRING(_, INDEX, NAME_VALUES) \
    smart_enum::detail::equal( \
        s, BOOST_PP_STRINGIZE(SMART_ENUM_IMPL_VALUE_HEAD(INDEX, BOOST_PP_SEQ_ELEM(1, NAME_VALUES)))) \
            ? BOOST_PP_SEQ_ELEM(0, NAME_VALUES) :: \
                SMART_ENUM_IMPL_VALUE_HEAD(INDEX, BOOST_PP_SEQ_ELEM(1, NAME_VALUES)) :

#define SMART_ENUM_IMPL_INDEX_OF(_, INDEX, NAME_VALUES) \
    value == BOOST_PP_SEQ_ELEM(0, NAME_VALUES) :: \
        SMART_ENUM_IMPL_VALUE_HEAD(INDEX, BOOST_PP_SEQ_ELEM(1, NAME_VALUES)) ? INDEX :

// (name, size) => name : size
#define SMART_ENUM_IMPL_NAME_SIZE(NAME_SIZE) \
    BOOST_PP_TUPLE_ELEM(0, NAME_SIZE) : BOOST_PP_TUPLE_ELEM(1, NAME_SIZE)

#define SMART_ENUM_IMPL_TO_STRING(_, NAME, VALUE) \
    value == NAME::BOOST_PP_TUPLE_ELEM(0, VALUE) \
        ? BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(0, VALUE)) :

#define SMART_ENUM_IMPL_TRAITS(NAME, VALUES) \
    SMART_ENUM_IMPL_TRAITS_1( \
        BOOST_PP_TUPLE_ELEM(0, SMART_ENUM_IMPL_ARG_TO_TUPLE(NAME)), \
        VALUES \
    )

#define SMART_ENUM_IMPL_TRAITS_1(NAME, VALUES) \
    namespace smart_enum \
    { \
        template<> struct enum_traits<NAME> : detail::enum_traits_base<NAME> \
        { \
            static constexpr std::size_t count = BOOST_PP_TUPLE_SIZE(VALUES); \
            static constexpr const char *name = BOOST_PP_STRINGIZE(NAME); \
            \
            static constexpr NAME from_string(const char *s) \
            { \
                /* TODO: assert */ \
                return BOOST_PP_REPEAT( \
                    BOOST_PP_TUPLE_SIZE(VALUES), SMART_ENUM_IMPL_FROM_STRING, (NAME)(VALUES) \
                ) value(0); \
            } \
            \
            static constexpr std::size_t index_of(NAME value) \
            { \
                return BOOST_PP_REPEAT( \
                    BOOST_PP_TUPLE_SIZE(VALUES), SMART_ENUM_IMPL_INDEX_OF, (NAME)(VALUES) \
                ) 0; \
            } \
            \
            static constexpr const char *to_string(NAME value) \
            { \
                return BOOST_PP_SEQ_FOR_EACH( \
                    SMART_ENUM_IMPL_TO_STRING, NAME, BOOST_PP_TUPLE_TO_SEQ(VALUES) \
                ) ""; \
            } \
            \
            static constexpr NAME value(std::size_t index) \
            { \
                /* TODO: assert(index <= count); */ \
                \
                return BOOST_PP_REPEAT( \
                    BOOST_PP_TUPLE_SIZE(VALUES), SMART_ENUM_IMPL_VALUE, (NAME)(VALUES) \
                ) value(0); \
            } \
        }; \
    }

#define SMART_ENUM_IMPL_VALUE(_, INDEX, NAME_VALUES) \
    index == INDEX ? BOOST_PP_SEQ_ELEM(0, NAME_VALUES) :: \
        SMART_ENUM_IMPL_VALUE_HEAD(INDEX, BOOST_PP_SEQ_ELEM(1, NAME_VALUES)) :

// 0, ((a, 0), (b, 1)) => a
// 1, ((a, 0), (b, 1)) => b
#define SMART_ENUM_IMPL_VALUE_HEAD(INDEX, VALUES) \
    BOOST_PP_TUPLE_ELEM(0, BOOST_PP_TUPLE_ELEM(INDEX, VALUES))

namespace smart_enum
{
    namespace detail
    {
        template
        <
            typename T
        >
        struct enum_traits_base
        {
            static constexpr bool is_enum_class =
                std::integral_constant
                <
                    bool, std::is_enum<T>::value && !std::is_convertible<T, int>::value
                >::value;
        };

        template
        <
            typename T
        >
        constexpr T get_value_or_default(T default_value)
        {
            return default_value;
        }

        template
        <
            typename T, typename U
        >
        constexpr U get_value_or_default(T /* default_value */, U value)
        {
            return value;
        }

        constexpr bool equal_helper(const char *x, const char *y)
        {
            return *x == *y && (*x == '\0' || equal_helper(x + 1, y + 1));
        }

        constexpr bool equal(const char *x, const char *y)
        {
            return (x == nullptr && y == nullptr) || (x && y && equal_helper(x, y));
        }
    }

    template
    <
        typename T
    >
    struct enum_traits : detail::enum_traits_base<T>
    {
    };

    template
    <
        typename T
    >
    class enum_iterator : public boost::iterator_facade
        <
            enum_iterator<T>,
            T,
            boost::random_access_traversal_tag,
            T
        >
    {
    public:
        constexpr enum_iterator()
            : index_{enum_traits<T>::count}
        {

        }

        constexpr explicit enum_iterator(T value)
            : index_{enum_traits<T>::index_of(value)}
        {
        }

    private:
        std::size_t index_;

        void advance(std::ptrdiff_t n)
        {
            index_ += n;
        }

        void decrement()
        {
            --index_;
        }

        constexpr T dereference() const
        {
            return enum_traits<T>::value(index_);
        }

        constexpr std::ptrdiff_t distance_to(const enum_iterator &other) const
        {
            // TODO
            return static_cast<std::ptrdiff_t>(other.index_ - index_);
        }

        constexpr bool equal(const enum_iterator &other) const
        {
            return other.index_ == index_;
        }

        void increment()
        {
            ++index_;
        }

        friend class boost::iterator_core_access;
    };
}

#endif
