#include <cctype>
#include <cstring>
#include <cstdlib>
#include "lexer.hpp"

/* Proceeds by adding current offset pointer to input by N bytes. */
#define proceed_lexer(N) if (proceed) this->current += N

bool motyf::is_numeric(char c)
{
    return isdigit(c);
}

bool motyf::is_legal(char c)
{
    return (isalnum(c) || c == '_');
}

bool motyf::is_ignored(char c)
{
    return ((c >= 1 && c <= 9) ||(c >= 11 && c <= 32) || c == 127);
}

bool motyf::is_key_or_id(char c)
{
    return (isalpha(c) || c == '_');
}

motyf::lexer::lexer(const char *in)
{
    size_t sz = strlen(in);

    this->text = (char *) malloc(sz + sizeof(char));
    if (text == NULL) {
        this->err = error::allocation_failure;
        return;
    }

    (void) memcpy(this->text, in, sz);
    this->text[sz] = '\0';

    this->current = this->text;
    this->lineno = 1;
    this->err = error::no_error;
}

motyf::lexer::~lexer()
{
    if (this->text == NULL)
        return;

    free(this->text);
    this->text = NULL;
}

motyf::token motyf::lexer::next(void)
{
    return this->lex(true);
}

motyf::token motyf::lexer::lookahead(void)
{
    return this->lex(false);
}

void motyf::lexer::advance(void)
{
    this->skip();

    if (is_key_or_id(*(this->current)))
        do { ++(this->current); } while (is_legal(*(this->current)));
    else if (is_numeric(*(this->current)))
        do { ++(this->current); } while (is_numeric(*(this->current)));
    else
        do { ++(this->current); } while (is_ignored(*(this->current)));
}

bool motyf::lexer::match(token tok)
{
    return this->lex(true) == tok;
}

bool motyf::lexer::match_lookahead(token tok)
{
    return this->lex(false) == tok;
}

const char *motyf::lexer::get_lexeme(void)
{
    return this->lexeme;
}

unsigned int motyf::lexer::get_lineno(void)
{
    return this->lineno;
}

bool motyf::lexer::is_error(void)
{
    return this->err != error::no_error;
}

motyf::error motyf::lexer::get_error(void)
{
    return this->err;
}

void motyf::lexer::skip(void)
{
    /* TODO */
}

motyf::token motyf::lexer::lex(bool proceed)
{
    this->skip();
    this->was_newline = false;

    switch (*this->current)
    {
    case '\0':
        return token::null;

    case '\n':
        this->was_newline = true;
        lineno += 1;
        proceed_lexer(1);
        return token::newline;

    case '~':
        proceed_lexer(1);
        return token::tilde;
        break;

    case '`':
        proceed_lexer(1);
        return token::backtick;
        break;

    case '!':
        if (*(this->current + 1) == '=') {
            proceed_lexer(2);
            return token::relational_not_equal;
        }

        proceed_lexer(1);
        return token::exclamation;
        break;

    case '@':
        proceed_lexer(1);
        return token::at;
        break;

    case '#':
        proceed_lexer(1);
        return token::numbersign;
        break;

    case '$':
        proceed_lexer(1);
        return token::dollar;
        break;

    case '%':
        if (*(this->current + 1) == '=') {
            proceed_lexer(2);
            return token::assignment_modulo;
        }

        proceed_lexer(1);
        return token::percent;
        break;

    case '^':
        if (*(this->current + 1) == '=') {
            proceed_lexer(2);
            return token::assignment_bitwise_xor;
        }

        proceed_lexer(1);
        return token::caret;
        break;

    case '&':
        if (*(this->current + 1) == '&') {
            proceed_lexer(2);
            return token::logical_and;
        } else if (*(this->current + 1) == '=') {
            proceed_lexer(2);
            return token::assignment_bitwise_and;
        }

        proceed_lexer(1);
        return token::ampersand;
        break;

    case '*':
        if (*(this->current + 1) == '=') {
            proceed_lexer(2);
            return token::assignment_multiply;
        }

        proceed_lexer(1);
        return token::asterisk;
        break;

    case '(':
        proceed_lexer(1);
        return token::leftparenthesis;
        break;

    case ')':
        proceed_lexer(1);
        return token::rightparenthesis;
        break;

    case '-':
        if (*(this->current + 1) == '-') {
            proceed_lexer(2);
            return token::unary_minus;
        } else if (*(this->current + 1) == '=') {
            proceed_lexer(2);
            return token::assignment_minus;
        }

        proceed_lexer(1);
        return token::minus;
        break;

    case '_':
        proceed_lexer(1);
        return token::underscore;
        break;

    case '=':
        if (*(this->current + 1) == '=') {
            proceed_lexer(2);
            return token::relational_equal;
        }

        proceed_lexer(1);
        return token::equalsign;
        break;

    case '+':
        if (*(this->current + 1) == '+') {
            proceed_lexer(2);
            return token::unary_plus;
        } else if (*(this->current + 1) == '=') {
            proceed_lexer(2);
            return token::assignment_plus;
        }

        proceed_lexer(1);
        return token::plus;
        break;

    case '[':
        proceed_lexer(1);
        return token::leftbracket;
        break;

    case '{':
        proceed_lexer(1);
        return token::leftbrace;
        break;

    case ']':
        proceed_lexer(1);
        return token::rightbracket;
        break;

    case '}':
        proceed_lexer(1);
        return token::rightbrace;
        break;

    case '\\':
        proceed_lexer(1);
        return token::backslash;
        break;

    case '|':
        if (*(this->current + 1) == '|') {
            proceed_lexer(2);
            return token::logical_or;
        } else if (*(this->current + 1) == '=') {
            proceed_lexer(2);
            return token::assignment_bitwise_or;
        }

        proceed_lexer(1);
        return token::verticalbar;
        break;

    case ';':
        proceed_lexer(1);
        return token::semicolon;
        break;

    case ':':
        proceed_lexer(1);
        return token::colon;
        break;

    case '\'':
        proceed_lexer(1);
        return token::apostrophe;
        break;

    case '"':
        proceed_lexer(1);
        return token::quotation;
        break;

    case ',':
        proceed_lexer(1);
        return token::comma;
        break;

    case '<':
        if (*(this->current + 1) == '=') {
            proceed_lexer(2);
            return token::relational_less_equal;
        } else if (*(this->current + 1) == '<' && *(this->current + 2) == '=') {
            proceed_lexer(3);
            return token::assignment_bitwise_shirt_left;
        } else if (*(this->current + 1) == '<') {
            proceed_lexer(2);
            return token::shift_left;
        }

        proceed_lexer(1);
        return token::leftchevron;
        break;

    case '.':
        proceed_lexer(1);
        return token::dot;
        break;

    case '>':
        if (*(this->current + 1) == '=') {
            proceed_lexer(2);
            return token::relational_greater_equal;
        } else if (*(this->current + 1) == '>' && *(this->current + 2) == '=') {
            proceed_lexer(3);
            return token::assignment_bitwise_shirt_right;
        } else if (*(this->current + 1) == '>') {
            proceed_lexer(2);
            return token::shift_right;
        }

        proceed_lexer(1);
        return token::rightchevron;
        break;

    case '/':
        if (*(this->current + 1) == '=') {
            proceed_lexer(2);
            return token::assignment_divide;
        }

        proceed_lexer(1);
        return token::slash;
        break;

    case '?':
        proceed_lexer(1);
        return token::questionmark;
        break;

    default:
        size_t length = 0UL;

        if (is_key_or_id(*this->current)) {
            do {
                this->lexeme[length] = *(this->current + length);
                ++(length);
            } while (is_legal(*(this->current + length)));

            this->lexeme[length] = '\0';

            proceed_lexer(length);
            return token::id;
        } else if (is_numeric(*this->current)) {
            do {
                this->lexeme[length] = *(this->current + length);
                ++(length);
            } while (is_numeric(*(this->current + length)));

            this->lexeme[length] = '\0';

            proceed_lexer(length);
            return token::numeric;
        }

        return token::unrecognized;
        break;
    }
}
