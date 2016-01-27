
//          Copyright Jarda Flieger 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SMART_ENUM_HEADER_INCLUDED
#define SMART_ENUM_HEADER_INCLUDED

// clang++ examples.cpp -I. -std=c++11 -Werror -Weverything -Wno-c++98-compat-pedantic (3.5.2)
// g++ examples.cpp -I. -std=c++11 -Wall -Weffc++ -Werror -Wextra -pedantic (4.7.3, 4.9.2)

#include <boost/preprocessor/punctuation/remove_parens.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/tuple/pop_front.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>

#define SMART_ENUM(...) \
    SMART_ENUM_IMPL(, __VA_ARGS__)

#define SMART_ENUM_CLASS(...) \
    SMART_ENUM_IMPL(class, __VA_ARGS__)

#define SMART_ENUM_IMPL(CLASS, ...) \
    SMART_ENUM_IMPL_1(CLASS, (SMART_ENUM_IMPL_ARGS_TO_TUPLES((__VA_ARGS__))))

#define SMART_ENUM_IMPL_1(CLASS, ENUM) \
    BOOST_PP_IF \
    ( \
        BOOST_PP_SUB(BOOST_PP_TUPLE_SIZE(ENUM), 2), \
            SMART_ENUM_IMPL_NAMESPACES(CLASS, ENUM, BOOST_PP_TUPLE_ELEM(0, ENUM)), \
            SMART_ENUM_IMPL_DEFINITION(CLASS, ENUM) \
    )

#define SMART_ENUM_IMPL_ARG_TO_TUPLE(ARG) \
    (BOOST_PP_REMOVE_PARENS(ARG))

#define SMART_ENUM_IMPL_ARGS_TO_TUPLES(ARGS) \
    BOOST_PP_ENUM(BOOST_PP_TUPLE_SIZE(ARGS), SMART_ENUM_IMPL_ARGS_TO_TUPLES_1, ARGS)

#define SMART_ENUM_IMPL_ARGS_TO_TUPLES_1(_, INDEX, ARGS) \
    SMART_ENUM_IMPL_ARG_TO_TUPLE(BOOST_PP_TUPLE_ELEM(INDEX, ARGS))

#define SMART_ENUM_IMPL_DEFINITION(CLASS, ENUM) \
    enum CLASS SMART_ENUM_IMPL_NAME_SIZE(BOOST_PP_TUPLE_ELEM(0, ENUM)) \
    { \
    };

#define SMART_ENUM_IMPL_FOR_EACH(TUPLE, MACRO) \
    BOOST_PP_REPEAT(BOOST_PP_TUPLE_SIZE(TUPLE), MACRO, TUPLE)

#define SMART_ENUM_IMPL_NAME_SIZE(NAME_SIZE) \
    BOOST_PP_TUPLE_ELEM(0, NAME_SIZE) \
    BOOST_PP_IIF \
    ( \
        BOOST_PP_DEC(BOOST_PP_TUPLE_SIZE(NAME_SIZE)), \
            : SMART_ENUM_IMPL_REMOVE_PARENS BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_TO_SEQ(NAME_SIZE)), \
    )

#define SMART_ENUM_IMPL_NAMESPACES(CLASS, ENUM, NAMESPACES) \
    SMART_ENUM_IMPL_FOR_EACH(NAMESPACES, SMART_ENUM_IMPL_NAMESPACE_START) \
        SMART_ENUM_IMPL_DEFINITION(CLASS, BOOST_PP_TUPLE_POP_FRONT(ENUM)) \
    SMART_ENUM_IMPL_FOR_EACH(NAMESPACES, SMART_ENUM_IMPL_NAMESPACE_END)

#define SMART_ENUM_IMPL_NAMESPACE_END(_, INDEX, NAMESPACES) \
    }

#define SMART_ENUM_IMPL_NAMESPACE_START(_, INDEX, NAMESPACES) \
    namespace BOOST_PP_TUPLE_ELEM(INDEX, NAMESPACES) {

#define SMART_ENUM_IMPL_REMOVE_PARENS(ARG) \
    ARG

#endif
