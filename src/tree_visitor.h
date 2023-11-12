#pragma once

#include "visitor.h"
#include "order_by.h"
#include "folder.h"
#include "iterator.h"

#include <vector>
#include <string>

class TreeVisitor: public Visitor {
public:
    TreeVisitor(OrderBy orderBy): _orderBy(orderBy){
        layer = -1;
    }

    void visitFile(File * file){
        tree+= file->name() + "\n";
    }

    void visitFolder(Folder * folder){
        if(layer>-1){
            tree+= folder->name()+"\n";
        }
        else{
            tree+= ".\n";
        }

        ++layer;
        lastOne.push_back(false);
        
        Iterator* it = folder->createIterator(_orderBy);
        for(it->first(); !it->isDone(); it->next()){
            for(int i=0; i<layer; i++){
                if( !lastOne.at(i) )
                    tree+="│   ";
                else
                    tree+="    ";
            }
            if( !it->lastOne() ){
                tree+= "├── ";
            }
            else{
                tree+= "└── ";
                lastOne.at(layer) = true;
            }
            it->currentItem()->accept(this);
        }
        --layer;
    }

    string getTree(){
        return tree;
    }

private:
    OrderBy _orderBy;
    std::string tree;
    int layer;
    vector<bool> lastOne;
};