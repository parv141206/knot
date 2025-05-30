// Big problem with functions. Currently it doesnt work well for functions and right paren. i think i should do something with the recursive calling to validate it , since when calling recursively it goes till end , when using normal ( we didnt increase the count and wt coming end it simply finds "extra" ). Abhi sona jaruri hai

#include "../include/parser.hpp"

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

bool SyntaxValidator::is_at_end() const
{
    return current >= tokens.size();
}

bool SyntaxValidator::check_syntax()
{
    try
    {
        return validate_statement();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Syntax error: " << e.what() << "\n";
        return false;
    }
}

bool SyntaxValidator::validate_statement()
{
    // Must begin with 'plot'
    if (peek().type != TokenType::Plot)
        throw std::runtime_error("Expected 'plot' at beginning of statement.");
    advance();

    // Expect identifier
    if (peek().type != TokenType::Function && peek().type != TokenType::Number)
    {
        if (peek().type != TokenType::Function && !std::isalpha(peek().lexeme[0]))
            throw std::runtime_error("Expected identifier after 'plot'.");
    }
    advance();

    // Expect '='
    if (peek().type != TokenType::Assign)
        throw std::runtime_error("Expected '=' after identifier.");
    advance();

    // Expect valid right-hand side expression
    if (!validate_expression())
        throw std::runtime_error("Invalid expression on right-hand side.");

    // All tokens should be consumed
    if (!is_at_end())
    {

        std::cout << std::endl
                  << peek() << std::endl;
        throw std::runtime_error("Unexpected token after valid statement.");
    }

    return true;
}

bool SyntaxValidator::validate_expression()
{
    int paren_balance = 0;

    while (!is_at_end())
    {
        TokenType type = peek().type;

        switch (type)
        {
        case TokenType::Function:
            advance();

            if (peek().type != TokenType::LParen)
                throw std::runtime_error("Expected '(' after function name.");
            advance();

            if (!validate_expression())
                throw std::runtime_error("Invalid expression inside function call.");

            if (peek().type != TokenType::RParen)
                throw std::runtime_error("Expected ')' after function arguments.");
            advance();
            break;

        case TokenType::Number:
        case TokenType::Ident:
            advance();
            break;

        case TokenType::LParen:
            paren_balance++;
            std::cout << std::endl
                      << "Increasing paren bal" << std::endl;
            advance();
            break;

        case TokenType::RParen:
            paren_balance--;

            std::cout << std::endl
                      << "decreasing paren bal" << std::endl;
            if (paren_balance < 0)
                throw std::runtime_error("Unmatched ')'");
            advance();
            break;

        case TokenType::Plus:
        case TokenType::Minus:
        case TokenType::Multiply:
        case TokenType::Divide:
        case TokenType::Power:
            advance();
            break;

        default:
            return true;
        }
    }

    if (paren_balance != 0)
        throw std::runtime_error("Unbalanced parentheses in expression.");

    return true;
}
