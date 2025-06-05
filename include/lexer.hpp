#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

namespace tokens
{

    /**
     * @brief All possible token types in the Knot language.
     */
    enum class TokenType
    {
        // Keywords
        Plot,
        LParen,
        RParen,

        // Math Operations
        Assign,
        Plus,
        Minus,
        Multiply,
        Divide,
        Power,
        Colon,
        Comma,

        // Identifiers
        Ident,

        // Literals
        Number,

        // Functions
        Function
    };

    /**
     * @brief Represents a token with type, value (lexeme), and line number.
     */
    struct Token
    {
        TokenType type;
        std::string lexeme;
        int line;
        Token() {}
        Token(TokenType t, std::string lex, int ln)
            : type(t), lexeme(std::move(lex)), line(ln) {}
    };

    using Tokens = std::vector<Token>;

    // ----------------------------------------------------------------------------
    // Static Token Maps for Tokenization
    // ----------------------------------------------------------------------------

    static const std::unordered_map<std::string, TokenType> keyword_map = {
        {"plot", TokenType::Plot}};

    static const std::unordered_map<std::string, TokenType> function_map = {
        {"sin", TokenType::Function},
        {"cos", TokenType::Function},
        {"tan", TokenType::Function},
        {"cosec", TokenType::Function},
        {"sec", TokenType::Function},
        {"cot", TokenType::Function},
        {"sqrt", TokenType::Function},
        {"log", TokenType::Function},
        {"ln", TokenType::Function},
        {"pow", TokenType::Function},
        {"abs", TokenType::Function},
        {"exp", TokenType::Function},
        {"floor", TokenType::Function},
        {"ceil", TokenType::Function}};

    static const std::unordered_map<char, TokenType> symbol_map = {
        {'=', TokenType::Assign},
        {'+', TokenType::Plus},
        {'-', TokenType::Minus},
        {'*', TokenType::Multiply},
        {'/', TokenType::Divide},
        {'^', TokenType::Power},
        {':', TokenType::Colon},
        {'(', TokenType::LParen},
        {')', TokenType::RParen},
        {',', TokenType::Comma}};

    // ----------------------------------------------------------------------------
    // Function Arity (Arguments Expected)
    // ----------------------------------------------------------------------------

    const std::unordered_map<std::string, int> valid_functions = {
        {"sin", 1},
        {"cos", 1},
        {"tan", 1},
        {"cosec", 1},
        {"sec", 1},
        {"cot", 1},
        {"sqrt", 1},
        {"log", 2}, // base, number
        {"ln", 1},
        {"pow", 2}, // base, exponent
        {"abs", 1},
        {"exp", 1},
        {"floor", 1},
        {"ceil", 1}};

    std::ostream &operator<<(std::ostream &os, const Token &tok);

} 

// ----------------------------------------------------------------------------
// Lexer Interface
// ----------------------------------------------------------------------------

tokens::Tokens tokenize(const std::string &line, int line_no);
std::vector<std::string> read_knot_file(const std::string &path);
