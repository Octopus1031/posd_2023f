#pragma once
#include <dirent.h>
#include <string>
#include <vector>

#include "node.h"

using std::string;

class FileSystemScanner {
public:
    FileSystemScanner(){
        start = false;
    }
    bool isFile(){
        // if(this->isDone()){ return false; }
        return entry->d_type != DT_DIR;
    }

    bool isFolder(){
        // if(this->isDone()){ return false; }
        return entry->d_type == DT_DIR;
    }

    bool isDone(){
        return entry==NULL && start;
        // return entry==NULL;
    }

    void setPath(string path){
        dir = opendir(path.c_str());
    }

    string currentNodeName(){
        return string(entry->d_name);
    }

    void nextNode(){
        if( !start ){ start = true; }
        entry = readdir(dir);
        if( !this->isDone() ){
            while( !string(entry->d_name).compare(".") || !string(entry->d_name).compare("..") ){
                entry = readdir(dir);
            }
            nodeVector.push_back(entry->d_name);
        }
    }

    std::vector<string> getVector(){
        return nodeVector;
    }

    bool isStart(){
        return start;
    }

private:
    // map<std::string, Node*> * m;
    std::vector<string> nodeVector;

    DIR * dir;
    struct dirent * entry;
    bool start;
};
