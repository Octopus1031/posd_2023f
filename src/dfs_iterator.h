#if !defined(DFS_ITERATOR_H)
#define DFS_ITERATOR_H

#include "iterator.h"
#include "./node.h"

class DfsIterator: public Iterator {
public:
    DfsIterator(Node* composite): _composite(composite) {}

    void first(){
        //TODO
        return;
    }

    Node * currentItem() const{
        //TODO
        return *_it;
    }

    void next(){
        //TODO
        _it++;
    }
    
    bool isDone() const{
        //TODO
        return false;
    }

private:
    Node * _composite;
    std::vector<Node *>::iterator _it;
};

class BfsIterator: public Iterator {
public:
    BfsIterator(Node* composite): _composite(composite) {}
    void first(){
        //TODO
        return;
    }

    Node * currentItem() const{
        //TODO
        return *_it;
    }

    void next(){
        //TODO
        _it++;
    }
    
    bool isDone() const{
        //TODO
        return false;
    }

private:
    Node * _composite;
    std::vector<Node *>::iterator _it;
};

#endif // DFS_ITERATOR_H
