#pragma once

#include "lexer.hpp"
#include <iostream>

namespace parser
{

    /**
     * @brief SyntaxValidator class checks the token stream for valid syntax according to the rules of the language.
     * This does NOT build an AST yet.
     */
    class SyntaxValidator
    {
        const tokens::Tokens &tokens;
        size_t current = 0;

    public:
        SyntaxValidator(const tokens::Tokens &toks) : tokens(toks) {}

        /**
         * @brief Entry point to validate the token stream.
         * @return true if the syntax is valid, false otherwise.
         */
        bool check_syntax();

    private:
        // Helper functions
        const tokens::Token &peek() const;     // Look at current token
        const tokens::Token &advance();        // Move to next token
        const tokens::Token &previous() const; // Last consumed token
        bool is_at_end() const;                // Reached end of token stream

        // Rule validation functions
        bool validate_statement();  // Checks a full 'plot' statement
        bool validate_expression(); // Checks right-hand side of assignment
    };

} // namespace parser
