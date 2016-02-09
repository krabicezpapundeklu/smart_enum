

//          Copyright Jarda Flieger 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SMART_ENUM_HEADER_INCLUDED
#define SMART_ENUM_HEADER_INCLUDED

#include <stdexcept>

#include <boost/iterator/iterator_facade.hpp>
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
        template<> struct enum_traits<FULL_NAME> : detail::enum_traits_base<FULL_NAME> \
        { \
            using type = FULL_NAME; \
            \
            static constexpr const char *name = BOOST_PP_STRINGIZE(NAME); \
            static constexpr const char *full_name = FULL_NAME_STRING; \
            \
            static constexpr std::size_t count = BOOST_PP_TUPLE_SIZE(MEMBERS); \
            \
            SMART_ENUM_IMPL_APPLY(FULL_NAME, MEMBERS) \
            SMART_ENUM_IMPL_FROM_STRING(FULL_NAME, MEMBERS) \
            SMART_ENUM_IMPL_INDEX_OF(FULL_NAME, MEMBERS) \
            SMART_ENUM_IMPL_ITERATORS(FULL_NAME) \
            SMART_ENUM_IMPL_TO_STRING(FULL_NAME, MEMBERS) \
            SMART_ENUM_IMPL_VALUE_OF(FULL_NAME, MEMBERS) \
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

// data
#define SMART_ENUM_IMPL_APPLY(PREFIX, MEMBERS) \
    template \
    < \
        typename Action \
    > \
    static auto apply(PREFIX value, Action action) -> decltype(action()) \
    { \
        switch(value) \
        { \
            SMART_ENUM_IMPL_REPEAT_MEMBERS(PREFIX, MEMBERS, MEMBER_APPLY) \
        } \
        \
        throw std::invalid_argument("value"); \
    }

#define SMART_ENUM_IMPL_MEMBER_APPLY(PREFIX, NAME, MEMBER, INDEX) \
    case PREFIX :: NAME: \
        return action \
            SMART_ENUM_IMPL_MEMBER_APPLY_1 \
            ( \
                BOOST_PP_TUPLE_ELEM(BOOST_PP_DEC(BOOST_PP_TUPLE_SIZE(MEMBER)), MEMBER) \
            ) \
        ;

#define SMART_ENUM_IMPL_MEMBER_APPLY_1(DATA) \
    BOOST_PP_IIF \
    ( \
        BOOST_PP_IS_BEGIN_PARENS(DATA), DATA, () \
    )

// member definitions
#define SMART_ENUM_IMPL_MEMBER_DEFINITIONS(MEMBERS) \
    SMART_ENUM_IMPL_ENUM_MEMBERS(_, MEMBERS, MEMBER_DEFINITION)

#define SMART_ENUM_IMPL_MEMBER_DEFINITION(PREFIX, NAME, MEMBER, INDEX) \
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

#define SMART_ENUM_IMPL_MEMBER_FROM_STRING(PREFIX, NAME, MEMBER, INDEX) \
    !strcmp(s, BOOST_PP_STRINGIZE(NAME)) ? PREFIX :: NAME :

// index_of
#define SMART_ENUM_IMPL_INDEX_OF(PREFIX, MEMBERS) \
    static constexpr std::size_t index_of(PREFIX value) \
    { \
        return SMART_ENUM_IMPL_REPEAT_MEMBERS(PREFIX, MEMBERS, MEMBER_INDEX_OF) throw std::invalid_argument("value"); \
    }

#define SMART_ENUM_IMPL_MEMBER_INDEX_OF(PREFIX, NAME, MEMBER, INDEX) \
    value == PREFIX :: NAME ? INDEX ## u :

// to_string
#define SMART_ENUM_IMPL_TO_STRING(PREFIX, MEMBERS) \
    static constexpr const char *to_string(PREFIX value) \
    { \
        return SMART_ENUM_IMPL_REPEAT_MEMBERS(PREFIX, MEMBERS, MEMBER_TO_STRING) throw std::invalid_argument("s"); \
    }

#define SMART_ENUM_IMPL_MEMBER_TO_STRING(PREFIX, NAME, MEMBER, INDEX) \
    value == PREFIX :: NAME ? BOOST_PP_STRINGIZE(NAME) :

// value_of
#define SMART_ENUM_IMPL_VALUE_OF(PREFIX, MEMBERS) \
    static constexpr PREFIX value_of(std::size_t index) \
    { \
        return SMART_ENUM_IMPL_REPEAT_MEMBERS(PREFIX, MEMBERS, MEMBER_VALUE_OF) throw std::invalid_argument("index"); \
    }

#define SMART_ENUM_IMPL_MEMBER_VALUE_OF(PREFIX, NAME, MEMBER, INDEX) \
    index == INDEX ? PREFIX :: NAME :

// iterators
#define SMART_ENUM_IMPL_ITERATORS(FULL_NAME) \
    static constexpr enum_iterator<FULL_NAME> begin() \
    { \
        return enum_iterator<FULL_NAME>{value_of(0)}; \
    } \
    \
    static constexpr enum_iterator<FULL_NAME> end() \
    { \
        return {}; \
    } \
    \
    static constexpr enum_range<FULL_NAME> range() \
    { \
        return {}; \
    }

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
        BOOST_PP_TUPLE_ELEM(2, PREFIX_MEMBERS_MACRO), \
        INDEX \
    )

#define SMART_ENUM_IMPL_PROCESS_MEMBERS_2(PREFIX, MEMBER, MACRO, INDEX) \
    BOOST_PP_CAT(SMART_ENUM_IMPL_, MACRO)(PREFIX, BOOST_PP_TUPLE_ELEM(0, MEMBER), MEMBER, INDEX)

namespace smart_enum
{
    template
    <
        typename Enum
    >
    class enum_iterator;

    template
    <
        typename Enum
    >
    struct enum_range;

    namespace detail
    {
        template
        <
            typename Enum
        >
        struct enum_traits_base
        {
            static constexpr bool is_enum_class =
                std::integral_constant
                <
                    bool, std::is_enum<Enum>::value && !std::is_convertible<Enum, int>::value
                >
                ::value;
        };
    }

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
    constexpr enum_iterator<Enum> begin()
    {
        return enum_traits<Enum>::begin();
    }

    template
    <
        typename Enum
    >
    constexpr enum_iterator<Enum> end()
    {
        return enum_traits<Enum>::end();
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
    constexpr std::size_t index_of(Enum value)
    {
        return enum_traits<Enum>::index_of(value);
    }

    template
    <
        typename Enum
    >
    constexpr bool is_enum_class()
    {
        return enum_traits<Enum>::is_enum_class;
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
    constexpr enum_range<Enum> range()
    {
        return enum_traits<Enum>::range();
    }

    template
    <
        typename Enum
    >
    constexpr const char *to_string(Enum value)
    {
        return enum_traits<Enum>::to_string(value);
    }

    template
    <
        typename Enum
    >
    constexpr Enum value_of(std::size_t index)
    {
        return enum_traits<Enum>::value_of(index);
    }

    template
    <
        typename Enum
    >
    class enum_iterator : public boost::iterator_facade
    <
        enum_iterator<Enum>, Enum, boost::random_access_traversal_tag, Enum
    >
    {
    public:
        constexpr enum_iterator()
            : index_{ count<Enum>() }
        {
        }

        constexpr explicit enum_iterator(Enum value)
            : index_{ index_of(value) }
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

        constexpr Enum dereference() const
        {
            return value_of<Enum>(index_);
        }

        constexpr std::ptrdiff_t distance_to(const enum_iterator &other) const
        {
            return other.index_ - index_;
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

    template
    <
        typename Enum
    >
    struct enum_range
    {
        constexpr enum_iterator<Enum> begin() const
        {
            return smart_enum::begin<Enum>();
        }

        constexpr enum_iterator<Enum> end() const
        {
            return smart_enum::end<Enum>();
        }
    };
}

#endif
