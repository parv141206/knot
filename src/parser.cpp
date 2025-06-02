/**
 *
 * THIS FILE TOOK BLOOD, SWEAT, and TEARS TO MAKE
 *
 * This file only CHECKS if the given tokens are even valid or not.
 * It DOES NOT create an AST
 *
 * This uses a Recursive Descent Parser technique, GOATED!
 *
 * For this, i have made following grammer, kind of a standard one:
 *
 * --- Grammer ---
 * program -> plot_statement
 * plot_statement -> Plot Ident Assign expression
 * expression -> term { (Plus | Minus) term }*
 * term -> factor { (Multiply | Divide) factor }*
 * factor -> primary { Power primary }*
 * primary -> Number | Ident | Function LParen expression_list RParen | LParen expression RParen
 * expression_list -> expression { Comma expression }* | // Empty if needed
 *
 */
#include "../include/parser.hpp"
#include "../include/utils.hpp" 

Parser::Parser(const tokens::Tokens& token_list) : tokens(token_list), current_token_index(0) {}

std::vector<tokens::Token> Parser::parse()
{
    postfix_output.clear(); 
    current_token_index = 0; 

    try
    {
        parse_program(); 
        if (current_token_index == tokens.size()) {
            return postfix_output;
        }
        else {
            std::string msg = "Internal parser error: Did not consume all tokens after successful parse_program.";
            print_error(msg);
            return {};
        }
    }
    catch (const std::runtime_error& e)
    {
        return {};
    }
}

const tokens::Token& Parser::peek() const
{
    if (current_token_index >= tokens.size())
    {
        int line = tokens.empty() ? 0 : tokens.back().line;
        std::string msg = "Unexpected end of input at or near line " + std::to_string(line);
        throw std::runtime_error(msg);
    }
    return tokens[current_token_index];
}

const tokens::Token& Parser::consume()
{
    if (current_token_index >= tokens.size())
    {
        int line = tokens.empty() ? 0 : tokens.back().line;
        std::string msg = "Attempted to consume past end of input at or near line " + std::to_string(line);
        throw std::runtime_error(msg);
    }
    return tokens[current_token_index++];
}

void Parser::expect(tokens::TokenType type, const std::string& expected_lexeme)
{
    const auto& token = peek(); 

    if (token.type != type || (!expected_lexeme.empty() && token.lexeme != expected_lexeme))
    {
        std::string msg = "Expected token type " + token_type_to_string(type) +
            (expected_lexeme.empty() ? "" : " ('" + expected_lexeme + "')") +
            " but got type " + token_type_to_string(token.type) +
            " ('" + token.lexeme + "')" +
            " at line " + std::to_string(token.line);
        throw std::runtime_error(msg);
    }
    consume(); 
}

bool Parser::match(const std::vector<tokens::TokenType>& types)
{
    if (current_token_index >= tokens.size())
    {
        return false; 
    }
    const auto& token = peek();
    for (tokens::TokenType type : types)
    {
        if (token.type == type)
        {
            return true;
        }
    }
    return false;
}

// --- Parser Functions for Grammar Rules ---

// Rule: program -> plot_statement
void Parser::parse_program()
{
    parse_plot_statement();
    if (current_token_index < tokens.size())
    {
        const auto& token = peek(); 
        std::string msg = "Unexpected tokens after plot statement starting at line " + std::to_string(token.line);
        throw std::runtime_error(msg);
    }
}

// Rule: plot_statement -> Plot Ident Assign expression
void Parser::parse_plot_statement()
{
    expect(tokens::TokenType::Plot);
    expect(tokens::TokenType::Ident);
    expect(tokens::TokenType::Assign); 
    parse_expression(); 
}

// Rule: expression -> term { (Plus | Minus) term }*
void Parser::parse_expression()
{
    parse_term(); 

    while (match({ tokens::TokenType::Plus, tokens::TokenType::Minus }))
    {
        const auto& op_token = peek();
        consume(); 
        parse_term(); 
        postfix_output.push_back(op_token); 
    }
}

void Parser::parse_term()
{
    parse_factor(); 

    while (match({ tokens::TokenType::Multiply, tokens::TokenType::Divide }))
    {
        const auto& op_token = peek();
        consume(); 
        parse_factor(); 
        postfix_output.push_back(op_token);
    }
}

// Rule: factor -> primary { Power primary }*
void Parser::parse_factor()
{
    parse_primary(); 

    while (match({ tokens::TokenType::Power }))
    {
        const auto& op_token = peek();
        consume();
        parse_primary();
        postfix_output.push_back(op_token); 
    }
}

// Rule: primary -> Number | Ident | Function LParen expression_list RParen | LParen expression RParen
void Parser::parse_primary()
{
    const auto& token = peek(); 

    if (match({ tokens::TokenType::Number, tokens::TokenType::Ident }))
    {
        postfix_output.push_back(token); 
        consume();
    }
    else if (match({ tokens::TokenType::Function }))
    {
        std::string function_name = token.lexeme;
        const auto& function_token = token; 
        consume();
        expect(tokens::TokenType::LParen);

        int expected_arity = 0;
        if (tokens::valid_functions.count(function_name))
        {
            expected_arity = tokens::valid_functions.at(function_name);
        }
        else
        {
            std::string msg = "Unknown function '" + function_name + "' at line " + std::to_string(token.line);
            throw std::runtime_error(msg);
        }

        parse_expression_list(function_name, expected_arity);
        expect(tokens::TokenType::RParen);

        postfix_output.push_back(function_token); 
    }
    else if (match({ tokens::TokenType::LParen }))
    {
        consume(); 
        parse_expression(); 
        expect(tokens::TokenType::RParen);
    }
    else
    {
        std::string msg = "Unexpected token in primary expression: type " + token_type_to_string(token.type) +
            " ('" + token.lexeme + "')" +
            " at line " + std::to_string(token.line);
        throw std::runtime_error(msg);
    }
}

// Rule: expression_list -> expression { Comma expression }* |
// Parses comma-separated arguments. Adds each argument's RPN sequentially.
void Parser::parse_expression_list(const std::string& function_name, int expected_arity)
{
    int argument_count = 0;

    if (!match({ tokens::TokenType::RParen })) 
    {
        parse_expression(); 
        argument_count++;

        while (match({ tokens::TokenType::Comma }))
        {
            consume(); 
            parse_expression();
            argument_count++;
        }
    }

    if (argument_count != expected_arity)
    {
        int error_line = tokens.empty() ? 0 : tokens[current_token_index > 0 ? current_token_index - 1 : 0].line;
        if (current_token_index < tokens.size()) { 
            error_line = peek().line;
        }

        std::string msg = "Function '" + function_name + "' expects " +
            std::to_string(expected_arity) + " arguments, but got " +
            std::to_string(argument_count) + " at line " + std::to_string(error_line);
        throw std::runtime_error(msg);
    }
}