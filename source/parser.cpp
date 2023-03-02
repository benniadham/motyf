#include "../include/motyf/parser.hpp"

namespace motyf
{

    parser::parser() {
        define_tokens();
    }

    void parser::define_tokens()
    {
        scan.add_token_spec(Whitespace, "Whitespace", "^[ \\t]+");
        scan.add_token_spec(Number, "Number", "^\\d+");
        scan.add_token_spec(String, "String", "^\"[^\"]*\"");

        // -------------------------------------------------------------------
        // Symbols, Delimiters
        scan.add_token_spec(Colon, ":", "^:");
        scan.add_token_spec(SemiColon, ";", "^;");
        scan.add_token_spec(OpenCurly, "{", "^\\{");
        scan.add_token_spec(CloseCurly, "}", "^\\}");

        // --------------------------------------------------------------------
        // Comments
        scan.add_token_spec(LineComment, "LineComment", "^\\/\\/[^\\n]*");
        scan.add_token_spec(MultiComment, "MultiComment", "^\\/\\*[\\s\\S]*\\*\\/");
    }

    parser::ast_node parser::parse(const std::string& program)
    {
        ast_node node;

        return node;
    }
    
    err::type parser::consume_token(int token_type)
    {
        auto current_token = look_ahead;

        if (current_token.type == InvalidToken) {
            err::set_last_error(fmt::sprintf("Syntax error: Unexpected end of input, expecting: %s", scan.token_type_name(token_type)));
            return err::invalid_state;
        }

        
        return err::no_error;
    }

    /**
     * Program
     *  : StatementList
     *  ;
     */
    parser::ast_node parser::program()
    {
        ast_node node;

        return node;
    }

    /**
     * StatementList
     *  : Statement
     *  | StatementList Statement
     *  ; 
     */
    parser::ast_node parser::statement_list()
    {
        ast_node node;

        return node;
    }

    /**
     * Statement
     *  : ExpressionStatement
     *  ; 
     */
    parser::ast_node parser::statement()
    {
        ast_node node;

        return node;
    }

    /**
     * ExpressionStatement
     *  : Expression ';'
     *  ; 
     */
    parser::ast_node parser::expression_statement()
    {
        ast_node node;

        return node;
    }

    /**
     * Expression
     *  : Literal
     *  ; 
     */
    parser::ast_node parser::expression()
    {
        ast_node node;

        return node;
    }

    /**
     * Literal
     *  : NummericLiteral
     *  | StringLiteral
     *  ; 
     */
    parser::ast_node parser::literal()
    {
        ast_node node;

        return node;
    }

    /**
     * NumericLiteral
     *  : NUMBER
     *  ; 
     */
    parser::ast_node parser::numeric_literal()
    {
        ast_node node;

        return node;
    }

    /**
     * StringLiteral
     *  : STRING
     *  ; 
     */
    parser::ast_node parser::string_literal()
    {
        ast_node node;

        return node;
    }

    parser::ast_node::ast_node()
    {

    }
    
    parser::ast_node::ast_node(ast_node&& other)
    {
        body = std::move(other.body);
        text = other.text;
        type = other.type;
    }

    parser::ast_node& parser::ast_node::operator=(ast_node&& other)
    {
        body = std::move(other.body);
        text = other.text;
        type = other.type;

        return *this;
    }

} // namespace motyf