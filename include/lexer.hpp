// It was a pain to document this in detail.
// Heavy documentation has to be maintained for this file.
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
        Plot,   ///< Represents the `plot` keyword
        LParen, ///< Left parenthesis: `(`
        RParen, ///< Right parenthesis: `)`

        // Math Operations
        Assign,   ///< Assignment operator: `=`
        Plus,     ///< Addition operator: `+`
        Minus,    ///< Subtraction operator: `-`
        Multiply, ///< Multiplication operator: `*`
        Divide,   ///< Division operator: `/`
        Power,    ///< Exponentiation operator: `^`
        Colon,    ///< Colon symbol: `:`

        // Identifiers
        Ident,

        // Literals
        Number, ///< Numeric literal (integer or float)

        // Functions
        Function ///< Mathematical function (e.g., sin, cos)
    };

    /**
     * @brief Represents a token with type, value (lexeme), and line number.
     */
    struct Token
    {
        TokenType type;     ///< Type of the token
        std::string lexeme; ///< Actual string from input
        int line;           ///< Line number where the token was found

        Token(TokenType t, std::string lex, int ln)
            : type(t), lexeme(std::move(lex)), line(ln) {}
    };

    /**
     * @brief Alias for a list of tokens.
     */
    using Tokens = std::vector<Token>;

    // ----------------------------------------------------------------------------
    // Static Token Maps for Tokenization
    // ----------------------------------------------------------------------------

    /**
     * @brief Maps reserved keywords to their corresponding TokenType.
     *
     * Includes:
     * - `plot`
     */
    static const std::unordered_map<std::string, TokenType> keyword_map = {
        {"plot", TokenType::Plot}};

    /**
     * @brief Maps supported mathematical functions to the Function token type.
     *
     * Includes:
     * - sin, cos, tan, cosec, sec, cot
     */
    static const std::unordered_map<std::string, TokenType> function_map = {
        {"sin", TokenType::Function},
        {"cos", TokenType::Function},
        {"tan", TokenType::Function},
        {"cosec", TokenType::Function},
        {"sec", TokenType::Function},
        {"cot", TokenType::Function}};

    /**
     * @brief Maps single-character symbols to their corresponding TokenType.
     *
     * Includes:
     * - `=`, `+`, `-`, `*`, `/`, `^`, `:`, `(`, `)`
     */
    static const std::unordered_map<char, TokenType> symbol_map = {
        {'=', TokenType::Assign},
        {'+', TokenType::Plus},
        {'-', TokenType::Minus},
        {'*', TokenType::Multiply},
        {'/', TokenType::Divide},
        {'^', TokenType::Power},
        {':', TokenType::Colon},
        {'(', TokenType::LParen},
        {')', TokenType::RParen}};

    std::ostream &operator<<(std::ostream &os, const Token &tok)
    {
        os << "{ type: " << static_cast<int>(tok.type)
           << ", lexeme: \"" << tok.lexeme
           << "\", line: " << tok.line << " }";
        return os;
    }
}
// ----------------------------------------------------------------------------
// Lexer Interface
// ----------------------------------------------------------------------------

/**
 * @brief Tokenizes a single line of Knot source code.
 *
 * @param line The line to tokenize.
 * @return A vector of tokens found in the line.
 */
tokens::Tokens tokenize(const std::string &line);

/**
 * @brief Reads all lines from a .knot file.
 *
 * @param path The relative or absolute path to the file.
 * @return A list of strings, each representing a line from the file.
 */
std::vector<std::string> read_knot_file(const std::string &path);
