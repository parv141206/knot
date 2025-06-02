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

    for (size_t i = 0; i < lines.size(); ++i)
    {
        const auto &line = lines[i];
        int line_no = static_cast<int>(i + 1);

        tokens::Tokens tokens_ = tokenize(line, line_no);

        for (auto token : tokens_)
        {
            // std::cout << token << std::endl;
        }

        Parser parser(tokens_);
    }

    std::cout << std::flush;
    return 0;
}
