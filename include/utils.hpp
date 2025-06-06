#pragma once
#include <iostream>
#include <lexer.hpp>


/**
 * @brief Prints an error, thats it!
 *
 * @param error
 */
void print_error(std::string error);

/**
 * @brief Prints info or any kind of notice!
 *
 * @param info
 */
void print_info(std::string info);
/**
 * @brief It uses the magic_enum, which i just downloaded from github, to convert a type to string. This is so that i can show proper error. No credits taken what so ever.
 *
 * @param type
 * @return std::string
 */
std::string token_type_to_string(tokens::TokenType type);
/**
 * @brief Simply converts string to double, name says it all
 *
 * @param str
 * @return double
 */
double string_to_double(const std::string& str);
/**
 * @brief Simply exits in case of error
 */
void exit_with_error();
/**
 * @brief Prints title
 */
void print_branding();
/**
 * @brief Prints the help page for the app
 */
void print_help();