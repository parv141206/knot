#include "../include/lexer.hpp"
#include <vector>
#include <stdexcept>
#include <iostream>

class Parser
{
public:
    Parser(const tokens::Tokens &token_list);

    /**
     * @brief Parses the token list to check for syntax correctness.
     * @return True if the syntax is valid, false otherwise.
     */
    bool parse();

private:
    const tokens::Tokens &tokens;
    size_t current_token_index;

    /**
     * @brief Peeks at the current token without consuming it.
     * @return The current token.
     * @throws std::runtime_error if at the end of input.
     */
    const tokens::Token &peek() const;

    /**
     * @brief Consumes the current token and advances the index.
     * @return The consumed token.
     * @throws std::runtime_error if attempting to consume past the end of input.
     */
    const tokens::Token &consume();

    /**
     * @brief Checks if the current token matches the expected type and optional lexeme.
     *        If it matches, it consumes the token. Otherwise, throws an error.
     * @param type The expected token type.
     * @param expected_lexeme The expected lexeme (optional).
     * @throws std::runtime_error if the token does not match expectations.
     */
    void expect(tokens::TokenType type, const std::string &expected_lexeme = "");

    /**
     * @brief Parses the top-level program rule.
     */
    void parse_program();

    /**
     * @brief Parses a plot statement (e.g., plot y = ...).
     */
    void parse_plot_statement();

    /**
     * @brief Parses an expression (addition and subtraction).
     */
    void parse_expression();

    /**
     * @brief Parses a term (multiplication and division).
     */
    void parse_term();

    /**
     * @brief Parses a factor (exponentiation).
     */
    void parse_factor();

    /**
     * @brief Parses a primary expression (number, identifier, function call, parenthesized expression).
     */
    void parse_primary();

    /**
     * @brief Parses a list of expressions for function arguments.
     */
    void parse_expression_list(const std::string &function_name, int expected_arity);

    /**
     * @brief Checks if the current token type is one of the specified types.
     * @param types A vector of token types to check against.
     * @return True if the current token type is in the list, false otherwise.
     */
    bool match(const std::vector<tokens::TokenType> &types);
};
