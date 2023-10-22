#pragma once

#include <list>
#include "node.h"
#include "iterator.h"
#include "dfs_iterator.h"

using namespace std;

class Folder: public Node {
private:
    list<Node *> _nodes;
    time_t record_time;

protected:
    void removeChild(Node * target) override{
        _nodes.remove(target);
    }

public:
    // Folder(string path): Node(path) {}
    Folder(string path): Node(path){
        struct stat buf;
        if(!stat(path.c_str(), &buf)){
            if(!S_ISDIR(buf.st_mode)){
                // Can't work!
                // throw string("Can't create File obj to a Folder by path" + path);
                throw exception();
            }
        }
        else{
            throw exception();
        }
        record_time = buf.st_mtime;
    }

    void add(Node * node) override{
        if (node->path() != this->path() + "/" + node->name()) {
            throw string("Incorrect path of node: " + node -> path());
        }
        _nodes.push_back(node);
        node->parent(this);
    }

    Node * getChildByName(const char * name) const override{
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            if ((*it)->name() == name) {
                return *it;
            }
        }
        return nullptr;
    }

    int numberOfFiles() const override{
        int num = 0;
        if (_nodes.size() == 0) {
            return 0;
        }
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            num += (*it)->numberOfFiles();
        }
        return num;
    }

    class FolderIterator : public Iterator {
    public:
        FolderIterator(Folder* composite):_host(composite) {}
        ~FolderIterator() {}
        void first(){
            struct stat buf;
            stat(_host->path().c_str(), &buf);
            if(buf.st_mtime != _host->getRecordTime()){
                throw exception();
            }

            _current = _host->_nodes.begin();
        }
        Node * currentItem() const{
            return *_current;
        }
        void next(){
            struct stat buf;
            stat(_host->path().c_str(), &buf);
            if(buf.st_mtime != _host->getRecordTime()){
                throw exception();
            }
            
            _current++;
        }
        bool isDone() const{
            return _current == _host->_nodes.end();
        }

    private:
        Folder* const _host;
        std::list<Node *>::iterator _current;
    };

    Iterator * createIterator() override{
        return new FolderIterator(this);
    }

    Iterator * dfsIterator() override{
        return new DfsIterator(this);
    }

    Node * find(string path) override{
        if (this->path() == path) {
            return this;
        }

        size_t index = path.find(this->path());

        if (string::npos == index) {
            return nullptr;
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            Node * result = (*it)->find(path);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }

    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            std::list<string> paths = (*it)->findByName(name);
            for (auto i = paths.begin(); i != paths.end(); i++)
            {
                pathList.push_back(*i);  
            }
        }

        return pathList;
    }

    void remove(string path) override{
        Node * target = find(path);
        if (target) {
            target->parent()->removeChild(target);
        }
    }

    void accept(Visitor * v) override{
        v->visitFolder(this);
    }

    time_t getRecordTime(){
        return record_time;
    }
};