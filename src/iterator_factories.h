#pragma once

#include "iterator_factory.h"
#include "folder.h"

class FolderIteratorFactory: public IteratorFactory {
public:
    FolderIteratorFactory(){

    }

    Folder::FolderIterator* create(Folder * node, int operationCount) override{
        return new Folder::FolderIterator(node, operationCount);
    }
};

class OrderByNameIteratorFactory: public IteratorFactory {
public:
    OrderByNameIteratorFactory(){

    }

    Folder::OrderByNameIterator* create(Folder * node, int operationCount) override{
        return new Folder::OrderByNameIterator(node, operationCount);
    }
};

class OrderByNameWithFolderFirstIteratorFactory: public IteratorFactory {
public:
    OrderByNameWithFolderFirstIteratorFactory(){

    }

    Folder::OrderByNameWithFolderFirstIterator* create(Folder* node, int operationCount) override{
        return new Folder::OrderByNameWithFolderFirstIterator(node, operationCount);
    }
};

class OrderByKindIteratorFactory: public IteratorFactory {
public:
    OrderByKindIteratorFactory(){

    }

    Folder::OrderByKindIterator* create(Folder* node, int operationCount) override{
        return new Folder::OrderByKindIterator(node, operationCount);
    }
};
