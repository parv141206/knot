#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <matplot/matplot.h>
#include "../include/lexer.hpp"
#include "../include/utils.hpp"
#include "../include/constants.hpp"
#include "../include/parser.hpp"
#include "../include/evaluate.hpp"
#include "../include/plot.hpp"

tokens::Tokens tokenize(const std::string &line, int line_no);
std::vector<std::string> read_knot_file(const std::string &path);

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

    for (size_t i = 0; i < lines.size(); ++i)
    {
        const auto &line = lines[i];
        int line_no = static_cast<int>(i + 1);

        std::cout << codes::yellow << "Processing line " << line_no << ": \"" << line << "\"" << codes::reset << "\n";

        tokens::Tokens line_tokens = tokenize(line, line_no);

        Parser parser(line_tokens);

        std::vector<tokens::Token> postfix_expression = parser.parse();

        if (!postfix_expression.empty())
        {
            //std::cout << codes::green << "Syntax: VALID" << codes::reset << "\n";
            //std::cout << codes::cyan << "Postfix Expression: " << codes::reset;
            for (const auto &token : postfix_expression)
            {
                //std::cout << token << " ";
                // following is temp, i will remove it. in future syntax, ill keep it so that user can mention values of a to z (apart from x and y) too ,
    // but for now i am throwing an error for it.
                if (token.type == tokens::TokenType::Ident) {
                    if (token.lexeme != "x" && token.lexeme != "y") {
                        throw std::runtime_error("Only supporting 'y' and 'x' based equations right now! A more dynamic version coming soon!");
                        exit(0);
                    }
                }
            }
            std::cout << "\n";

            std::map<double, double> values = evaluate(postfix_expression , 0.1 , 10.0);
            /*for (auto pair : values) {
                std::cout << "\n" << pair.first << " " << pair.second;
            }*/
            plot_values(values, "");
        }
        else
        {
            std::cout << codes::red << "Syntax: INVALID" << codes::reset << "\n";
            exit(0);
        }

        std::cout << "\n";
    }

    std::cout << std::flush;
    return 0;
}
