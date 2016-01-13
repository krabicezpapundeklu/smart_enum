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

Defines:

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
(See `examples.cpp`.)

##Documentation
###Macros `SMART_ENUM` and `SMART_ENUM_CLASS`
Macros for defining "smart" enums. The only difference is that `SMART_ENUM` generates `enum` while `SMART_ENUM_CLASS` generates `enum class`.

####Usage
`SMART_ENUM(name_with_optional_size, (value_name_with_optional_value, value_name_with_optional_value, ...))`
- `name_with_optional_size` - either enum name or tuple `(name, size)`. Example: `SMART_ENUM(e, ...)` defines `enum e {...};`, `SMART_ENUM((e, short), ...)` defines `enum e : short {...}`.
- `value_name_with_optional_value` - either value name or tuple `(value_name, value)`. Example: `SMART_ENUM(e, (a, b))` defines `enum e {a, b};`, `SMART_ENUM(e, (a, (b, 10), c))` defines `enum e {a, b = 10, c};`.

###Template `smart_enum::enum_traits<T>`
- `count` - number of values in enum
- `from_string(s)` - converts value name to its value, throws `std::invalid_argument` exception if no such value exists
- `index_of(value)` - returns index of value in enum
- `is_enum_class` - whether enum is `enum` or `enum class`
- `name` - name of enum
- `to_string(value)` - converts value to its name
- `value_of(index)` - returns value based on its index, throws `std::invalid_argument` exception if `index >= count`.

###Functions
- `smart_enum::count<T>()` - same as `smart_enum::enum_traits<T>::count`
- `smart_enum::from_string(s)` - same as `smart_enum::enum_traits<T>::from_string(s)`
- `smart_enum::index_of(value)` - same as `smart_enum::enum_traits<T>::index_of(value)`
- `smart_enum::is_enum_class<T>()` - same as `smart_enum::enum_traits<T>::is_enum_class`
- `smart_enum::name<T>()` - same as `smart_enum::enum_traits<T>::name`
- `smart_enum::to_string(value)` - same as `smart_enum::enum_traits<T>::to_string(value)`
- `smart_enum::value_of<T>(index)` - same as `smart_enum::enum_traits<T>::value_of(index)`

##Library usage
If you are using [Boost](http://www.boost.org/) >= 1.60 then just add `smart_enum.hpp` to your project and you're done.
If not then also add included `boost` directory which contains subset of [Boost](http://www.boost.org/).

##Supported compilers
Tested with Clang 3.7.0, g++ 5.3.0 and MSVC 2015, but should work with any compiler with support for C++ 11 and variadic macros.

##License
Uses standard [Boost license](http://www.boost.org/LICENSE_1_0.txt).

If you find this library useful I'll be glad if you star this repo :-) Any feedback is welcome!
