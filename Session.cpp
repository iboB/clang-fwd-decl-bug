#include "Session.hpp"

#include <string>

class ForwardDeclared
{
public:
    kuzco::Node<std::string> a;
    kuzco::Node<std::string> b;
};

Session::Session()
    : m_froot(kuzco::Node<ForwardDeclared>{})

{}

Session::~Session() = default;
