#include "./dfs_iterator.h"
#include "./node.h"
// #include "./folder.h"

DfsIterator::DfsIterator(Node * composite): _composite(composite) {}

void DfsIterator::first(){
    //TODO
    return;
}

Node * DfsIterator::currentItem() const{
    //TODO
    return *_it;
}

void DfsIterator::next(){
    //TODO
    _it++;
}

bool DfsIterator::isDone() const{
    //TODO
    return false;
}

BfsIterator::BfsIterator(Node * composite): _composite(composite) {}

void BfsIterator::first(){
    //TODO
    return;
}

Node * BfsIterator::currentItem() const{
    //TODO
    return *_it;
}

void BfsIterator::next(){
    //TODO
    _it++;
}

bool BfsIterator::isDone() const{
    //TODO
    return false;
}