#include <iostream>
#include <map>
#include <stack>
#include <cmath> 
#include <stdexcept> 
#include <../include/lexer.hpp>
#include <../include/utils.hpp>

using namespace std;
using namespace tokens;

map<double, double> evaluate(tokens::Tokens tokens_ , double step , double end ) {
	map<double, double> values;

	for (int i = 0; i <= (int)(end / step); ++i) {
		double x = i * step;

		stack<double> operands;

		for (Token token : tokens_) {
			if (token.type == TokenType::Number) {
				operands.push(string_to_double(token.lexeme));
			}
			else if (token.type == TokenType::Ident && token.lexeme == "x") {
				operands.push(x);
			}
			// seems like an operator, not supposed to break :p
			else if (symbol_map.find(token.lexeme[0]) != symbol_map.end()) {
				if (operands.size() < 2) {
					throw std::runtime_error("Insufficient operands for operator: " + token.lexeme);
				}

				double right = operands.top(); operands.pop();
				double left = operands.top(); operands.pop();
				double result = 0.0;

				switch (token.lexeme[0]) {
				case '+': result = left + right; break;
				case '-': result = left - right; break;
				case '*': result = left * right; break;
				case '/': result = left / right; break;
				case '^': result = std::pow(left, right); break;
				default:
					throw std::runtime_error("Unknown operator: " + token.lexeme);
				}

				operands.push(result);
			}
			else if (token.type == TokenType::Function && valid_functions.find(token.lexeme) != valid_functions.end()) {
				int arg_count = valid_functions.at(token.lexeme);

				if (operands.size() < arg_count) {
					throw std::runtime_error("Not enough operands for function: " + token.lexeme);
				}

				std::vector<double> args(arg_count);
				for (int i = arg_count - 1; i >= 0; --i) {
					args[i] = operands.top();
					operands.pop();
				}

				double result = 0.0;

				if (token.lexeme == "sin") result = std::sin(args[0]);
				else if (token.lexeme == "cos") result = std::cos(args[0]);
				else if (token.lexeme == "tan") result = std::tan(args[0]);
				else if (token.lexeme == "cosec") result = 1.0 / std::sin(args[0]);
				else if (token.lexeme == "sec") result = 1.0 / std::cos(args[0]);
				else if (token.lexeme == "cot") result = 1.0 / std::tan(args[0]);
				else if (token.lexeme == "sqrt") result = std::sqrt(args[0]);
				else if (token.lexeme == "log") result = std::log(args[1]) / std::log(args[0]);
				else if (token.lexeme == "ln") result = std::log(args[0]);
				else if (token.lexeme == "pow") result = std::pow(args[0], args[1]);
				else if (token.lexeme == "abs") result = std::abs(args[0]);
				else if (token.lexeme == "exp") result = std::exp(args[0]);
				else if (token.lexeme == "floor") result = std::floor(args[0]);
				else if (token.lexeme == "ceil") result = std::ceil(args[0]);
				else throw std::runtime_error("Unknown function: " + token.lexeme + "\n" + "How though?! This error will never come!");

				operands.push(result);
			}
			else {
				throw std::runtime_error("How the hell did u get this error, this error is not supposed to be thrown ever!!!");
			}

		}
		values[x] = operands.top();
	}
	return values;
}