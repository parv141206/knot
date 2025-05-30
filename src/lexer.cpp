#include <iostream>
#include <fstream>
#include <string>
#include "../include/lexer.hpp"
#include "../include/utils.hpp"
#include "lexer.hpp"

tokens::Tokens tokenize(const std::string &line)
{
    tokens::Tokens tokens_;
    size_t i = 0;
    int line_no = 1; // For now :/

    while (i < line.size())
    {
        char ch = line[i];

        if (std::isspace(ch))
        {
            ++i;
            continue;
        }

        // Handles alphabetic words (keywords, functions, variables)
        if (std::isalpha(ch))
        {
            std::string word;
            while (i < line.size() && std::isalpha(line[i]))
            {
                word += line[i++];
            }

            // Keyword
            if (auto it = tokens::keyword_map.find(word); it != tokens::keyword_map.end())
            {
                tokens_.emplace_back(it->second, word, line_no);
            }
            // Function
            else if (auto it = tokens::function_map.find(word); it != tokens::function_map.end())
            {
                tokens_.emplace_back(it->second, word, line_no);
            }
            // Will be treated like an identifier
            else
            {
                tokens_.emplace_back(tokens::TokenType::Ident, word, line_no);
            }

            continue;
        }

        // Handles numbers
        if (std::isdigit(ch) || (ch == '.' && i + 1 < line.size() && std::isdigit(line[i + 1])))
        {
            std::string number;
            bool has_dot = false;

            while (i < line.size() &&
                   (std::isdigit(line[i]) || (!has_dot && line[i] == '.')))
            {
                if (line[i] == '.')
                    has_dot = true;

                number += line[i++];
            }

            tokens_.emplace_back(tokens::TokenType::Number, number, line_no);
            continue;
        }

        // Handles single-character symbols
        if (auto it = tokens::symbol_map.find(ch); it != tokens::symbol_map.end())
        {
            std::string sym(1, ch); // ass syntax to turn char into string
            tokens_.emplace_back(it->second, sym, line_no);
            ++i;
            continue;
        }

        // Unknown character fallback
        print_error("Unexpected character: " + ch);
        ++i;
    }

    return tokens_;
}

std::vector<std::string> read_knot_file(const std::string &path)
{
    std::vector<std::string> lines;
    std::ifstream file(path);

    if (!file.is_open())
    {
        print_error("Error opening the file: " + path);
        return lines;
    }

    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();
    return lines;
}

std::ostream &tokens::operator<<(std::ostream &os, const tokens::Token &tok)
{
    os << "{ type: " << static_cast<int>(tok.type)
       << ", lexeme: \"" << tok.lexeme
       << "\", line: " << tok.line << " }";
    return os;
}
