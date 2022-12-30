#ifndef MOTYF_PARSER_HPP
#define MOTYF_PARSER_HPP

#include "lexer.hpp"

namespace motyf {
    /**
     * @brief
     * Motyf's recursive descent parser. This whole part of the compiler is not yet
     * 'flattened' for optimization.
     * TODO: flatten the parser for optimization.
     * TODO: integrate parser with code generator.
     * TODO: better way to initiate lexer?
     */
    class parser {
        lexer *lex;

        bool module_declaration(void);

        bool imports(void);

        bool module_name(void);

        bool import_name(void);

        bool definitions(void);

        bool type_definition(void);
    public:
        parser(lexer *);

        bool parse(void);
    };
}

#endif
