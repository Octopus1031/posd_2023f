#pragma once

#include <string>

#include "file.h"
#include "folder.h"
#include "visitor.h"

class FindByNameVisitor : public Visitor{
public:
    FindByNameVisitor(const char * name): _name(name) {
    }

    void visitFile(File * file){
        if(!file->name().compare(_name)){
            _path.push_back(file->path());
        }
    }

    void visitFolder(Folder * folder){
        if(!folder->name().compare(_name)){
            _path.push_back(folder->path());
        }
        else{
            auto it = folder->createIterator();
            for(it->first(); !it->isDone(); it->next()){
                it->currentItem()->accept(this);
            }
        }
    }

    std::list<string> getPaths() const{
        return _path;
    }
    
private:
    const char * _name;
    std::list<string> _path;
};
