#pragma once

#include "node.h"
#include "folder.h"

// A Proxy to other Nodes
class Link : public Node{
private:
    Node* node;

public:
    // Link(std::string path) : Node(path) {
    //     struct stat fileInfo;
    //     const char *c = path.c_str();
    //     if(lstat(c, &fileInfo) == 0){
    //         if(S_ISDIR(fileInfo.st_mode))
    //             node = new Folder(path);
    //         else
    //             node = new File(path);
    //     }
    //     throw "No Folder exists";
    // }

    Link(Node * node) : Node(node->path()){
        this->node = node;
    }

    int numberOfFiles() const {
        // TODO:
        return 0;
    }

    Node * find(std::string path) {
        // TODO:
        return nullptr;
    }

    std::list<std::string> findByName(std::string name) {
        // TODO:
        std::list<std::string> l;
        return  l;
    }

    void add(Node * node){
        // TODO:
    }

    void remove(string path){
        // TODO:
    }

    Node * getChildByName(const char * name) const {
        // TODO:
        return nullptr;
    }

    // returns a pointer to the target node.
    Node * getTarget() {
        return node;
    }

    void accept(Visitor * visitor) {
        // TODO:
    }

};

// int numberOfFiles()
// Node * find(string path)
// std::list<string> findByName(string name)
// void add(Node * node)
// void remove(string path)
// Node * getChildByName(const char * name)