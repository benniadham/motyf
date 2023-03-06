#ifndef _MOTYF_INCLUDE_AST_NODE_HPP_
#define _MOTYF_INCLUDE_AST_NODE_HPP_

#include <vector>
#include <string>
#include <functional>

namespace motyf
{
    class ast_node
    {
    private:
        std::vector<ast_node> _body;
        std::string           _text;
        int                   _type;

    public:
        ast_node();
        ast_node(int type, const std::string& text);

        ast_node(ast_node&& other);
        ast_node& operator=(ast_node&& other);

        ast_node(const ast_node& other) = delete;
        ast_node& operator=(const ast_node& other) = delete;

        std::string get_text()  const;
        void set_text(const std::string& text);

        int get_type() const;
        void set_type(int type);

        size_t get_body_size() const;
        void iterate_nodes(std::function<void(const ast_node&)> func) const;
        
        void put_node(ast_node&& node);
    };
} // namespace motyf

#endif // _MOTYF_INCLUDE_AST_NODE_HPP_