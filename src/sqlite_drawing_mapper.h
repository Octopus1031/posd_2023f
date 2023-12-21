#pragma once

#include <string>

#include <sqlite3.h>

#include "drawing.h"
#include "sqlite_abstract_mapper.h"
#include "drawing_mapper.h"
#include "painter_mapper.h"
#include "scanner.h"
#include "builder.h"
#include "parser.h"

class SQLiteDrawingMapper : public SQLiteAbstractMapper, public DrawingMapper {
public:

    ~SQLiteDrawingMapper() {
        delete _parser;
    }

    void add(DomainObject * Drawing);

    Drawing* find(std::string id);

    void update(std::string id);

    void del(std::string id);

    static SQLiteDrawingMapper* instance();

    void cleanCache();

protected:
    SQLiteDrawingMapper();

    static int callback(void* notUsed, int argc, char** argv, char** colNames);

    std::list<Shape *> convertShapes(char * shape_string) override ;

    std::string addStmt(DomainObject * domainObject) const override;
    std::string findByIdStmt(std::string id) const override;
    std::string updateStmt(DomainObject * domainObject) const override;
    std::string deleteByIdStmt(std::string id) const override;

private:
    static SQLiteDrawingMapper* _instance;
    Parser * _parser;
};