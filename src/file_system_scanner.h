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
        return entry->d_type != DT_DIR;
    }

    bool isFolder(){
        return entry->d_type == DT_DIR;
    }

    bool isDone(){
        return entry==NULL && start;
    }

    void setPath(string path){
        dir = opendir(path.c_str());
    }

    string currentNodeName(){
        return string(entry->d_name);
    }

    void nextNode(){
        if( !start ){ 
            start = true; 
        }
        entry = readdir(dir);
        if( !this->isDone() ){
            while( entry!=NULL && ( !string(entry->d_name).compare(".") || !string(entry->d_name).compare("..") ) ){
                entry = readdir(dir);
            }
            if(entry!=NULL){
                nodeVector.push_back(entry->d_name);
            }
        }
    }

    std::vector<string> getVector(){
        return nodeVector;
    }

    bool isStart(){
        return start;
    }

private:
    std::vector<string> nodeVector;

    DIR * dir;
    struct dirent * entry;
    bool start;
};
