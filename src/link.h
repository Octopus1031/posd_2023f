#pragma once

#include <list>

#include "node.h"
#include "file.h"
#include "folder.h"

class Link : public Node{
private:
    Node* _node;

public:
    Link(std::string path, Node * node) : Node(path), _node(node) { }

    int numberOfFiles() const {
        return _node->numberOfFiles();
    }

    Node * find(std::string path) {
        return _node->find(path);
    }

    std::list<std::string> findByName(std::string name) {
        return _node->findByName(name);
    }

    void add(Node * node){
        _node->add(node);
    }

    void remove(string path){
        _node->remove(path);
    }

    Node * getChildByName(const char * name) const {
        return _node->getChildByName(name);
    }

    Node * getTarget() {
        return _node;
    }

    void accept(Visitor * visitor) {
        visitor->visitLink(this);
    }

};