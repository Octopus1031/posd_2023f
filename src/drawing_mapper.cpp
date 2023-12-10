#include "drawing_mapper.h"

#include <sqlite3.h>
#include <string>
#include <map>
#include "drawing.h"
#include "parser.h"
#include "scanner.h"
#include "builder.h"
#include "painter_mapper.h"

DrawingMapper *DrawingMapper::_instance = nullptr;

DrawingMapper *DrawingMapper::instance()
{
    if (_instance == nullptr)
    {
        _instance = new DrawingMapper();
    }
    return _instance;
}

DrawingMapper::DrawingMapper()
{
    _builder = new Builder();
    _scanner = new Scanner();
    _parser = new Parser(_scanner, _builder);
}

std::list<Shape *> DrawingMapper::convertShapes(int argc, char **argv)
{
    _parser->clear();
    _parser->setInput(argv[2]);
    _parser->parse();
    return _parser->getShapes();
}

int DrawingMapper::callback(void* notUsed, int argc, char** argv, char** colNames) {
    Painter * painter = PainterMapper::instance()->find(argv[1]);
    Parser * parser = new Parser(new Scanner(), new Builder());
    parser->setInput(argv[2]);
    parser->parse();
    std::list<Shape *> shapes = parser->getShapes();
    Drawing* drawing = new Drawing(argv[0], painter, shapes);
    DrawingMapper::instance()->load(drawing);
    return 0;
}

Drawing *DrawingMapper::find(std::string id){
    return static_cast<Drawing*>(abstractFind(id, DrawingMapper::callback));
}

void DrawingMapper::add(DomainObject *drawing){
    abstractAdd(drawing);
}

    // update
void DrawingMapper::update(std::string id){
    abstractUpdate(_domainObjects.at(id));
}

// delete
void DrawingMapper::del(std::string id){
    abstractDelete(id);
}

std::string DrawingMapper::findByIdStmt(std::string id) const{
    std::string stmt = "SELECT * FROM drawing WHERE ID='" + id + "'";
    return stmt;
}

std::string DrawingMapper::updateStmt(DomainObject* domainObject) const{
    Drawing* drawing = static_cast<Drawing*>(domainObject);
    std::string stmt = "UPDATE drawing SET Painter='" + drawing->painter()->id() + "' WHERE ID='" + drawing->id() + "'";
    return stmt;
}

std::string DrawingMapper::addStmt(DomainObject *domainObject) const{
    Drawing* drawing = static_cast<Drawing*>(domainObject);
    std::string stmt = "INSERT INTO drawing VALUES ('" + drawing->id() + "', '" + drawing->painter()->id() + "', '" + drawing->getShapesAsString() + "')";
    return stmt;
}

std::string DrawingMapper::deleteByIdStmt(std::string id) const{
    std::string stmt = "DELETE FROM drawing WHERE ID='" + id + "'";
    return stmt;
}
