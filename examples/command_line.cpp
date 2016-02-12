#include "smart_enum.hpp"

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
        // ... with member "run_1" having data "runs 'function_1'" and pointer to "function_1" ...
        (run_1, ("runs 'function_1'", &function_1)),
        // ... with member "run_2" having data "runs 'function_2'" and pointer to "function_2"  ...
        (run_2, ("runs 'function_2'", &function_2)),
        // ... with member "run_1" having data "runs 'function_3'" and pointer to "function_3"  ...
        (run_3, ("runs 'function_3'", &function_3))
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

int main(int argc, char **argv)
{
    using namespace examples;
    using namespace smart_enum;

    if(argc == 1)
    {
        std::cout
            << "Available options: "
            << "(using '" << full_name<options>() << "' enum having " << count<options>() << " values)"
            << std::endl << std::endl;

        // for each option ...
        for(auto option : range<options>())
        {
            // ... get its data and ...
            auto option_data = data(option);

            std::cout
                // ... print option name ...
                << to_string(option) << " ==> "
                // ... and its description
                << std::get<0>(option_data)
                << std::endl;
        }

        return 0;
    }

    for(auto i = 1; i < argc; ++i)
    {
        auto arg = argv[i];

        try
        {
            // find option based on its name ...
            auto option = from_string<options>(arg);
            // ... and get its data
            auto option_data = data(option);

            std::get<1>(option_data)();
        }
        catch(const std::invalid_argument &)
        {
            std::cout << "Invalid option " << arg << std::endl;
        }
    }

    return 0;
}
