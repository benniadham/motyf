#include <motyf/motyf.hpp>

auto main() -> int 
{
    motyf::parser parser;

    auto [node, e] = parser.parse("100");

    if (e != ltd::err::no_error) {
        fmt::println("Error: %s", ltd::err::get_last_error());
        return 1;
    }

    parser.print(node);

    return 0;
}
