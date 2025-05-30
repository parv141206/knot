#include <iostream>
#include <vector>
#include <fstream>
#include "../include/lexer.hpp"
#include "../include/utils.hpp"
#include "../include/constants.hpp"
#include "../include/parser.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        print_error("File path not mentioned!");
        print_info("Usage: ./knotc <path/to/file.knot>");
        return 1;
    }

    std::string file_path = argv[1];
    std::cout << codes::green << codes::arrow << "Reading file: " << file_path << "\n"
              << codes::reset;

    std::vector<std::string> lines = read_knot_file(file_path);

    for (const auto &line : lines)
    {
        tokens::Tokens tokens_ = tokenize(line);
        for (auto token : tokens_)
        {
            // std::cout << token << std::endl;
        }
        parser::SyntaxValidator validator = parser::SyntaxValidator(tokens_);
        if (validator.check_syntax())
        {
            std::cout << "Valid";
        }
        else
        {
            std::cout << "Invalid";
        }
        // std::cout << line << '\n';
    }

    std::cout << std::flush;
    return 0;
}
