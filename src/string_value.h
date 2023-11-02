#pragma once

#include <string>
#include "value.h"
#include "visitor.h"

class StringValue : public Value {
public:
    // StringValue(string key) : _key(key) {}
    StringValue(std::string k){
        _key = k;
    }

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


