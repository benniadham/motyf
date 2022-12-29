#include <iostream>
#include <cstring>
#include "parser.hpp"

#define syntax_error(S)                            \
do {                                               \
    std::cerr << "syntax error at line "           \
        << lex->get_lineno() << ": " << S << '\n'; \
} while (false)

motyf::parser::parser(lexer *lex)
{
    this->lex = lex;
}

bool motyf::parser::parse()
{
    if (! module_declaration())
        return false;

    if (! imports())
        return false;

    if (! definitions())
        return false;

    return true;
}

bool motyf::parser::module_declaration(void)
{
    if (! lex->match(token::id)) {
        syntax_error("expecting 'module' name");
        return false;
    }

    if (strcmp(lex->get_lexeme(), "module") != 0) {
        syntax_error("expecting 'module' name");
        return false;
    }

    if (! module_name())
        return false;

    if (! lex->match(token::newline)) {
        syntax_error("expecting newline");
        return false;
    }

    return true;
}

bool motyf::parser::imports(void)
{
    while (lex->match_lookahead(token::id)) {
        if (strcmp(lex->get_lexeme(), "import") != 0)
            break;

        lex->advance(); /* token::id "import" */

        if (! import_name())
            return false;

        if (! lex->match(token::newline)) {
            syntax_error("expecting newline");
            return false;
        }
    }

    return true;
}

bool motyf::parser::module_name(void)
{
    if (! lex->match(token::id)) {
        syntax_error("expecting module identifier");
        return false;
    }

    if (lex->match_lookahead(token::dot)) {
        lex->advance(); /* token::dot */
        if (! module_name())
            return false;
    }

    return true;
}

bool motyf::parser::import_name(void)
{
    if (! lex->match(token::id)) {
        syntax_error("expecting import identifier");
        return false;
    }

    if (lex->match_lookahead(token::dot)) {
        lex->advance(); /* token::dot */
        if (! import_name())
            return false;
    }

    return true;
}

bool motyf::parser::definitions(void)
{
    return true;
}

bool motyf::parser::type_definition(void)
{
    return true;
}
