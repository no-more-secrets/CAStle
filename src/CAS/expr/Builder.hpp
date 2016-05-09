#pragma once

#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include "Expression.hpp"

namespace Numbers {

class Number;

}

namespace DS {
namespace CAS {
namespace Expressions {

class Builder : private boost::noncopyable
{
public:
    virtual ~Builder() {}

    virtual Expression::Ptr operator()(const string& name) const;
    virtual Expression::Ptr operator()(const string& name, const vector<Expression::Ptr>& children) const;
    virtual Expression::Ptr operator()(const string& name, Expression::Ptr ptr) const;
    virtual Expression::Ptr operator()(const string& name, Expression::Ptr ptr1, Expression::Ptr ptr2) const;

    virtual Expression::Ptr symbol(const string&) const = 0;
    virtual Expression::Ptr symbol(const string&, Expression::Ptr) const = 0;
    virtual Expression::Ptr symbol(const string&, Expression::Ptr, Expression::Ptr) const = 0;
    virtual Expression::Ptr symbol(const string&, const vector<Expression::Ptr>&) const = 0;
    virtual Expression::Ptr literal(Numbers::Number*) const = 0;
    virtual Expression::Ptr literal(const Numbers::Number&) const = 0;
    virtual Expression::Ptr add(Expression::Ptr, Expression::Ptr) const = 0;
    virtual Expression::Ptr add(const vector<Expression::Ptr>&) const = 0;
    virtual Expression::Ptr add(const vector<Expression::Ptr>&, const vector<Sign>&) const = 0;
    virtual Expression::Ptr subtract(Expression::Ptr, Expression::Ptr) const = 0;
    virtual Expression::Ptr negate(Expression::Ptr) const = 0;
    virtual Expression::Ptr multiply(Expression::Ptr, Expression::Ptr) const = 0;
    virtual Expression::Ptr multiply(const vector<Expression::Ptr>&) const = 0;
    virtual Expression::Ptr divide(Expression::Ptr top, Expression::Ptr bottom) const = 0;
    virtual Expression::Ptr modulus(Expression::Ptr top, Expression::Ptr bottom) const = 0;
    virtual Expression::Ptr power(Expression::Ptr base, Expression::Ptr power) const = 0;
    virtual Expression::Ptr factorial(Expression::Ptr) const = 0;
};

} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */