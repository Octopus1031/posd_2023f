#pragma once

#include "value.h"

#include <map>
class JsonObject : public Value {
public:
    std::string toString() {
        std::string s = "{\n";
        // s+= "\"" + sets.begin()->first + "\":";
        // s+= sets.begin()->second->toString();
        unsigned n=0;
        for(const auto& [key, value] : sets){
            s+= "\"" + key + "\":";
            s+= value->toString();
            if( n!=sets.size()-1 ){
                s+=",\n";
            }
            n++;
        }

        s+= "\n}";
        return s;
    }

    void set(std::string key, Value* value){
        sets[key] = value;
    }

    Value* getValue(std::string k){
        return sets.find(k)->second;
    }

private:
    std::map<std::string, Value *> sets;
};