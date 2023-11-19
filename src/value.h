#pragma once

#include <string>
#include "json_iterator.h"
#include "visitor.h"

class Value {
public:
    virtual std::string toString() {}
    virtual JsonIterator * createIterator(){}
    virtual void accept(JsonVisitor * visitor){}
};