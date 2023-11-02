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
            root->add(file);
    }

    void buildFolder(string path){
        Folder * folder = new Folder(path);
    }

    void endFolder(Folder *folder){
        root->add(folder);
    }

    //add
    void setPath(string path){
        root = new Folder(path);
    }

private:
    Folder * root;
};
