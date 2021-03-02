#include "Session.hpp"

#include <string>

class ForwardDeclared
{
public:
    kuzco::Node<std::string> a;
    kuzco::Node<std::string> b;
};

Session::Session()
    : m_froot({})
{}

Session::~Session() = default;
