#include "../include/motyf/scanner.hpp"

#include <regex>

namespace motyf
{
    token::token()
    {
        reset();
    }

    void token::reset()
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
        stream = program;
        buffer = stream.c_str();
    }

    void scanner::add_token_spec(int type, const std::string& name, const std::string& pattern)
    {
        token_spec spec = {type, name, pattern};
        token_specs[type] = spec;
    }
    
   ret<token,err::type> scanner::get_next_token()
    {
        token tok;

        if (is_eof())
            return {tok, err::not_found};

        for (auto spec : token_specs) 
        {
            std::cmatch cm;
            std::regex rex(spec.second.pattern);

            if (std::regex_search (&buffer[cursor], cm, rex) == false) {
                continue;
            }

            tok.type = spec.second.type;
            tok.text = cm[0];

            cursor += tok.text.length();

            return {tok, err::no_error};
        }
        
        auto error_message = fmt::sprintf("Syntax Error: Unexpexted token: '%c'", buffer[cursor]);
        err::set_last_error(error_message);
        return {tok, err::invalid_operation};
    }

    bool scanner::is_eof() const
    {
        return cursor < stream.length() ? false : true;
    }

    std::string scanner::token_type_name(int type)
    {
        auto tok = token_specs[type];
        return tok.name;
    }
}