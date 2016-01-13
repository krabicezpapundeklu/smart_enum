#smart_enum
Tiny library for C++ `enum` introspection.

##Motivating example
```c++
SMART_ENUM
(
  e_1,
  (
    e_1_a, (e_1_b, 10), e_1_c, (e_1_d, e_1_a + 1), (e_1_e, 30)
  )
)

```

Generates:

```c++
enum e_1
{
  e_1_a,
  e_1_b = 10,
  e_1_c,
  e_1_d = e_1_a + 1,
  e_1_e = 30
};
```

And makes following `constexpr` functions available:

```c++
count<e_1>() = 5 // number of values in enum

from_string<e_1>("e_1_a") = e_1::e_1_a; // converts value name to value
...
from_string<e_1>("e_1_e") = e_1::e_1_e;

index_of(e_1::e_1_a) = 0 // index of value in enum
...
index_of(e_1::e_1_e) = 4

is_enum_class<e_1>() = false // whether enum is 'enum' or 'enum class'

name<e_1>() = "e_1" // name of enum

to_string(e_1::e_1_a) = "e_1_a" // converts value to string
...
to_string(e_1::e_1_e) = "e_1_e"

value_of<e_1>(0) = e_1::e_1_a // value at specified 'index'
...
value_of<e_1>(4) = e_1::e_1_e
```

##Usage
If you are using [Boost](http://www.boost.org/) >= 1.60 then just add `smart_enum.hpp` to your project and you're done.
If not then also add included `boost` directory which contains subset of [Boost](http://www.boost.org/).

##Supported compilers
Tested with Clang 3.7.0, g++ 5.3.0 and MSVC 2015, but should work with any compiler with support for C++ 11 and variadic macros.

##License
Uses standard [Boost license](http://www.boost.org/LICENSE_1_0.txt).

If you find this library useful I'll be glad if you star this repo :-) Any feedback is welcome!
