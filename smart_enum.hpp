

//          Copyright Jarda Flieger 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SMART_ENUM_HEADER_INCLUDED
#define SMART_ENUM_HEADER_INCLUDED

#include <stdexcept>

#include <boost/preprocessor.hpp>

#define SMART_ENUM(...) \
    SMART_ENUM_IMPL(, __VA_ARGS__)

#define SMART_ENUM_CLASS(...) \
    SMART_ENUM_IMPL(class, __VA_ARGS__)

#ifdef _MSC_VER
    #define SMART_ENUM_IMPL(CLASS, ...) \
        BOOST_PP_CAT \
        ( \
            BOOST_PP_OVERLOAD(SMART_ENUM_IMPL_, __VA_ARGS__)(CLASS, __VA_ARGS__), \
            BOOST_PP_EMPTY() \
        )
#else
    #define SMART_ENUM_IMPL(CLASS, ...) \
        BOOST_PP_OVERLOAD(SMART_ENUM_IMPL_, __VA_ARGS__)(CLASS, __VA_ARGS__)
#endif

#define SMART_ENUM_IMPL_2(CLASS, NAME, MEMBERS) \
    SMART_ENUM_IMPL_DEFINITION(CLASS, _, NAME, MEMBERS)

#define SMART_ENUM_IMPL_3(CLASS, NAMESPACES, NAME, MEMBERS) \
    SMART_ENUM_IMPL_DEFINITION(CLASS, SMART_ENUM_IMPL_ARG_TO_TUPLE(NAMESPACES), NAME, MEMBERS)

#define SMART_ENUM_IMPL_DEFINITION(CLASS, NAMESPACES, NAME, MEMBERS) \
    SMART_ENUM_IMPL_DEFINITION_1 \
    ( \
        CLASS, NAMESPACES, SMART_ENUM_IMPL_ARG_TO_TUPLE(NAME), (SMART_ENUM_IMPL_ARGS_TO_TUPLES(MEMBERS)) \
    )

#define SMART_ENUM_IMPL_DEFINITION_1(CLASS, NAMESPACES, NAME, MEMBERS) \
    SMART_ENUM_IMPL_REPEAT(NAMESPACE_START, NAMESPACES) \
        enum CLASS SMART_ENUM_IMPL_NAME_SIZE(NAME) \
        { \
            SMART_ENUM_IMPL_MEMBER_DEFINITIONS(MEMBERS) \
        }; \
    SMART_ENUM_IMPL_REPEAT(NAMESPACE_END, NAMESPACES) \
    \
    SMART_ENUM_IMPL_TRAITS(NAMESPACES, BOOST_PP_TUPLE_ELEM(0, NAME), MEMBERS)

#define SMART_ENUM_IMPL_NAME_SIZE(NAME_SIZE) \
    BOOST_PP_TUPLE_ELEM(0, NAME_SIZE) \
    BOOST_PP_IF \
    ( \
        BOOST_PP_DEC(BOOST_PP_TUPLE_SIZE(NAME_SIZE)), \
            SMART_ENUM_IMPL_NAME_SIZE_1, BOOST_PP_TUPLE_EAT(1) \
    ) \
    NAME_SIZE

#define SMART_ENUM_IMPL_NAME_SIZE_1(NAME, SIZE) \
    : SIZE

// traits
#define SMART_ENUM_IMPL_TRAITS(NAMESPACES, NAME, MEMBERS) \
    SMART_ENUM_IMPL_TRAITS_1 \
    ( \
        SMART_ENUM_IMPL_FULL_NAME(NAMESPACES, NAME), \
        SMART_ENUM_IMPL_FULL_NAME_STRING(NAMESPACES, NAME), \
        NAME, \
        MEMBERS \
    )

#define SMART_ENUM_IMPL_TRAITS_1(FULL_NAME, FULL_NAME_STRING, NAME, MEMBERS) \
    namespace smart_enum \
    { \
        template<> struct enum_traits<FULL_NAME> \
        { \
            using type = FULL_NAME; \
            \
            static constexpr const char *name = BOOST_PP_STRINGIZE(NAME); \
            static constexpr const char *full_name = FULL_NAME_STRING; \
            \
            static constexpr std::size_t count = BOOST_PP_TUPLE_SIZE(MEMBERS); \
            \
            SMART_ENUM_IMPL_ADDITIONAL_DATA(FULL_NAME, MEMBERS) \
            SMART_ENUM_IMPL_FROM_STRING(FULL_NAME, MEMBERS) \
            SMART_ENUM_IMPL_TO_STRING(FULL_NAME, MEMBERS) \
        }; \
    }

// full name
#define SMART_ENUM_IMPL_FULL_NAME(NAMESPACES, NAME) \
    SMART_ENUM_IMPL_REPEAT(FULL_NAME_1, NAMESPACES) NAME

#define SMART_ENUM_IMPL_FULL_NAME_1(NAMESPACE) \
    NAMESPACE ::

#define SMART_ENUM_IMPL_FULL_NAME_STRING(NAMESPACES, NAME) \
    SMART_ENUM_IMPL_REPEAT(FULL_NAME_STRING_1, NAMESPACES) BOOST_PP_STRINGIZE(NAME)

#define SMART_ENUM_IMPL_FULL_NAME_STRING_1(NAMESPACE) \
    BOOST_PP_STRINGIZE(NAMESPACE) "::"

// additional data
#define SMART_ENUM_IMPL_ADDITIONAL_DATA(PREFIX, MEMBERS) \
    template \
    < \
        typename Action \
    > \
    static auto apply(PREFIX value, Action action) -> decltype(action()) \
    { \
        switch(value) \
        { \
            SMART_ENUM_IMPL_REPEAT_MEMBERS(PREFIX, MEMBERS, MEMBER_ADDITIONAL_DATA) \
        } \
        \
        throw std::invalid_argument("value"); \
    }

#define SMART_ENUM_IMPL_MEMBER_ADDITIONAL_DATA(PREFIX, NAME, MEMBER) \
    case PREFIX :: NAME: return action \
        SMART_ENUM_IMPL_MEMBER_ADDITIONAL_DATA_1 \
        ( \
            BOOST_PP_TUPLE_ELEM(BOOST_PP_DEC(BOOST_PP_TUPLE_SIZE(MEMBER)), MEMBER) \
        ) \
    ;

#define SMART_ENUM_IMPL_MEMBER_ADDITIONAL_DATA_1(ADDITIONAL_DATA) \
    BOOST_PP_IIF \
    ( \
        BOOST_PP_IS_BEGIN_PARENS(ADDITIONAL_DATA), ADDITIONAL_DATA, () \
    )

// member definitions
#define SMART_ENUM_IMPL_MEMBER_DEFINITIONS(MEMBERS) \
    SMART_ENUM_IMPL_ENUM_MEMBERS(_, MEMBERS, MEMBER_DEFINITION)

#define SMART_ENUM_IMPL_MEMBER_DEFINITION(_, NAME, MEMBER) \
    NAME \
    SMART_ENUM_IMPL_MEMBER_DEFINITION_1 \
    ( \
        BOOST_PP_TUPLE_ELEM(1, BOOST_PP_TUPLE_PUSH_BACK(MEMBER, ())) \
    )

#define SMART_ENUM_IMPL_MEMBER_DEFINITION_1(VALUE) \
    BOOST_PP_EXPR_IIF \
    ( \
        BOOST_PP_NOT(BOOST_PP_IS_BEGIN_PARENS(VALUE)), = VALUE \
    )

// from_string
#define SMART_ENUM_IMPL_FROM_STRING(PREFIX, MEMBERS) \
    static PREFIX from_string(const char *s) \
    { \
        return SMART_ENUM_IMPL_REPEAT_MEMBERS(PREFIX, MEMBERS, MEMBER_FROM_STRING) throw std::invalid_argument("s"); \
    }

#define SMART_ENUM_IMPL_MEMBER_FROM_STRING(PREFIX, NAME, _) \
    !strcmp(s, BOOST_PP_STRINGIZE(NAME)) ? PREFIX :: NAME :

// to_string
#define SMART_ENUM_IMPL_TO_STRING(PREFIX, MEMBERS) \
    static constexpr const char *to_string(PREFIX value) \
    { \
        return SMART_ENUM_IMPL_REPEAT_MEMBERS(PREFIX, MEMBERS, MEMBER_TO_STRING) throw std::invalid_argument("s"); \
    }

#define SMART_ENUM_IMPL_MEMBER_TO_STRING(PREFIX, NAME, _) \
    value == PREFIX :: NAME ? BOOST_PP_STRINGIZE(NAME) :

// namespaces
#define SMART_ENUM_IMPL_NAMESPACE_END(_) \
    }

#define SMART_ENUM_IMPL_NAMESPACE_START(NAMESPACE) \
    namespace NAMESPACE {

// utils
#define SMART_ENUM_IMPL_ARG_TO_TUPLE(ARG) \
    (BOOST_PP_REMOVE_PARENS(ARG))

#define SMART_ENUM_IMPL_ARGS_TO_TUPLES(ARGS) \
    BOOST_PP_ENUM(BOOST_PP_TUPLE_SIZE(ARGS), SMART_ENUM_IMPL_ARGS_TO_TUPLES_1, ARGS)

#define SMART_ENUM_IMPL_ARGS_TO_TUPLES_1(_, INDEX, ARGS) \
    SMART_ENUM_IMPL_ARG_TO_TUPLE(BOOST_PP_TUPLE_ELEM(INDEX, ARGS))

#define SMART_ENUM_IMPL_REPEAT(MACRO, TUPLE) \
    BOOST_PP_EXPR_IIF \
    ( \
        BOOST_PP_IS_BEGIN_PARENS(TUPLE), \
            BOOST_PP_REPEAT(BOOST_PP_TUPLE_SIZE(TUPLE), SMART_ENUM_IMPL_REPEAT_1, (TUPLE, MACRO)) \
    )

#define SMART_ENUM_IMPL_REPEAT_1(_, INDEX, TUPLE_MACRO) \
    BOOST_PP_CAT(SMART_ENUM_IMPL_, BOOST_PP_TUPLE_ELEM(1, TUPLE_MACRO)) \
        (BOOST_PP_TUPLE_ELEM(INDEX, BOOST_PP_TUPLE_ELEM(0, TUPLE_MACRO)))

#define SMART_ENUM_IMPL_ENUM_MEMBERS(PREFIX, MEMBERS, MACRO) \
    BOOST_PP_ENUM(BOOST_PP_TUPLE_SIZE(MEMBERS), SMART_ENUM_IMPL_PROCESS_MEMBERS_1, (PREFIX, MEMBERS, MACRO))

#define SMART_ENUM_IMPL_REPEAT_MEMBERS(PREFIX, MEMBERS, MACRO) \
    BOOST_PP_REPEAT(BOOST_PP_TUPLE_SIZE(MEMBERS), SMART_ENUM_IMPL_PROCESS_MEMBERS_1, (PREFIX, MEMBERS, MACRO))

#define SMART_ENUM_IMPL_PROCESS_MEMBERS_1(_, INDEX, PREFIX_MEMBERS_MACRO) \
    SMART_ENUM_IMPL_PROCESS_MEMBERS_2 \
    ( \
        BOOST_PP_TUPLE_ELEM(0, PREFIX_MEMBERS_MACRO), \
        BOOST_PP_TUPLE_ELEM(INDEX, BOOST_PP_TUPLE_ELEM(1, PREFIX_MEMBERS_MACRO)), \
        BOOST_PP_TUPLE_ELEM(2, PREFIX_MEMBERS_MACRO) \
    )

#define SMART_ENUM_IMPL_PROCESS_MEMBERS_2(PREFIX, MEMBER, MACRO) \
    BOOST_PP_CAT(SMART_ENUM_IMPL_, MACRO)(PREFIX, BOOST_PP_TUPLE_ELEM(0, MEMBER), MEMBER)

namespace smart_enum
{
    template
    <
        typename Enum
    >
    struct enum_traits {};

    template
    <
        typename Enum, typename Action
    >
    auto apply(Enum value, Action action) -> decltype(action())
    {
        return enum_traits<Enum>::apply(value, action);
    }

    template
    <
        typename Enum
    >
    constexpr std::size_t count()
    {
        return enum_traits<Enum>::count;
    }

    template
    <
        typename Enum
    >
    Enum from_string(const char *s)
    {
        return enum_traits<Enum>::from_string(s);
    }

    template
    <
        typename Enum
    >
    constexpr const char *full_name()
    {
        return enum_traits<Enum>::full_name;
    }

    template
    <
        typename Enum
    >
    constexpr const char *name()
    {
        return enum_traits<Enum>::name;
    }

    template
    <
        typename Enum
    >
    constexpr const char *to_string(Enum value)
    {
        return enum_traits<Enum>::to_string(value);
    }
}

#endif
