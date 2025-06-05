#include <iostream>
#include <map>
#include <../include/lexer.hpp>

/**
 * @brief Evaluates the line...
 *
 * @param tokens_ , all the tokens to compute
 * @param step , increment steps
 * @param end , the end bound to stop
 * @return a map of "x" mapped to it's "y" value
 */
std::map<double, double> evaluate(tokens::Tokens tokens_ , double step , double end );