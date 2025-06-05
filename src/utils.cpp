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
    std::cout << codes::new_line << codes::red << "[Error] " << error << codes::reset;
}

void print_info(std::string info)
{
    std::cout << codes::new_line << codes::cyan << "" << info << codes::reset;
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