#include "../include/motyf/scanner.hpp"

#include <regex>

namespace motyf
{
    scanner::token::token()
    {
        reset();
    }

    void scanner::token::reset()
    {
        type    = -1;
        start   = -1;
        end     = -1;
        line_no = -1;
        text    = "";
    }

    scanner::scanner()
    {
        
    }

    void scanner::load_buffer(const std::string& program)
    {
        _program = program;
        _buffer  = _program.c_str();
    }

    void scanner::add_token_spec(int type, const std::string& name, const std::string& pattern)
    {
        token_spec spec = {type, name, pattern};

        _specs[type] = spec;
    }
    
   ret<scanner::token,err::type> scanner::get_next_token()
    {
        scanner::token token;

        if (is_eof())
            return {token, err::not_found};

        for (auto spec : _specs) 
        {
            std::cmatch cm;
            std::regex rex(spec.second.pattern);

            if (std::regex_search (&_buffer[_cursor], cm, rex) == false) {
                continue;
            }

            token.type = spec.second.type;
            token.text = cm[0];

            _cursor += token.text.length();

            return {token, err::no_error};
        }
        
        auto error_message = fmt::sprintf("Syntax Error: Unexpexted token: '%c'", _buffer[_cursor]);
        err::set_last_error(error_message);

        return {token, err::invalid_operation};
    }

    bool scanner::is_eof() const
    {
        return _cursor < _program.length() ? false : true;
    }

    std::string scanner::get_token_type_name(int type)
    {
        auto token = _specs[type];
        return token.name;
    }
}