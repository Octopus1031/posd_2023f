#pragma once

#include <string>

// #include "visitor.h"
#include "node.h"

class FindByNameVisitor{
public:
    FindByNameVisitor(const char * name): _name(name) {
    }

    // File* findByName(File* file){
    //     if(!file->name().compare(_name)){
    //         return file;
    //     }
    //     return nullptr;
    // }
    
    Node * findByName(Node* n){
        if(!n->name().compare(_name)){
            return n;
        }
        return n->getChildByName(_name);
    }
    

private:
    const char * _name;
};