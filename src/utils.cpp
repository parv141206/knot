#include <iostream>
#include "../include/utils.hpp"
#include "../include/constants.hpp"

void print_error(std::string error)
{
    std::cout << codes::new_line << codes::red << "[Error] " << error << codes::reset;
}

void print_info(std::string info)
{
    std::cout << codes::new_line << codes::cyan << "" << info << codes::reset;
}
