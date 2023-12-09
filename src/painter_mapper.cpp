#include "painter_mapper.h"
#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"
#include "abstract_mapper.h"

PainterMapper* PainterMapper::_instance = nullptr;
PainterMapper::PainterMapper() {

}

PainterMapper* PainterMapper::instance(){
    if(_instance==nullptr){
        _instance = new PainterMapper();
    }
    return _instance;
}

int PainterMapper::callback(void *notUsed, int argc, char **argv, char **colNames){
    Painter* painter = new Painter(argv[0], argv[1]);
    PainterMapper::instance()->load(painter);
    return 0;
}

// TODO
Painter* PainterMapper::find(std::string id){
    return static_cast<Painter*>(abstractFind(id, PainterMapper::callback));
    // return nullptr;
}

void PainterMapper::add(DomainObject * painter){
    abstractAdd(painter);
}

void PainterMapper::update(std::string id){
    abstractUpdate(_domainObjects.at(id));
}

void PainterMapper::del(std::string id){
    abstractDelete(id);
}

std::string PainterMapper::findByIdStmt(std::string id) const
{
    std::string stmt = "SELECT * FROM painter WHERE ID = '" + id + "'";
    return stmt;
}

std::string PainterMapper::updateStmt(DomainObject* domainObject) const{
    Painter* painter = static_cast<Painter*>(domainObject);
    std::string stmt = "UPDATE painter SET name='" + painter->name() + "' WHERE ID='" + painter->id() + "'";
    return stmt;
}

std::string PainterMapper::addStmt(DomainObject *domainObject) const{
    Painter* painter = static_cast<Painter*>(domainObject);
    std::string stmt = "INSERT INTO painter VALUES (" + painter->id() + ", " + painter->name() + ")";
    return stmt;
}

std::string PainterMapper::deleteByIdStmt(std::string id) const{
    std::string stmt = "DELETE FROM painter WHERE ID='" + id + "'";
    return stmt;
}