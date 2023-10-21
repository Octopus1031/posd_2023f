#pragma once

#include "node.h"
#include "visitor.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

class File: public Node {
public:
    // File(string path): Node(path) {}
    File(string path): Node(path){
        struct stat buf;
        if(!stat(path.c_str(), &buf)){
            if(S_ISDIR(buf.st_mode)){
                // Can't work!
                // throw string("Can't create File obj to a Folder by path" + path);
                throw exception();
            }
        }
        else{
            throw exception();
        }
    }

    int numberOfFiles() const override{
        return 1;
    }

    Node * find(string path) override{
        if (this->path() == path) {
            return this;
        }
        return nullptr;
    }

    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }
        return pathList;
    }

    void accept(Visitor * v) override{
        v->visitFile(this);
    }
};