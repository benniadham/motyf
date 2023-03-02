#ifndef _MOTYF_INCLUDE_SCANNER_HPP_
#define _MOTYF_INCLUDE_SCANNER_HPP_

#include <ltd/ltd.hpp>
#include <string>
#include <vector>
#include <map>

using namespace ltd;

namespace motyf 
{
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

    struct token_spec
    {
        int type;
        std::string name;
        std::string pattern;
    };

    class scanner
    {
    private:
        std::map<int, token_spec> token_specs;
        std::map<int,int> type_map;
        std::string stream;
        const char *buffer;
        int cursor = 0;
        
    public:
        scanner();
        
        void load_buffer(const std::string& program);

        std::string token_type_name(int type);

        void add_token_spec(int type, const std::string& name, const std::string& pattern);
        
        ret<token,err::type> get_next_token();

        bool is_eof() const;
    };
    
}

#endif // _MOTYF_INCLUDE_SCANNER_HPP_