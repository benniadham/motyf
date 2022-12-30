#ifndef MOTYF_LEXER
#define MOTYF_LEXER

#include <cstddef>

#include "error.hpp"

#define LEXER_LEXEME_MAXBUF (128)

namespace motyf {
    /**
     * @brief
     * Checks whether provided character is numeric
     */
    bool is_numeric(char);

    /**
     * @brief
     * Checks whether provided character legal character for
     * keywords and identifiers.
     */
    bool is_legal(char);

    /**
     * @brief
     * Checks whether provided character is to be ignored by the lexer.
     */
    bool is_ignored(char);

    /**
     * @brief
     * Checks whether provided character marks the beginning of a keyword
     * or an identifier.
     */
    bool is_key_or_id(char);

    enum class token {
        null, /* [ \0 ] */
        unrecognized, /* Unrecognized */
        newline, /* \n */
        tilde, /* [ ~ ] */
        backtick, /* [ ` ] */
        exclamation, /* [ ! ] */
        at, /* [ @ ] */
        numbersign, /* [ # ] */
        dollar, /* [ $ ] */
        percent, /* [ % ] */
        caret, /* [ ^ ] */
        ampersand, /* [ & ] */
        asterisk, /* [ * ] */
        leftparenthesis, /* [ ( ] */
        rightparenthesis, /* [ ) ] */
        minus, /* [ - ] */
        underscore, /* [ _ ] */
        equalsign, /* [ = ] */
        plus, /* [ + ] */
        leftbracket, /* [ [ ] */
        leftbrace, /* [ { ] */
        rightbracket, /* [ ] ] */
        rightbrace, /* [ } ] */
        backslash, /* [ \ ] */
        verticalbar, /* [ | ] */
        semicolon, /* [ ; ] */
        colon, /* [ : ] */
        apostrophe, /* [ ' ] */
        quotation, /* [ " ] */
        comma, /* [ , ] */
        leftchevron, /* [ < ] */
        dot, /* [ . ] */
        rightchevron, /* [ > ] */
        slash, /* [ / ] */
        questionmark, /* [ ? ] */
        unary_plus, /* [ ++ ] */
        unary_minus, /* [ -- ] */
        relational_less_equal, /* [ <= ] */
        relational_greater_equal, /* [ >= ] */
        relational_equal, /* [ == ] */
        relational_not_equal, /* [ != ] */
        logical_and, /* [ && ] */
        logical_or, /* [ || ] */
        shift_left, /* [ << ] */
        shift_right, /* [ >> ] */
        assignment_plus, /* [ += ] */
        assignment_minus, /* [ -= ] */
        assignment_multiply, /* [ *= ] */
        assignment_divide, /* [ /= ] */
        assignment_modulo, /* [ %= ] */
        assignment_bitwise_and, /* [ &= ] */
        assignment_bitwise_or, /* [ |= ] */
        assignment_bitwise_xor, /* [ ^= ] */
        assignment_bitwise_shirt_left, /* [ <<= ] */
        assignment_bitwise_shirt_right, /* [ >>= ] */
        numeric, /* Numeric constant / literal */
        id /* Keyword or identifier */
    };

    class lexer {
        char        *text;
        const char  *current;
        char         lexeme[LEXER_LEXEME_MAXBUF];
        bool         was_newline;
        unsigned int lineno;
        error        err;

        /**
         * @brief
         * Skips ignored characters, comments, whitespaces, and empty lines.
         */
        void skip(void);

        /**
         * @brief
         * Tokenizes current input.
         * If `proceed` is true, progresses the lexer.
         */
        token lex(bool);

    public:
        lexer(const char *);

        ~lexer();

        /**
         * @brief
         * Returns current token and progresses the lexer.
         */
        token next(void);

        /**
         * @brief
         * Returns current token and without progressing the lexer.
         */
        token lookahead(void);

        /**
         * @brief
         * Just progresses the lexer without doing anything else.
         * Should be called when current token is certainly known.
         */
        void advance(void);

        /**
         * @brief
         * Checks whether current token matches the expected token
         * and progresses the lexer.
         */
        bool match(token);

        /**
         * @brief
         * Checks whether current token matches the expected token
         * without progressing the lexer.
         */
        bool match_lookahead(token);

        /**
         * @brief
         * Returns the lexeme of last recognized token.
         * Note that lexemes of singulative tokens shall
         * not be stored.
         */
        const char *get_lexeme(void);

        /**
         * @brief
         * Returns currently analyzed line number.
         */
        unsigned int get_lineno(void);

        /**
         * @brief
         * Checks whether the lexical analyzer is in error state.
         */
        bool is_error(void);

        /**
         * @brief
         * Returns last error occured.
         */
        error get_error(void);
    };
}

#endif
