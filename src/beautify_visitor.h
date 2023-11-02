#pragma once

class BeautifyVisitor : public JsonVisitor {
public:
    BeautifyVisitor(){
        result = "";
    }
    void visitJsonObject(JsonObject * obj){

    }

    void visitStringValue(StringValue * val){
        result+=val->toString();
    }

    std::string getResult() const{
        return result;
    }

private:
    std::string result;
};