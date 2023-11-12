#pragma once 

#include <list>
#include <sys/stat.h>
#include <algorithm>
#include <typeinfo>

#include "node.h"
#include "iterator.h"
#include "order_by.h"

using namespace std;

class Folder: public Node {
private:
    list<Node *> _nodes;
    int _operationCount = 0;

protected:
    void removeChild(Node * target) override {
        _nodes.remove(target);
        _operationCount++;
    }

public:
    Folder(string path): Node(path) {
        struct stat fileInfo;
        const char *c = path.c_str();
        if(lstat(c, &fileInfo) == 0){
            if(S_ISDIR(fileInfo.st_mode))
                return;
        }
        throw "No Folder exists";
    }

    void add(Node * node) override {
        if (node->path() != this->path() + "/" + node->name()) {
            throw string("Incorrect path of node: " + node -> path());
        }
        _nodes.push_back(node);
        node->parent(this);
        _operationCount++;
    }

    Node * getChildByName(const char * name) const override {
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            if ((*it)->name() == name) {
                return *it;
            }
        }

        return nullptr;
    }

    int numberOfFiles() const override {
        int num = 0;
        if (_nodes.size() == 0) {
            return 0;
        }
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            num += (*it)->numberOfFiles();
        }
        return num;
    }

    Iterator * createIterator() override {
        return new FolderIterator(this, _operationCount);
    }

    Node * find(string path) override {
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

    void remove(string path) override {
        Node * target = find(path);
        if (target) {
            target->parent()->removeChild(target);
        }
    }

    void accept(Visitor * visitor) override {
        visitor->visitFolder(this);
    }

    class FolderIterator : public Iterator {
    public:
        FolderIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {}

        ~FolderIterator() {}

        void first() {
            checkAvailable();
            _current = _host->_nodes.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _host->_nodes.end();
        }

        bool lastOne() const{
            return *_current == _host->_nodes.back();
        }

    private:
        Folder* const _host;
        std::list<Node *>::iterator _current;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }
    };

    Iterator * createIterator(OrderBy orderBy) override{
        if(orderBy == OrderBy::Normal)
            return new FolderIterator(this, _operationCount);
        else if(orderBy == OrderBy::Name){
            return new OrderByNameIterator(this, _operationCount);
        }
        else if(orderBy == OrderBy::NameWithFolderFirst){
            return new OrderByNameWithFolderFirstIterator(this, _operationCount);
        }
        else if(orderBy == OrderBy::Kind){
            return new OrderByKindIterator(this, _operationCount);
        }
        else{
            throw string("order by error");
        }
    }

    class OrderByNameIterator: public Iterator {
    public:
        OrderByNameIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {
            sortByName();
        }

        ~OrderByNameIterator() {}

        void first() {
            checkAvailable();
            _current = _sortedNodes.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _sortedNodes.end();
        }

        bool lastOne() const{
            return *_current == _sortedNodes.back();
        }

    private:
        Folder* const _host;
        std::list<Node *>::iterator _current;
        int _operationCount;
        std::list<Node *> _sortedNodes;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }

        void sortByName() {
            for(auto i:_host->_nodes){
                _sortedNodes.push_back(i);
            }
            _sortedNodes.sort(cmp);
        }
        static bool cmp(Node * n1, Node * n2){
            return n1->name() < n2->name();
        }
    };

    class OrderByNameWithFolderFirstIterator: public Iterator {
        public:
        OrderByNameWithFolderFirstIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {
            sortByNameWithFolderFirst();
        }

        ~OrderByNameWithFolderFirstIterator() {}

        void first() {
            checkAvailable();
            _current = _sortedNodes.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _sortedNodes.end();
        }

        bool lastOne() const{
            return *_current == _sortedNodes.back();
        }

    private:
        Folder* const _host;
        std::list<Node *>::iterator _current;
        int _operationCount;
        std::list<Node *> _sortedNodes;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }

        void sortByNameWithFolderFirst() {
            for(auto i:_host->_nodes){
                _sortedNodes.push_back(i);
            }
            _sortedNodes.sort(cmp);
        }
        static bool cmp(Node * n1, Node * n2){
            Folder* f1 = dynamic_cast<Folder*>(n1);
            Folder* f2 = dynamic_cast<Folder*>(n2);
            if((f1!=0) ^ (f2!=0)){ // 種類不同
                if(f1){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return n1->name() < n2->name();
            }

        }
    };

    class OrderByKindIterator: public Iterator {
    public:
        OrderByKindIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {
            sortByKindWithFolderFirst();
        }

        ~OrderByKindIterator() {}

        void first() {
            checkAvailable();
            _current = _sortedNodes.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _sortedNodes.end();
        }

        bool lastOne() const{
            return *_current == _sortedNodes.back();
        }

    private:
        Folder* const _host;
        std::list<Node *>::iterator _current;
        int _operationCount;
        std::list<Node *> _sortedNodes;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }

        void sortByKindWithFolderFirst() {
            for(auto i:_host->_nodes){
                _sortedNodes.push_back(i);
            }
            _sortedNodes.sort(cmp);
        }
        static bool cmp(Node * n1, Node * n2){
            Folder* f1 = dynamic_cast<Folder*>(n1);
            Folder* f2 = dynamic_cast<Folder*>(n2);
            if((f1!=0) && (f2!=0)){ // both folder
                    return n1->name() < n2->name();
            }
            else if((f1==0) && (f2==0)){ //both file
                bool b1 = n1->name().find(".")!=string::npos && n2->name().find(".")!=string::npos;
                bool b2 = n1->name().find(".")==string::npos && n2->name().find(".")==string::npos;
                //both have filename extension
                if( b1 || b2 ){
                    // return n1->name() < n2->name();
                    return true;
                }
                //only one have filename extension
                else{
                    if( n1->name().find(".")==string::npos ){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
            }
            else{ // type different
                if( f1!=0 ){ // n1 is folder, n2 is file
                    bool b = n2->name().find(".")!=string::npos;
                    if(b)
                        return true;
                    else
                        return false;
                }
                else{ // n1 is file, n2 is folder
                    bool b = n1->name().find(".")==string::npos;
                    if(b)
                        return true;
                    else
                        return false;
                }
            }
        }
    };
};
