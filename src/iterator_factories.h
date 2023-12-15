#pragma once

#include "iterator_factory.h"
#incldue "folder.h"

class FolderIteratorFactory: public IteratorFactory {
public:
    FolderIteratorFactory(){

    }

    FolderIterator* create(Folder * node, int operationCount) override{
        if(node->_operationCount != operationCount){
            throw "FolderIteratorFactory create fail";
        }
        return new FolderIterator(node);
    }
};

class OrderByNameIteratorFactory: public IteratorFactory {
public:
    OrderByNameIteratorFactory(){

    }

    OrderByNameIterator* create(Folder * node, int operationCount) override{
        if(node->_operationCount != operationCount){
            throw "OrderByNameIteratorFactory create fail";
        }
        return new OrderByNameIterator(node);
    }
};

class OrderByNameWithFolderFirstIteratorFactory: public IteratorFactory {
public:
    OrderByNameWithFolderFirstIteratorFactory(){

    }

    OrderByNameWithFolderFirstIterator* create(Folder* node, int operationCount) override{
        if(node->_operationCount != operationCount){
            throw "OrderByNameWithFolderFirstIteratorFactory create fail";
        }
        return new OrderByNameWithFolderFirstIterator(node);
    }
};

class OrderByKindIteratorFactory: public IteratorFactory {
public:
    OrderByKindIteratorFactory(){

    }

    OrderByKindIterator* create(Folder* node, int operationCount) override{
        if(node->_operationCount != operationCount){
            throw "OrderByKindIteratorFactory create fail";
        }
        return new OrderByKindIterator(node);
    }
};
