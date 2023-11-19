#pragma once

#include <string>
#include "value.h"
#include "visitor.h"

class StringValue : public Value {
public:
    StringValue(std::string key) : _key(key) {}

    std::string toString() {
        return "\"" + _key + "\"";
    }

    JsonIterator * createIterator(){
        return new NullIterator();
    }

    void accept(JsonVisitor * visitor){
        visitor->visitStringValue(this);
    }

private:
    std::string _key;
};


