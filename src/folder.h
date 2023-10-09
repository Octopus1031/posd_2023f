#if !defined(FOLDER)
#define FOLDER

#include <string>
#include <vector>

#include "iterator.h"

using namespace std;

class Folder: public Node {
public:
    Folder(string path):_path(path) {
        
    }
    string name() const override{
        vector<string> v = split(path(), "/");
        return v.back();
    };

    string path() const override{
        return _path;
    }

    void add(Node * node) {
        if(!node->getFolder().compare(this->name())){
            _child.push_back(node);
        }
    }

    void remove(string path){
        vector<Node *>::iterator it = _child.begin();
        while(it!=_child.end()){
            if(!path.compare((*it)->path())){
                _child.erase(it);
                break;
            }
            it++;
        }
        
    }

    Node * getChildByName(const char * name) const {
        for(auto c:_child){
            if(!c->name().compare(name)){
                return c;
            }
        }
        return nullptr;
    }

    //new add
    string getFolder() const override{
        vector<string> v = split(_path, "/");
        v.pop_back();
        return v.back();
    }

    // FolderIterator * createIterator(){
    //     return new FolderIterator(this);
    // }    

private: 
    string _path;
    vector<Node *> _child;
};


#endif // FOLDER
