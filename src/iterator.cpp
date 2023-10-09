#include "./foldIterater.h"
#include "./iterator.h"
#include "./node.h"
#include "./folder.h"

Iterator::Iterator(Folder * composite): _composite(composite) {}

void first(){
    _it = _composite->_composite.begin();
}

Node * currentItem() const{
    return *_it;
}

void next(){
    _it++;
}

bool isDone() const{
    return _it == _composite->composite.end();
}