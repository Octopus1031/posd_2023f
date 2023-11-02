#pragma once

#include <string>
class StringValue : public Value {
public:
    // StringValue(string key) : _key(key) {}
    StringValue(std::string k){
        _key = k;
    }

    std::string toString() {
        return "\"" + _key + "\"";
    }

private:
    std::string _key;
};


