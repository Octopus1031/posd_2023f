#if !defined(FOLDER)
#define FOLDER

#include <string>
#include <vector>

#include "iterator.h"
// #include "foldIterator.h"

using namespace std;

class Folder: public Node {
    friend class FolderIterator;
public:
    Folder(string path):_path(path) {
        
    }
    string name() const override{
        std::vector<string> v = split(path(), "/");
        return v.back();
    };

    string path() const override{
        return _path;
    }

    void add(Node * node) override {
        if(!node->getFolder().compare(this->name())){
            _child.push_back(node);
        }
    }

    void remove(string path) override {
        std::vector<Node *>::iterator it = _child.begin();
        while(it!=_child.end()){
            if(!path.compare((*it)->path())){
                _child.erase(it);
                break;
            }
            it++;
        }
        
    }

    Node * getChildByName(const char * name) const override {
        for(auto c:_child){
            if(!c->name().compare(name)){
                return c;
            }
        }
        return nullptr;
    }

    Node * find(string path) override {
        for(auto c:_child){
            if(!c->path().compare(path)){
                return c;
            }
        }
        return nullptr;
    }

    int numberOfFiles() const override{
        int p = 0;
        for(auto c: _child){
            p += c->numberOfFiles();
        }
        return p;
    }

    //new add
    string getFolder() const override{
        std::vector<string> v = split(_path, "/");
        v.pop_back();
        return v.back();
    }

    FolderIterator * createIterator() override {
        return new FolderIterator(this);
    }

private: 
    string _path;
    std::vector<Node *> _child;
};


#endif // FOLDER
