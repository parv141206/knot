#include <iostream>
#include <vector>
#include <fstream>
#include "../include/lexer.hpp"    
#include "../include/utils.hpp"     
#include "../include/constants.hpp" 
#include "../include/parser.hpp"    

tokens::Tokens tokenize(const std::string& line, int line_no);
std::vector<std::string> read_knot_file(const std::string& path);

int main(int argc, char** argv)
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

    for (size_t i = 0; i < lines.size(); ++i)
    {
        const auto& line = lines[i];
        int line_no = static_cast<int>(i + 1); 

        std::cout << codes::yellow << "Processing line " << line_no << ": \"" << line << "\"" << codes::reset << "\n";

        tokens::Tokens line_tokens = tokenize(line, line_no);

        Parser parser(line_tokens);

        std::vector<tokens::Token> postfix_expression = parser.parse();

        if (!postfix_expression.empty())
        {
            std::cout << codes::green << "Syntax: VALID" << codes::reset << "\n";
            std::cout << codes::cyan << "Postfix Expression: " << codes::reset;
            for (const auto& token : postfix_expression) {
                std::cout << token << " ";
            }
            std::cout << "\n";
        }
        else
        {
            std::cout << codes::red << "Syntax: INVALID" << codes::reset << "\n";
        }

        std::cout << "\n"; 
    }

    std::cout << std::flush;
    return 0;
}