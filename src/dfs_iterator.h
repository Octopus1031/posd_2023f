#if !defined(DFS_ITERATOR_H)
#define DFS_ITERATOR_H

class Node;
#include "iterator.h"

class DfsIterator: public Iterator {
public:
    DfsIterator(Node* composite);

    void first();

    Node * currentItem() const;

    void next();
    
    bool isDone() const;

private:
    Node * _composite;
    std::vector<Node *>::iterator _it;
};

class BfsIterator: public Iterator {
public:
    BfsIterator(Node* composite);
    void first();
    Node * currentItem() const;
    void next();
    bool isDone() const;

private:
    Node * _composite;
    std::vector<Node *>::iterator _it;
};

#endif // DFS_ITERATOR_H
