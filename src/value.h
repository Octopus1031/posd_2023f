#pragma once

#include <string>
#include "json_iterator.h"

class Value {
public:
    virtual std::string toString() {}
    virtual JsonIterator * createIterator(){}
};