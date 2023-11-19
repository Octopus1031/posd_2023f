#pragma once

#include <string>

class Value;
class StringValue;

class JsonIterator {
public:
    virtual void first(){}

    virtual std::string currentKey() = 0;

    virtual Value* currentValue(){
        return nullptr;
    }

    virtual void next(){}
    virtual bool isDone(){
        return true;
    }
    virtual bool lastOne() = 0;
};

class NullIterator : public JsonIterator {
public:
    std::string currentKey(){
        throw std::string("NullIterator currentKey error");
    }

    Value* currentValue(){
        throw std::string("NullIterator currentValue error");
    }

    bool isDone(){
        return true;
    }

    bool lastOne(){
        return false;
    }
};