#include "unit_of_work.h"
#include "drawing_mapper.h"
#include "painter_mapper.h"
#include "domain_object.h"
#include <list>
#include <iostream>


UnitOfWork * UnitOfWork::_instance = nullptr;

UnitOfWork::UnitOfWork() { }

UnitOfWork * UnitOfWork::instance(){
    if(_instance == nullptr){
        _instance = new UnitOfWork();
    }
    return _instance;
}

void UnitOfWork::registerNew(DomainObject * domainObject){
    _new[domainObject->id()] = domainObject;
}

void UnitOfWork::registerClean(DomainObject * domainObject){
    _clean[domainObject->id()] = domainObject;
}

void UnitOfWork::registerDirty(DomainObject * domainObject){
    _dirty[domainObject->id()] = domainObject;
    _clean.erase(domainObject->id());
}

void UnitOfWork::registerDeleted(DomainObject * domainObject){
    _deleted[domainObject->id()] = domainObject;
}

bool UnitOfWork::inNew(std::string id) const{
    return _new.count(id);
}

bool UnitOfWork::inClean(std::string id) const{
    return _clean.count(id);
}

bool UnitOfWork::inDirty(std::string id) const{
    return _dirty.count(id);
}

bool UnitOfWork::inDeleted(std::string id) const{
    return _deleted.count(id);
}

void UnitOfWork::commit(){
    for(auto dirty : _dirty) {
        Drawing* d = dynamic_cast<Drawing*>(dirty.second);
        Painter* p = dynamic_cast<Painter*>(dirty.second);
        if(d!=nullptr){
            std::cout << "dd id: " + d->id() <<std::endl;
            DrawingMapper::instance()->update(dirty.first);
        }
        else if(p!=nullptr){
            std::cout << "dp id: " + p->id() <<std::endl;
            PainterMapper::instance()->update(dirty.first);
        }
        else{
            throw std::string("commit dirty err");
        }
        registerClean(dirty.second);
    }
    _dirty.clear();

    std::cout << "run in newObj loop "<<std::endl;
    for(auto newObj : _new) {
        Drawing* d = dynamic_cast<Drawing*>(newObj.second);
        Painter* p = dynamic_cast<Painter*>(newObj.second);
        if(d!=nullptr){
            std::cout << "nd id: " + d->id() <<std::endl;
            DrawingMapper::instance()->add(newObj.second);
        }
        else if(p!=nullptr){
            std::cout << "np id: " + p->id() <<std::endl;
            PainterMapper::instance()->add(newObj.second);
        }
        else{
            throw std::string("commit new err");
        }
        registerClean(newObj.second);
    }
    _new.clear();
}