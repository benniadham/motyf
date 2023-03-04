#ifndef _MOTYF_INCLUDE_SCANNER_HPP_
#define _MOTYF_INCLUDE_SCANNER_HPP_

#include <ltd/ltd.hpp>
#include <string>
#include <vector>
#include <map>

using namespace ltd;

namespace motyf 
{
    class scanner
    {
    public:
        struct token
        {
            int type;
            int start;
            int end;
            int line_no;
            
            std::string text;

            token();
            void reset();
        };

    private: // private types and member variables
        struct token_spec
        {
            int type;
            std::string name;
            std::string pattern;
        };

        std::map<int, token_spec> _specs;
        std::string _program;
        const char *_buffer;

        int _cursor = 0;
        
    public: // ctor and operations

        /**
         * @brief
         * Scanner constructor.
         */
        scanner();
        
        /**
         * @brief
         * Load stream from a string buffer. 
         */
        void load_buffer(const std::string& program);

        /**
         * @brief 
         * Translate token type enum to a string. 
         * 
         * @param type  The type of the token as token_type enum.
         * @returns     The string name of the token.
         */
        std::string get_token_type_name(int type);

        /**
         * @brief
         * Add a token specification to the scanner. 
         * 
         * @param type  The type of the token as token_type enum.
         */
        void add_token_spec(int type, const std::string& name, const std::string& pattern);
        
        /**
         * @brief 
         * Read next token.
         * 
         * @returns token       The next token. invalid_token is returned if there is no more token.
         * @returns err::type   The error code if there is an error.
         */
        ret<token,err::type> get_next_token();

        /**
         * @brief
         * Check whether the scanner has hit EOF.
         * 
         * @returns True if the scanner has reach the end of the stream, false otherwise.
         */
        bool is_eof() const;    
    };
    
}

#endif // _MOTYF_INCLUDE_SCANNER_HPP_