#include <iostream>
#include <sstream> 
#include <string>
#include <stdexcept> 
#include "../include/utils.hpp"
#include "../include/constants.hpp"
#include "../include/external/magic_enum.hpp"
#include "../include/lexer.hpp"

void print_error(std::string error)
{
    std::cout << codes::new_line;
    std::cout << codes::red << "┏━" << codes::reset;
    std::cout << codes::red << "\n┃ Error ~> " << error << codes::new_line;
    std::cout << codes::red << "┗━" << codes::reset;
    std::cout << codes::new_line;
    exit_with_error();
}

void print_info(std::string info)
{
    std::cout << codes::new_line;
    std::cout << codes::cyan << "┏━" << codes::reset;
    std::cout << codes::cyan << "\n┃ " << info << codes::new_line;
    std::cout << codes::cyan << "┗━" << codes::reset;
    std::cout << codes::new_line;
}

std::string token_type_to_string(tokens::TokenType type)
{
    return std::string(magic_enum::enum_name(type));
}


double string_to_double(const std::string& str) {
    try {
        size_t idx;
        double result = std::stod(str, &idx);

        if (idx != str.size()) {
            throw std::invalid_argument("Invalid characters found after number");
        }

        return result;
    }
    catch (const std::invalid_argument& e) {
        throw std::runtime_error("Invalid input: not a number");
    }
    catch (const std::out_of_range& e) {
        throw std::runtime_error("Input number out of range");
    }
}

void exit_with_error() {
    std::cout << codes::new_line;
    exit(0);
}

void print_branding()
{
    std::cout << codes::new_line;
    std::cout << codes::cyan << "┏━━━━━━━━━━━━━━━━━━━━━━┓" << codes::reset;
    std::cout << codes::cyan << "\n┃         Knot         ┃\n"
        << codes::reset;
    std::cout << codes::cyan << "┗━━━━━━━━━━━━━━━━━━━━━━┛" << codes::reset;
    std::cout << codes::new_line;
    std::cout << codes::new_line;
}

void print_help()
{
    std::cout << codes::new_line;
    std::cout << codes::green << "┏━" << codes::reset;
    std::cout << codes::green << "\n┃ Welcome to Knot – your lightweight graph plotter!";
    std::cout << codes::green << "\n┃ Thanks for checking it out.";
    std::cout << codes::green << "\n┃";
    std::cout << codes::green << "\n┃ 📄 Basic Usage:";
    std::cout << codes::green << "\n┃  1. Create a `.knot` file, e.g. `main.knot`.";
    std::cout << codes::green << "\n┃  2. Write equations in the form `plot y = expression`.";
    std::cout << codes::green << "\n┃  3. All equations will be plotted on the same graph.";
    std::cout << codes::green << "\n┃  4. Currently, only `x` and `y` are supported (i.e., y = f(x)).";
    std::cout << codes::green << "\n┃  5. Run it using: `./knotc main.knot`.";
    std::cout << codes::green << "\n┃";
    std::cout << codes::green << "\n┃ ⚙️  Options:";
    std::cout << codes::green << "\n┃  --step       Set the increment in x. Default: 0.1";
    std::cout << codes::green << "\n┃  --end-bound  Set the max absolute value of x. Default: 10.0";
    std::cout << codes::green << "\n┃";
    std::cout << codes::green << "\n┃ 📚 Docs & source: github.com/parv141206/knot";
    std::cout << codes::green << "\n┗━" << codes::reset;
    std::cout << codes::new_line;
    std::cout << codes::new_line;

}
