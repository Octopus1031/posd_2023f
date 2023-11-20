#pragma once

#include <string>
#include <stack>

#include "json_object.h"
#include "string_value.h"

class JsonBuilder {
public:
    void buildValue(std::string key, std::string value);

    void buildObject(std::string key){
        if(key.compare("")){ // inital Json object
            root = new JsonObject();
            objects.push(root);
        }
        else{
            JsonObject * jo = new JsonObject();
            objects.push(jo);
        }
    }

    void endObject();

    JsonObject * getJsonObject();

private:
    JsonObject * root;
    std::stack<JsonObject *> objects;
};
