#pragma once

#include <string>

#include "../src/json_iterator.h"

#include <iostream>

class BeautifyVisitor : public JsonVisitor {
public:
    BeautifyVisitor(){
        result = "";
    }
    void visitJsonObject(JsonObject * obj){
        result+= "{\n";
        
        JsonIterator* it = obj->createIterator();
        ++layer;
        for(it->first(); !it->isDone(); it->next()){
            for(int i=0; i<layer; i++){
                result+="    ";
            }
            result+= "\"" + it->currentKey() + "\": ";
            it->currentValue()->accept(this);
            if( !it->lastOne() ){
                result+=",";
            }
            result+="\n";
        }
        layer--;
        for(int i=0; i<layer; i++){
            result+="    ";
        }
        result+= "}";
    }

    void visitStringValue(StringValue * val){
        result+=val->toString();
    }

    std::string getResult() const{
        return result;
    }

private:
    std::string result;
    int layer = 0;
};