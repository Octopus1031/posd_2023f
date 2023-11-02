#pragma once

#include <string>
#include <stack>

#include "folder.h"
#include "file.h"

using std::string;

class FileSystemBuilder {
public:
    Folder * getRoot() const{
        return root;
    }

    void buildFile(string path){
        File * file = new File(path);
        if(_stack.empty())
            root->add(file);
        else
            _stack.top()->add(file);
    }

    void buildFolder(string path){
        Folder * folder = new Folder(path);
        _stack.push(folder);
    }

    void endFolder(){
        Folder * folder = _stack.top();
        _stack.pop();
        if(_stack.empty())
            root->add(folder);
        else
            _stack.top()->add(folder);
    }

    //add
    void setPath(string path){
        root = new Folder(path);
    }

private:
    std::stack<Folder*> _stack;
    Folder * root;
};
