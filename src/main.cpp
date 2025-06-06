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

tokens::Tokens tokenize(const std::string& line, int line_no);
std::vector<std::string> read_knot_file(const std::string& path);

int main(int argc, char** argv)
{
	print_branding();

	double step = 0.1;
	double end_bound = 10.0;
	std::string file_path;

	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg == "--help") {
			print_help();
			return 0;
		}
	}

	if (argc < 2) {
		print_error("File path not mentioned!");
		print_info("Usage: ./knotc <path/to/file.knot> [--step <value>] [--end-bound <value>]");
		print_info("Use --help for more info.");
		return 1;
	}

	file_path = argv[1];
	std::cout << codes::green << codes::arrow << "Reading file: " << file_path << codes::new_line << codes::reset;

	for (int i = 2; i < argc; ++i) {
		std::string arg = argv[i];

		if (arg == "--step") {
			if (i + 1 < argc) {
				try {
					step = string_to_double(argv[++i]);
				}
				catch (const std::runtime_error& e) {
					print_error("Invalid --step value");
					print_error(e.what());
					return 1;
				}
			}
			else {
				print_error("Missing value for --step");
				return 1;
			}
		}
		else if (arg == "--end-bound") {
			if (i + 1 < argc) {
				try {
					end_bound = string_to_double(argv[++i]);
				}
				catch (const std::runtime_error& e) {
					print_error("Invalid --end-bound value");
					print_error(e.what());
					return 1;
				}
			}
			else {
				print_error("Missing value for --end-bound");
				return 1;
			}
		}
		else {
			print_error("Unknown option: " + arg);
			print_info("Use --help to see available options.");
			return 1;
		}
	}

	std::vector<std::string> lines = read_knot_file(file_path);
	std::cout << codes::new_line;

	std::vector<std::pair<std::map<double, double>, std::string>> all_plots;


	for (size_t i = 0; i < lines.size(); ++i)
	{
		const auto& line = lines[i];
		int line_no = static_cast<int>(i + 1);

		std::cout << codes::yellow << "\t➤  " << line_no << " | " << line << "" << codes::reset << "\n";

		tokens::Tokens line_tokens = tokenize(line, line_no);

		Parser parser(line_tokens);

		std::vector<tokens::Token> postfix_expression = parser.parse();

		if (!postfix_expression.empty())
		{
			for (const auto& token : postfix_expression)
			{
				// following is temp, i will remove it. in future syntax, ill keep it so that user can mention values of a to z (apart from x and y) too ,
	// but for now i am throwing an error for it.
				if (token.type == tokens::TokenType::Ident) {
					if (token.lexeme != "x" && token.lexeme != "y") {
						throw std::runtime_error("Only supporting 'y' and 'x' based equations right now! A more dynamic version coming soon!");
						exit(0);
					}
				}
			}

			std::map<double, double> values = evaluate(postfix_expression, step, end_bound);

			all_plots.push_back({ values, "f" + std::to_string(i + 1) });
		}
		else
		{
			exit(0);
		}
	}
	std::cout << "\n" << std::flush;
	plot_values(all_plots);
	return 0;
}
