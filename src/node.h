#if !defined(NODE_H)
#define NODE_H

#include <string>
#include <vector>

#include "./iterator.h"

using namespace std;

class Node {
public:
    virtual string name() const = 0;
    
    virtual string path() const = 0;
    
    virtual void add(Node * node) {}

    virtual void remove(string path) {}
    
    virtual Node * getChildByName(const char * name) const {}

    virtual Node * find(string path) {}

    virtual int numberOfFiles() const = 0;

    virtual Iterator * createIterator() {}

    // new add
    vector<string> split (string str, string token) const {
        std::vector<string> v;
        while(1){
            v.push_back(str.substr(0, str.find(token)));
            str = str.substr(str.find(token)+1, str.length());
            if(str.find(token) == -1){
                v.push_back(str);
                break;
            }
        }
        return v;
    }

    virtual string getFolder() const = 0;
};


#endif // NODE_H
