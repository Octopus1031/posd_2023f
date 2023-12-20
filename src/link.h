#pragma once

#include "node.h"
#include "file.h"
#include "folder.h"

// A Proxy to other Nodes
class Link : public Node{
private:
    Node* _node;

public:
    Link(std::string path, Node * node) : Node(path), _node(node) { }

    int numberOfFiles() const {
        return _node->numberOfFiles();
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
        _node->add(node);
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
        return _node;
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