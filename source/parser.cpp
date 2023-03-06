#include "../include/motyf/parser.hpp"

namespace motyf
{

    parser::parser() {
        define_tokens();
    }

    void parser::define_tokens()
    {
        _scanner.add_token_spec(Whitespace, "Whitespace", "^[ \\t]+");
        _scanner.add_token_spec(Number, "Number", "^\\d+");
        _scanner.add_token_spec(String, "String", "^\"[^\"]*\"");

        // -------------------------------------------------------------------
        // Symbols, Delimiters
        _scanner.add_token_spec(Colon, ":", "^:");
        _scanner.add_token_spec(SemiColon, ";", "^;");
        _scanner.add_token_spec(OpenCurly, "{", "^\\{");
        _scanner.add_token_spec(CloseCurly, "}", "^\\}");

        // --------------------------------------------------------------------
        // Comments
        _scanner.add_token_spec(LineComment, "LineComment", "^\\/\\/[^\\n]*");
        _scanner.add_token_spec(MultiComment, "MultiComment", "^\\/\\*[\\s\\S]*\\*\\/");
    }
    
    ret<scanner::token,err::type> parser::  consume_token(int token_type)
    {
        scanner::token token;

        if (_lookahead.type == InvalidToken) {
            auto msg = fmt::sprintf("Syntax error: Unexpected end of input, expecting: %s", 
                                     _scanner.get_token_type_name(token_type));

            err::set_last_error(msg);
            return {token, err::invalid_state};
        }

        if (_lookahead.type != token_type) {
            auto expected_token = _scanner.get_token_type_name(token_type);
            auto current_token = _scanner.get_token_type_name(_lookahead.type);

            auto msg = fmt::sprintf("Syntax error: Unexpected token: %s, expecting: %s", 
                                     current_token, expected_token);

            err::set_last_error(msg);
            return {token, err::invalid_state};
        }
        
        token = _lookahead;
        err::type e;

        catch_ret(_lookahead, e) = _scanner.get_next_token();

        return {token, err::no_error};
    }
    
    ret<ast_node, err::type> parser::parse(const std::string& program)
    {
        _scanner.load_buffer(program);

        err::type e;
        catch_ret(_lookahead, e) = _scanner.get_next_token();

        return this->program();
    }

    void parser::print(const ast_node& node) const
    {
        fmt::println("Type %d", node.get_type());
        fmt::printf("(%s,%s,[", desc[node.get_type()], node.get_text());
        int flag=0;
        node.iterate_nodes([this, &flag](const ast_node& child_node) -> void {
            if(flag==0) {
                flag = 1;
                fmt::printf(",");
            }
            print(child_node);
        });
        fmt::printf("]");
        fmt::printf(")");
    }

    /**
     * Program
     *  : StatementList
     *  ;
     */
    ret<ast_node, err::type> parser::program()
    {
        return expression();
    }

    /**
     * StatementList
     *  : Statement
     *  | StatementList Statement
     *  ; 
     */
    ret<ast_node, err::type> parser::statement_list()
    {
        ast_node node;

        return {std::move(node), err::no_error};
    }

    /**
     * Statement
     *  : ExpressionStatement
     *  ; 
     */
    ret<ast_node, err::type> parser::statement()
    {
        ast_node node;

        return {std::move(node), err::no_error};
    }

    /**
     * ExpressionStatement
     *  : Expression ';'
     *  ; 
     */
    ret<ast_node, err::type> parser::expression_statement()
    {
        ast_node node;

        return {std::move(node), err::no_error};
    }

    /**
     * Expression
     *  : Literal
     *  ; 
     */
    ret<ast_node, err::type> parser::expression()
    {
        return literal();
    }

    /**
     * Literal
     *  : NummericLiteral
     *  | StringLiteral
     *  ; 
     */
    ret<ast_node, err::type> parser::literal()
    {
        ast_node node;

        switch (_lookahead.type)
        {
        case Number:
            return numeric_literal();
        case String:
            return string_literal();
        }

        err::set_last_error("Syntax Error : unexpected Literal production");
        return {std::move(node), err::invalid_state};
    }

    /**
     * NumericLiteral
     *  : NUMBER
     *  ; 
     */
    ret<ast_node, err::type> parser::numeric_literal()
    {
        ast_node node;
        fmt::println("numeric_literal");
        auto [token, e] = consume_token(Number);
        if (e != err::no_error) {
            return {std::move(node), e};
        }

        node.set_text(token.text);
        node.set_type(NumericLiteral);

        return {std::move(node), err::no_error};
    }

    /**
     * StringLiteral
     *  : STRING
     *  ; 
     */
    ret<ast_node, err::type> parser::string_literal()
    {
        ast_node node;

        auto [token, e] = consume_token(String);
        if (e != err::no_error) {
            return {std::move(node), e};
        }

        node.set_text(token.text);
        node.set_type(StringLiteral);
        
        return {std::move(node), err::no_error};
    }

} // namespace motyf