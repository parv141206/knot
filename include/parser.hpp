#include "../include/lexer.hpp" 
#include <vector>
#include <stdexcept> 
#include <iostream>
#include <unordered_map> 

class Parser {
public:
    Parser(const tokens::Tokens& token_list);

    /**
     * @brief Parses the token list to check for syntax correctness and generate postfix notation for the expression.
     * @return A vector of tokens representing the expression in postfix notation on success.
     *         Returns an empty vector if a syntax error occurred (error message printed via print_error).
     */
    std::vector<tokens::Token> parse(); 

private:
    const tokens::Tokens& tokens;
    size_t current_token_index;

    // This stores the postfix version of the parsed expression's tokens
    std::vector<tokens::Token> postfix_output; 

    /**
     * @brief Peeks at the current token without consuming it.
     * @return The current token reference.
     * @throws std::runtime_error if at the end of input.
     */
    const tokens::Token& peek() const;

    /**
     * @brief Consumes the current token and advances the index.
     * @return The consumed token reference.
     * @throws std::runtime_error if attempting to consume past the end of input.
     */
    const tokens::Token& consume();

    /**
     * @brief Checks if the current token matches the expected type and optional lexeme.
     *        If it matches, it consumes the token. Otherwise, throws an error.
     * @param type The expected token type.
     * @param expected_lexeme The expected lexeme (optional).
     * @throws std::runtime_error if the token does not match expectations.
     */
    void expect(tokens::TokenType type, const std::string& expected_lexeme = "");

    // Removed the duplicate parse() declaration here

    /**
     * @brief Parses the top-level program rule (program -> plot_statement).
     * @throws std::runtime_error on syntax error.
     */
    void parse_program();

    /**
     * @brief Parses a plot statement (plot_statement -> Plot Ident Assign expression).
     *        Parses the expression and adds its RPN to postfix_output.
     * @throws std::runtime_error on syntax error.
     */
    void parse_plot_statement();

    /**
     * @brief Parses an expression (expression -> term { (Plus | Minus) term }*).
     *        Adds operators (+, -) to postfix_output.
     * @throws std::runtime_error on syntax error.
     */
    void parse_expression();

    /**
     * @brief Parses a term (term -> factor { (Multiply | Divide) factor }*).
     *        Adds operators (*, /) to postfix_output.
     * @throws std::runtime_error on syntax error.
     */
    void parse_term();

    /**
     * @brief Parses a factor (factor -> primary { Power primary }*).
     *        Adds operator (^) to postfix_output.
     * @throws std::runtime_error on syntax error.
     */
    void parse_factor();

    /**
     * @brief Parses a primary expression (Number, Ident, Function call, Parenthesized expression).
     *        Adds operands (Number, Ident) and Function tokens to postfix_output.
     * @throws std::runtime_error on syntax error.
     */
    void parse_primary();

    /**
     * @brief Parses a list of expressions for function arguments (expression_list -> expression { Comma expression }* | ).
     *        Parses each argument's expression (adding their RPN) and checks arity.
     * @param function_name The name of the function being called (for arity check error message).
     * @param expected_arity The number of arguments the function expects.
     * @throws std::runtime_error on syntax error or arity mismatch.
     */
    void parse_expression_list(const std::string& function_name, int expected_arity);

    /**
     * @brief Checks if the current token type is one of the specified types. Does not consume.
     * @param types A vector of token types to check against.
     * @return True if the current token type is in the list, false otherwise.
     */
    bool match(const std::vector<tokens::TokenType>& types);
};
