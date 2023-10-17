#pragma once 

#include<string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "iterator.h"
#include "null_iterator.h"

using namespace std;

class Node {
private:
    string _path;
    Node * _parent;
protected:

    Node(string path): _path(path) {}
    // Node(string path){
    //     struct stat buf;
    //     stat(path.c_str(), &buf);
    //     if(S_ISDIR(buf.st_mode)){

    //     }
    // }

public:
    virtual ~Node() {}

    Node * parent() {
        return _parent;
    }

    void parent(Node * parent) {
        _parent = parent;
    }
    
    virtual void removeChild(Node * target) {
        throw string("This node does not support removing sub node");
    }

    string name() const {
        size_t slash = _path.rfind("/");
        return _path.substr(slash+1);
    }
    
    string path() const {
        return _path;
    }
    
    virtual void add(Node * node) {
        throw string("This node does not support adding sub node");
    }

    virtual Node * getChildByName(const char * name) const {
        return nullptr;
    }

    virtual int numberOfFiles() const = 0;

    virtual Iterator * createIterator() {
        return new NullIterator();
    }

    virtual Iterator * dfsIterator() {
        return new NullIterator();
    }

    virtual Node * find(string path) = 0;

    virtual void remove(string path) {
        throw string("This node does not support deleting sub node");
    }
};