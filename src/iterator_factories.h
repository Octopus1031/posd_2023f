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

    static OrderByNameIteratorFactory* instance(){
        if(_instance==nullptr){
            _instance = new OrderByNameIteratorFactory();
        }
        return _instance;
    }

    Folder::OrderByNameIterator* create(Folder * node, int operationCount) override{
        return new Folder::OrderByNameIterator(node, operationCount);
    }

protected:
    OrderByNameIteratorFactory(){
        
    }

private:
    static OrderByNameIteratorFactory* _instance;
    
};

class OrderByNameWithFolderFirstIteratorFactory: public IteratorFactory {
public:
    static OrderByNameWithFolderFirstIteratorFactory* instance(){
        if(_instance==nullptr){
            _instance = new OrderByNameWithFolderFirstIteratorFactory();
        }
        return _instance;
    }

    Folder::OrderByNameWithFolderFirstIterator* create(Folder* node, int operationCount) override{
        return new Folder::OrderByNameWithFolderFirstIterator(node, operationCount);
    }

protected:
    OrderByNameWithFolderFirstIteratorFactory(){

    }

private:
    static OrderByNameWithFolderFirstIteratorFactory* _instance;
};

class OrderByKindIteratorFactory: public IteratorFactory {
public:
    static OrderByKindIteratorFactory* instance(){
        if(_instance==nullptr){
            _instance = new OrderByKindIteratorFactory();
        }
        return _instance;
    }

    Folder::OrderByKindIterator* create(Folder* node, int operationCount) override{
        return new Folder::OrderByKindIterator(node, operationCount);
    }

protected:
    OrderByKindIteratorFactory(){

    }

private:
    static OrderByKindIteratorFactory* _instance;
};

OrderByNameIteratorFactory* OrderByNameIteratorFactory::_instance = nullptr;
OrderByNameWithFolderFirstIteratorFactory* OrderByNameWithFolderFirstIteratorFactory::_instance = nullptr;
OrderByKindIteratorFactory* OrderByKindIteratorFactory::_instance = nullptr;