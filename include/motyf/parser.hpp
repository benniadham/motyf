#ifndef _MOTYF_INCLUDE_PARSER_HPP_
#define _MOTYF_INCLUDE_PARSER_HPP_

#include <ltd/ltd.hpp>
#include <vector>
#include <string>

#include "scanner.hpp"
#include "ast_node.hpp"

using namespace ltd;

namespace motyf
{
    class parser
    {
    public: // types
        static constexpr char const *desc[3] =
        {
            "Unknown",              "NumericLiteral",           "StringLiteral"
        };

        enum ast_node_type
        {
            Unknown, NumericLiteral, StringLiteral
        };

        enum token_type
        {
            InvalidToken,   Whitespace,     Number,         String, 
            SemiColon,      Colon,          OpenCurly,      CloseCurly, 
            LineComment,    MultiComment
        };
        
    private:
        scanner _scanner;
        scanner::token _lookahead;

        void define_tokens();

    public:
        parser();

        ret<scanner::token,err::type> consume_token(int token);

        void print(const ast_node& node) const;

        ret<ast_node, err::type> parse(const std::string& program);
        ret<ast_node, err::type> program();
        ret<ast_node, err::type> statement_list();
        ret<ast_node, err::type> statement();
        ret<ast_node, err::type> expression_statement();
        ret<ast_node, err::type> expression();
        ret<ast_node, err::type> literal();
        ret<ast_node, err::type> numeric_literal();
        ret<ast_node, err::type> string_literal();

    };
} // namespace motyf

#endif // _MOTYF_INCLUDE_PARSER_HPP_