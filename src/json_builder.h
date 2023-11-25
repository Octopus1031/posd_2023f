#pragma once

#include <string>
#include <stack>

#include "json_object.h"
#include "string_value.h"

class JsonBuilder {
public:
    void buildValue(std::string key, std::string value){
        // std::cout << "bv key:" << key << " value:" << value << std::endl;
        Value * v = new StringValue(value);
        objects.top()->set(key, v);
    }

    void buildObject(std::string key){
        // std::cout << "bo key:" << key << std::endl;
        if(!key.compare("")){ // inital Json object
            root = new JsonObject();
            objects.push(root);
        }
        else{
            objects.push(new JsonObject());
        }
        keys.push(key);
    }

    void endObject(){
        // std::cout << "end o" << std::endl;
        JsonObject * jo = objects.top();
        objects.pop();
        std::string key = keys.top();
        keys.pop();
        if( !objects.empty() ){
            objects.top()->set(key, jo);
        }
    }

    JsonObject * getJsonObject(){
        return root;
    }

private:
    JsonObject * root;
    std::stack<JsonObject *> objects;
    std::stack<std::string> keys;
};
