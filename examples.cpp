
//          Copyright Jarda Flieger 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "smart_enum.hpp"

SMART_ENUM(a, (a, b, c))
SMART_ENUM((b, short), (a, b, c))

SMART_ENUM_CLASS(c, (a, b, c))
SMART_ENUM_CLASS((d, short), (a, b, c))

SMART_ENUM(n, a, (a, b, c))
SMART_ENUM(n, (b, short), (a, b, c))

SMART_ENUM_CLASS(n, c, (a, b, c))
SMART_ENUM_CLASS(n, (d, short), (a, b, c))

int main()
{
    return 0;
}
