#pragma once

#include "./json_scanner.h"
#include "./json_builder.h"
#include "./json_object.h"
#include <string>
#include <regex>

class JsonParser {
public:
    JsonParser(JsonScanner * scanner, JsonBuilder * builder): _scanner(scanner), _builder(builder) {}

    void parse() {
        std::string key = "";
        while (!_scanner->isDone()) {
            char token = _scanner->next();
            if(token == ' ') {
                continue;
            }
            else if (token == '{') {
                _builder->buildObject(key);
            }
            else if (token == '"') {
                std::string value;
                token = _scanner->next();
                while(token != '"') {
                    value += token;
                    token = _scanner->next();
                }
                token = _scanner->next();

                while (token == ' ' || token == '\n') {
                // while (token == ' ') {
                    token = _scanner->next();
                }
                
                if(token == ':') {
                    key = value;
                }
                else if(token == ',') {
                    _builder->buildValue(key, value);
                }
                else if (token == '}') {
                    // std::cout << "~~~~~" << std::endl;
                    _builder->buildValue(key, value);
                    std::cout << "~~~~~" << std::endl;
                    _builder->endObject();
                }
                // std::cout << "~temp t: " << token << "|" << std::endl;
                // std::cout << "~temp v: " << value << std::endl;
            }
            else if (token == '}') {
                // std::cout << "=====" << std::endl;
                _builder->endObject();
            }

            // std::cout << "~temp k: " << key << std::endl;
        }
    }

    JsonObject * getJsonObject() {
        return _builder->getJsonObject();
    }

    void setInput(std::string input) {
        _scanner->setInput(input);
    }

private:
    JsonScanner * _scanner;
    JsonBuilder * _builder;
};