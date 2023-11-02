#pragma once

#include <string>

class Value;

class JsonIterator {
public:
    virtual void first(){}

    virtual std::string currentKey(){}

    virtual Value * currentValue(){}

    virtual void next(){}
    virtual bool isDone(){}
};

class NullIterator : public JsonIterator {
public:
    std::string currentKey(){
        throw std::string("NullIterator currentKey error");
    }

    Value * currentValue(){
        throw std::string("NullIterator currentValue error");
    }

    bool isDone(){
        return true;
    }
};