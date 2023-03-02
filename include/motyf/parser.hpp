#ifndef _MOTYF_INCLUDE_PARSER_HPP_
#define _MOTYF_INCLUDE_PARSER_HPP_

#include <ltd/ltd.hpp>
#include <vector>
#include <string>

#include "scanner.hpp"

using namespace ltd;

namespace motyf
{
    class parser
    {
    public: // types
        struct ast_node
        {
            std::vector<ast_node> body;
            std::string text;
            int type    = 0;

            ast_node(const ast_node&& other) = delete;
            
            ast_node(ast_node&& other);
            ast_node();

            ast_node& operator=(const ast_node& other) = delete;

            ast_node& operator=(ast_node&& other);
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

        scanner scan;

        void define_tokens();

        token look_ahead;

    public:
        parser();

        ast_node parse(const std::string& program);
        
        err::type consume_token(int token);

        ast_node program();
        ast_node statement_list();
        ast_node statement();
        ast_node expression_statement();
        ast_node expression();
        ast_node literal();
        ast_node numeric_literal();
        ast_node string_literal();

    };
} // namespace motyf

#endif // _MOTYF_INCLUDE_PARSER_HPP_