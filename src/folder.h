#if !defined(FOLDER)
#define FOLDER

#include <string>
#include <vector>

// #include "./node.h"

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

private: 
    string _path;
    vector<Node *> _child;
};


#endif // FOLDER
