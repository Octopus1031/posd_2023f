#pragma once

#include "value.h"
#include "json_iterator.h"
#include "visitor.h"

#include <map>
class JsonObject : public Value {
private:
    std::map<std::string, Value *> sets;

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

    JsonIterator * createIterator(){
        return new JsonObjectIterator(this);
    }

    void accept(JsonVisitor * visitor){
        visitor->visitJsonObject(this);
    }

    class JsonObjectIterator : public JsonIterator{
    public:
        JsonObjectIterator(JsonObject * jo): _jo(jo){
        }

        void first(){
            it = _jo->sets.begin();
        }

        std::string currentKey(){
            return it->first;
        }

        Value * currentValue(){
            return it->second;
        }

        void next(){
            it++;
        }

        bool isDone(){
            return it==_jo->sets.end();
        }

    private:
        std::map<std::string, Value *>::iterator it;
        JsonObject * _jo;
    };


};