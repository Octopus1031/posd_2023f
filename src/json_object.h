#pragma once

#include "value.h"
#include "string_value.h"
#include "json_iterator.h"
#include "visitor.h"

#include <map>
class JsonObject : public Value {
private:
    std::map<std::string, Value *> sets;

public:
    std::string toString() override {
        std::string s = "{\n";
        unsigned n=0;
        for(const auto &jsonPair : sets){
            s+= "\"" + jsonPair.first + "\":";
            s+= jsonPair.second->toString();
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
        if(sets.find(k)!=sets.end())
            return sets.find(k)->second;
        else
            throw std::string("getValue error");
    }

    JsonIterator * createIterator() override {
        return new JsonObjectIterator(this);
    }

    void accept(JsonVisitor * visitor) override {
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

        Value* currentValue(){
            return it->second;
        }

        void next(){
            it++;
        }

        bool isDone(){
            return it==_jo->sets.end();
        }

        bool lastOne(){
            auto _it = _jo->sets.end();
            _it--;
            return it==_it;
        }

    private:
        std::map<std::string, Value *>::iterator it;
        JsonObject * _jo;
    };


};