#pragma once
#include <dirent.h>
#include <string>
// #include <map>
#include <vector>

#include "node.h"

using std::string;

class FileSystemScanner {
public:
    bool isFile();

    bool isFolder();

    bool isDone(){
        return entry==NULL;
    }

    void setPath(string path){
        dir = opendir(path.c_str());
    }

    string currentNodeName();

    void nextNode(){
        entry = readdir(dir);
        while( string(entry->d_name).compare(".") || string(entry->d_name).compare("..") ){
            entry = readdir(dir);
        }
        // nodeList.push_back(entry->d_name);
        nodeVector.push_back(entry->d_name);
    }

    // string nextNode(){
    //     entry = readdir(dir);
    //     while( string(entry->d_name).compare(".") || string(entry->d_name).compare("..") ){
    //         entry = readdir(dir);
    //     }
    //     return entry->d_name;
    // }

    // map<std::string, Node*> * getMap(){
    //     return m;
    // }

    std::vector<string> getVector(){
        return nodeVector;
    }

private:
    // map<std::string, Node*> * m;
    std::vector<string> nodeVector;

    DIR * dir;
    struct dirent * entry;
};
