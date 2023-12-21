#include "drawing_mapper.h"

#include <sqlite3.h>
#include <string>
#include <map>
#include "drawing.h"
#include "triangle.h"
#include "parser.h"
#include "scanner.h"
#include "builder.h"
#include "domain_object.h"
#include "sqlite_drawing_mapper.h"

DrawingMapper* DrawingMapper::_instance = nullptr;

DrawingMapper* DrawingMapper::instance() {
    if(_instance == nullptr) {
        _instance = SQLiteDrawingMapper::instance();
    }
    return _instance;
}
