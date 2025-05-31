// TODO: actually implement this
#pragma once
#include <memory>
#include <string>
#include <vector>
#include "../include/lexer.hpp"

namespace ast
{

    struct Expr
    {
        virtual ~Expr() = default;
    };

    struct NumberExpr : Expr
    {
        std::string value;
        NumberExpr(std::string val) : value(std::move(val)) {}
    };

    struct IdentifierExpr : Expr
    {
        std::string name;
        IdentifierExpr(std::string n) : name(std::move(n)) {}
    };

    struct FunctionCallExpr : Expr
    {
        std::string name;
        std::vector<std::shared_ptr<Expr>> args;
        FunctionCallExpr(std::string n, std::vector<std::shared_ptr<Expr>> a)
            : name(std::move(n)), args(std::move(a)) {}
    };

    struct BinaryExpr : Expr
    {
        std::shared_ptr<Expr> left;
        tokens::TokenType op;
        std::shared_ptr<Expr> right;
        BinaryExpr(std::shared_ptr<Expr> l, tokens::TokenType o, std::shared_ptr<Expr> r)
            : left(std::move(l)), op(o), right(std::move(r)) {}
    };

    struct PlotStatement
    {
        std::string identifier;
        std::shared_ptr<Expr> expression;
    };

}
