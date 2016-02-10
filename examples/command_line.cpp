#include "smart_enum.hpp"

#include <cstring>
#include <iostream>

void function_1();
void function_2();
void function_3();

// define "enum class" (use "SMART_ENUM" to define "enum") ...
SMART_ENUM_CLASS
(
    // ... in namespace "examples" ...
    examples,
    // ... with name "options" having "char" type ("... enum class options : char ...") ...
    (options, char),
    (
        // ... with member "run_1" having data "run-1", "runs 'function_1'" and pointer to "function_1" ...
        (run_1, ("run-1", "runs 'function_1'", &function_1)),
        // ... with member "run_2" having data "run-2", "runs 'function_2'" and pointer to "function_2"  ...
        (run_2, ("run-2", "runs 'function_2'", &function_2)),
        // ... with member "run_1" having data "run-3", "runs 'function_3'" and pointer to "function_3"  ...
        (run_3, ("run-3", "runs 'function_3'", &function_3))
    )
)

void function_1()
{
    std::cout << "In 'function_1'" << std::endl;
}

void function_2()
{
    std::cout << "In 'function_2'" << std::endl;
}

void function_3()
{
    std::cout << "In 'function_3'" << std::endl;
}

int main(int argc, char **args)
{
    using namespace examples;
    using namespace smart_enum;

    if(argc == 1)
    {
        std::cout << "Available options:" << std::endl << std::endl;

        // for each option ...
        for(auto option : range<options>())
        {
            std::cout
                // ... print argument name ...
                << std::get<0>(data(option)) << " ==> "
                // ... and option description
                << std::get<1>(data(option))
                << std::endl;
        }

        return 0;
    }

    for(auto i = 1; i < argc; ++i)
    {
        auto arg = args[i];

        // for each option ...
        for(auto option : range<options>())
        {
            // ... get its data ...
            auto option_data = data(option);

            // ... check if argument matches option's argument name ...
            if(!std::strcmp(arg, std::get<0>(option_data)))
            {
                // ... call this option's function
                std::get<2>(option_data)();
            }
        }
    }

    return 0;
}
