#pragma once

#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"

class PainterMapper {
public:
    
    virtual void add(DomainObject * Painter) = 0;

    virtual Painter* find(std::string id) = 0;

    virtual void update(std::string id) = 0;

    virtual void del(std::string id) = 0;

    static PainterMapper* instance();

    virtual void cleanCache() = 0;

protected:

    static int callback(void* notUsed, int argc, char** argv, char** colNames);

    virtual std::string addStmt(DomainObject * domainObject) const = 0;
    virtual std::string findByIdStmt(std::string id) const = 0;
    virtual std::string updateStmt(DomainObject * domainObject) const = 0;
    virtual std::string deleteByIdStmt(std::string id) const = 0;
    
private:
    static PainterMapper* _instance;
};