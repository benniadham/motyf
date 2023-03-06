#include "../include/motyf/ast_node.hpp" 

namespace motyf
{
    ast_node::ast_node() : _type(0)
    {

    }

    ast_node::ast_node(int type, const std::string& text)
        : _type(type), _text(text)
    {

    }
    
    ast_node::ast_node(ast_node&& other)
    {
        _body = std::move(other._body);
        _text = other._text;
        _type = other._type;
    }

    ast_node& ast_node::operator=(ast_node&& other)
    {
        _body = std::move(other._body);
        _text = other._text;
        _type = other._type;

        return *this;
    }

    void ast_node::set_text(const std::string& text)
    {
        _text = text;
    }

    void ast_node::set_type(int type)
    {
        _type = type;
    }

    std::string ast_node::get_text()  const
    {
        return _text;
    }

    int ast_node::get_type() const
    {
        return _type;
    }

    size_t ast_node::get_body_size() const
    {
        return _body.size();
    }

    void ast_node::iterate_nodes(std::function<void(const ast_node&)> func) const
    {
        int len = _body.size();
        for (int i=0; i<len;i++) {
            func(_body[i]);
        }
    }
    
    void ast_node::put_node(ast_node&& node)
    {
        _body.push_back(std::move(node));
    }
}