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
        _child.push_back(node);
        // if(node.path.compare())
    }

    Node * getChildByName(const char * name) const {
        for(auto c:_child){
            if(!c->name().compare(name)){
                return c;
            }
        }
        return NULL;
    }

private: 
    string _path;
    vector<Node *> _child;
};


#endif // FOLDER
