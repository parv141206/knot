#include <iostream>
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
