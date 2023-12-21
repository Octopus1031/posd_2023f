#include "painter_mapper.h"
#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"
#include "sqlite_painter_mapper.h"

PainterMapper* PainterMapper::_instance = nullptr;


PainterMapper* PainterMapper::instance() {
    if(_instance == nullptr) {
        _instance = SQLitePainterMapper::instance();
    }
    return _instance;
}

void PainterMapper::cleanCache() {
    SQLitePainterMapper::instance()->cleanCache();
}