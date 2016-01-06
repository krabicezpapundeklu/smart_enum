#ifndef SMART_ENUM_HEADER_INCLUDED
#define SMART_ENUM_HEADER_INCLUDED

#include <type_traits>

#include <boost/core/enable_if.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/insert.hpp>
#include <boost/preprocessor/tuple/pop_front.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/vmd/is_tuple.hpp>

#define SMART_ENUM(NAME, VALUES) \
    SMART_ENUM_IMPL(, NAME, VALUES)

#define SMART_ENUM_CLASS(NAME, VALUES) \
    SMART_ENUM_IMPL(class, NAME, VALUES)

#define SMART_ENUM_IMPL(CLASS, NAME, VALUES) \
    enum CLASS \
        BOOST_PP_IIF(BOOST_VMD_IS_TUPLE(NAME), SMART_ENUM_IMPL_NAME_SIZE(NAME), NAME) \
    { \
        SMART_ENUM_IMPL_ENUM_VALUES(VALUES) \
    }; \
    \
    SMART_ENUM_IMPL_DESCRIPTION(NAME, VALUES)

//     a  => (a)
// (a, b) => (a, b)
#define SMART_ENUM_IMPL_ARG_TO_TUPLE(ARG) \
    BOOST_PP_IIF(BOOST_VMD_IS_TUPLE(ARG), ARG, (ARG))

// (a, (b, 1), c) => ((a), (b, 1), (c))
#define SMART_ENUM_IMPL_ARGS_TO_TUPLES(ARGS) \
    (BOOST_PP_ENUM(BOOST_PP_TUPLE_SIZE(ARGS), SMART_ENUM_IMPL_ARGS_TO_TUPLES_1, ARGS))

#define SMART_ENUM_IMPL_ARGS_TO_TUPLES_1(_, INDEX, ARGS) \
    SMART_ENUM_IMPL_ARG_TO_TUPLE(BOOST_PP_TUPLE_ELEM(INDEX, ARGS))

#define SMART_ENUM_IMPL_DESCRIPTION(NAME, VALUES) \
    SMART_ENUM_IMPL_DESCRIPTION_1( \
        BOOST_PP_TUPLE_ELEM(0, SMART_ENUM_IMPL_ARG_TO_TUPLE(NAME)), \
        BOOST_PP_TUPLE_TO_SEQ(SMART_ENUM_IMPL_ARGS_TO_TUPLES(VALUES)) \
    )

#define SMART_ENUM_IMPL_DESCRIPTION_1(NAME, VALUES) \
    constexpr const char *enum_description(NAME value) \
    { \
        return BOOST_PP_SEQ_FOR_EACH(SMART_ENUM_IMPL_DESCRIPTION_2, NAME, VALUES) ""; \
    }

#define SMART_ENUM_IMPL_DESCRIPTION_2(_, NAME, VALUE) \
    value == NAME::BOOST_PP_TUPLE_ELEM(0, VALUE) ? \
        smart_enum::get_value_or_default \
            BOOST_PP_TUPLE_POP_FRONT( \
                BOOST_PP_TUPLE_INSERT(VALUE, 1, BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(0, VALUE))) \
            ) :

//         (a), 1 => (1)
//      (a, 1), 2 => (2, 1)
// (a, 1, "x"), 3 => (3, 1, "x")
#define SMART_ENUM_IMPL_ENUM_VALUE_ARGS(VALUE, DEFAULT_VALUE) \
    BOOST_PP_TUPLE_POP_FRONT(BOOST_PP_TUPLE_INSERT(VALUE, 1, DEFAULT_VALUE))

// (a, (b, 1), (c, 2, "x")) =>
//  a = smart_enum::get_value_or_default(0),
//  b = smart_enum::get_value_or_default(a + 1, 1),
//  c = smart_enum::get_value_or_default(b + 1, 2, "x")
#define SMART_ENUM_IMPL_ENUM_VALUES(VALUES) \
    BOOST_PP_ENUM( \
        BOOST_PP_TUPLE_SIZE(VALUES), \
        SMART_ENUM_IMPL_ENUM_VALUES_1, \
        SMART_ENUM_IMPL_ARGS_TO_TUPLES(VALUES) \
    )

#define SMART_ENUM_IMPL_ENUM_VALUES_1(_, INDEX, VALUES) \
    SMART_ENUM_IMPL_VALUE_HEAD(INDEX, VALUES) = \
        smart_enum::get_value_or_default \
            BOOST_PP_IF(INDEX, \
                SMART_ENUM_IMPL_ENUM_VALUE_ARGS( \
                    BOOST_PP_TUPLE_ELEM(INDEX, VALUES), \
                    SMART_ENUM_IMPL_VALUE_HEAD(BOOST_PP_DEC(INDEX), VALUES) + 1 \
                ), \
                SMART_ENUM_IMPL_ENUM_VALUE_ARGS(BOOST_PP_TUPLE_ELEM(INDEX, VALUES), 0) \
            )

// (name, size) => name : size
#define SMART_ENUM_IMPL_NAME_SIZE(NAME_SIZE) \
    BOOST_PP_TUPLE_ELEM(0, NAME_SIZE) : BOOST_PP_TUPLE_ELEM(1, NAME_SIZE)

// 0, ((a, 0), (b, 1)) => a
// 1, ((a, 0), (b, 1)) => b
#define SMART_ENUM_IMPL_VALUE_HEAD(INDEX, VALUES) \
    BOOST_PP_TUPLE_ELEM(0, BOOST_PP_TUPLE_ELEM(INDEX, VALUES))

namespace smart_enum
{
    // get_value_or_default(default_value [, value [, value...]])
    //  => return 1st "value" compatible with "default_value" or "default_value" if no such value exists
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
        typename T,
        typename U,
        typename... Args,
        typename boost::enable_if<std::is_convertible<U, T>, int>::type = 0
    >
    constexpr U get_value_or_default(T, U value, Args...)
    {
        return value;
    }

    template
    <
        typename T,
        typename U,
        typename... Args,
        typename boost::disable_if<std::is_convertible<U, T>, int>::type = 0
    >
    constexpr auto get_value_or_default(T default_value, U, Args... args)
        -> decltype(get_value_or_default(default_value, args...))
    {
        return get_value_or_default(default_value, args...);
    }
}

#endif
