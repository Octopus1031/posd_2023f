#if !defined(ITERATOR_H)
#define ITERATOR_H

#pragma once 

#include<list>
#include <vector>

class Node;
class Folder;

class Iterator {
public:
    ~Iterator();
    virtual void first() = 0;
    virtual Node * currentItem() const = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
};

class FolderIterator : public Iterator {
public:
    FolderIterator(Folder * composite);
    void first();
    Node * currentItem() const;
    void next();
    bool isDone() const;

private:
    Folder * _composite;
    std::vector<Node *>::iterator _it;
};


#endif // ITERATOR_H
