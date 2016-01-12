#smart_enum
Tiny library for C++ `enum` introspection.

##Motivating example
```c++
SMART_ENUM
(
  e_1,
  (
    e_1_a, (e_1_b, 10), (e_1_c, "e_1::c"), (e_1_d, e_1_a + 1, "e_1::d"), (e_1_e, "e_1::e", 30)
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

And template `smart_enum::enum_traits<e_1>` having following fields and methods:

```c++
smart_enum::enum_traits<e_1>::count = 5
smart_enum::enum_traits<e_1>::description(e_1::e_1_a) = "e_1_a"
...
smart_enum::enum_traits<e_1>::description(e_1::e_1_e) = "e_1::e"
smart_enum::enum_traits<e_1>::is_enum_class = false
smart_enum::enum_traits<e_1>::name = "e_1"
smart_enum::enum_traits<e_1>::value(0) = e_1::e_1_a
...
smart_enum::enum_traits<e_1>::value(4) = e_1::e_1_e
```

(See `examples.cpp` for more examples.)

##Usage
If you are using [Boost](http://www.boost.org/) >= 1.60 then just add `smart_enum.hpp` to your project and you're done.
If not then also add included `boost` directory which contains subset of [Boost](http://www.boost.org/).

##Documentation
There are two public macros - `SMART_ENUM` and `SMART_ENUM_CLASS` - and one template struct - `smart_enum::enum_traits` (everything else is implementation detail and may change in the future).

The format of "smart" enum definition is as follows (the only difference between `SMART_ENUM` and `SMART_ENUM_CLASS` is that `SMART_ENUM` generates `enum ...` and `SMART_ENUM_CLASS` generates `enum class ...`):

```
SMART_ENUM(enum_name, (enum_values))
```

- `enum_name` can be either... well, enum name (`SMART_ENUM(e_1, ...)` generates `enum e_1...`) or tuple with enum name and its size (`SMART_ENUM((e_1, short), ...` generates `enum e_1 : short...`)
- `enum_values` is tuple of values where each value can be either simple name or tuple having 1 to 3 fields. The first field is always value name, the rest - its value and description - are optional and can be defined in any order.

Generated `smart_enum::enum_traits` defines following `constexpr` fields and methods:

- `count` - number of enum values
- `description(value)` - description of the value or its name if no description is set
- `is_enum_class` - whether enum is simple `enum` or `enum class` (this method supports all enums, not only "smart" ones)
- `name` - name of enum
- `value(index)` - enum value with specified index (`index >= 0 && index < count`)

(Again, see `examples.cpp` for more examples.)

##Supported compilers
Tested with Clang 3.7.0, g++ 5.3.0 and MSVC 2015, but should work with any compiler with support for C++ 11 and variadic macros.

##License
Uses standard [Boost license](http://www.boost.org/LICENSE_1_0.txt).

If you find this library useful I'll be glad if you star this repo :-) Any feedback is welcome!
