#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"
#include <fstream>
#include <iostream>
#include <sstream>

class StreamOutVisitor : public Visitor {
public:
    void visitFile(File * file){
        result += "_____________________________________________\n";
        result += file->path();
        result += "\n---------------------------------------------\n" ;
        ifstream ifs(file->path(), ios::in);
        if(!ifs.is_open()){
            throw exception();
        }
        stringstream ss;
        ss << ifs.rdbuf();
        result += ss.str();
        result += "\n_____________________________________________";
        ifs.close();
    }

    void visitFolder(Folder * folder){
        auto it = folder->createIterator();
        for(it->first(); !it->isDone(); it->next()){
            it->currentItem()->accept(this);
            result += "\n\n";
        }
    }

    string getResult() const{
        return result;
    }

private:
    string result;
};