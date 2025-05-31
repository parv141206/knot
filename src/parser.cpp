/**
 * Hours long of work.
 * TODO: I havent added any line number logic till now, will add it later.
 */
#include "../include/parser.hpp"
#include "../include/utils.hpp"
#include <iostream>
#include <cctype>
#include <stdexcept>

using namespace tokens;
using namespace parser;

const Token &SyntaxValidator::peek() const
{

    return tokens[current];
}

const Token &SyntaxValidator::advance()
{
    if (!is_at_end())
        current++;
    return previous();
}

const Token &SyntaxValidator::previous() const
{

    return tokens[current - 1];
}

bool SyntaxValidator::is_at_end() const { return current >= tokens.size(); }

bool SyntaxValidator::check_syntax()
{
    try
    {
        return validate_statement();
    }
    catch (const std::runtime_error &)
    {
        return false;
    }
    catch (const std::out_of_range &e)
    {
        // Catching potential out_of_range from peek() or advance() in unexpected scenarios
        print_error("Internal error: Reached end of tokens unexpectedly. Damn what code did you give!?");
        return false;
    }
}

bool SyntaxValidator::validate_statement()
{
    if (is_at_end() || peek().type != TokenType::Plot)
    {
        print_error("Expected 'plot' to start the statement. No 'plot', no plotting!");
        throw std::runtime_error("Expected 'plot'");
    }
    advance();

    if (is_at_end() || peek().type != TokenType::Ident)
    {
        print_error("Expected variable name (e.g., 'y') after 'plot'.");
        throw std::runtime_error("Expected identifier");
    }
    advance();

    if (is_at_end() || peek().type != TokenType::Assign)
    {
        print_error("Expected '=' after identifier.");
        throw std::runtime_error("Expected '='");
    }
    advance();

    validate_expression(0);

    if (!is_at_end())
    {
        std::cout << "\nUnexpected token: " << peek() << std::endl;
        print_error("Extra tokens after valid statement.");
        throw std::runtime_error("Extra tokens");
    }

    return true;
}

bool SyntaxValidator::validate_expression(int brackets_count, int function_args = 0)
{
    while (!is_at_end())
    {
        Token current_token = peek();
        if (current_token.type == TokenType::Number || current_token.type == TokenType::LParen || current_token.type == TokenType::Function || current_token.type == TokenType::Ident)
        {
            if (current_token.type == TokenType::Number || current_token.type == TokenType::Ident)
            {
                advance();
                if (symbol_map.find(peek().lexeme[0]) != symbol_map.end())
                {
                    advance();
                    validate_expression(brackets_count);
                }
                else
                {
                    print_error("Expected operator after an identifier or a number!");
                    std::runtime_error("Invalid Expression");
                }
            }
            else if (current_token.type == TokenType::LParen)
            {
                advance();
                validate_expression(brackets_count + 1);
            }
            else if (current_token.type == TokenType::RParen)
            {
                if (brackets_count - 1 >= 0)
                {
                    advance();
                    validate_expression(brackets_count - 1);
                }
                else
                {
                    print_error("Mismatch in brackets!");
                    std::runtime_error("Invalid Expression");
                }
            }
            else if (current_token.type == TokenType::Function)
            {
                if (function_map.find(current_token.lexeme) != function_map.end())
                {
                    advance();
                    validate_expression(brackets_count, valid_functions.at(current_token.lexeme) - 1);
                }
            }
            else if (current_token.type == TokenType::Comma)
            {
                if (function_args < 0)
                {
                    print_error("Wrong use of functions! Check the syntax again!");
                    std::runtime_error("Invalid Expression");
                }
                advance();
                validate_expression(brackets_count, function_args - 1);
            }
            else
            {
                print_error("Wrong use of functions! Check the syntax again!");
                std::runtime_error("Invalid Expression");
            }
        }
        else
        {
            print_error("Start of expression is invalid");
            std::runtime_error("Invalid Expression");
            exit(0);
        }
    }
    return true;
}
