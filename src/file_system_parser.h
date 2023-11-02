#pragma once

#include <string>

#include "folder.h"
#include "file_system_builder.h"
#include "file_system_scanner.h"

using std::string;

class FileSystemParser {
public:
    FileSystemParser(FileSystemBuilder * builder): _builder(builder){
        _scanner = new FileSystemScanner();
    }

    Folder * getRoot() const{
        return _builder->getRoot();
    }

    void parse(){
        _scanner->nextNode();
        while( !_scanner->isDone() ){
            if( _scanner->isFile() ){
                _builder->buildFile(_path + "/" + _scanner->currentNodeName());
            }

            // else if( _scanner->isFolder() ){
            //     _builder->buildFolder(_path + "/" + _scanner->currentNodeName());
            //     FileSystemParser* parser = new FileSystemParser( new FileSystemBuilder() );
            //     parser->setPath(_path + "/"  + _scanner->currentNodeName());
            //     parser->parse();
            //     // _builder->endFolder();
            // }
            _scanner->nextNode();
        }  
    }

    void setPath(string path){
        _path = path;
        _scanner->setPath(_path);
        _builder->setPath(_path);
    }

private:
    string _path;
    FileSystemBuilder * _builder;
    FileSystemScanner * _scanner;
};
