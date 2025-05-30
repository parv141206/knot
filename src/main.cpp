#include <iostream>
#include <vector>
#include <fstream>
#include "../include/lexer.hpp"
#include "../include/utils.hpp"
#include "../include/constants.hpp"

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
            std::cout << token << std::endl;
        }
        std::cout << line << '\n';
    }

    std::cout << std::flush;
    return 0;
}
