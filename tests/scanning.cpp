#include <motyf/motyf.hpp>

auto main() -> int 
{
    motyf::scanner scanner;
    
    scanner.load_buffer(" 123  456 789      my_var do_something(1,2,3)");
    scanner.add_token_spec(0, "Whitespace", "^[ \\t]+");
    scanner.add_token_spec(1, "Numeric", "^[0-9]+");
    scanner.add_token_spec(2, "Identifier", "^[a-zA-Z_]+");
    scanner.add_token_spec(3, "(", "^\\(");
    scanner.add_token_spec(4, ")", "^\\)");
    scanner.add_token_spec(5, ",", "^,");

    while(scanner.is_eof() == false) {
        auto [token, err]  = scanner.get_next_token();

        if(err == ltd::err::not_found) {
            ltd::fmt::println("Unrecognize token to parse");
            return -1;
        }
            
        if (token.type == 0)
            continue;

        ltd::fmt::println("'%s'", token.text);
    }
    
    
    return 0;
}