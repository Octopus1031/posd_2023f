#include "../src/json_object.h"
#include "../src/string_value.h"
#include "../src/json_iterator.h"
#include "../src/beautify_visitor.h"
#include "../src/json_parser.h"
#include "../src/json_scanner.h"
#include "../src/json_builder.h"

#include <string>
#include <iostream>

TEST(JSonSuite, OneKeyStringValue) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    ASSERT_EQ(v1, jo->getValue("key1"));
    std::string expect ="{\n"\
                            "\"key1\":\"value1\"\n"\
                        "}";
    ASSERT_EQ(expect, jo->toString());

}

TEST(JSonSuite, TwoKeyStringValue) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);
    std::string expect ="{\n"\
                            "\"key1\":\"value1\",\n"\
                            "\"key2\":\"value2\"\n"\
                        "}";
    ASSERT_EQ("\"value1\"", jo->getValue("key1")->toString());
    ASSERT_EQ("\"value2\"", jo->getValue("key2")->toString());
    ASSERT_EQ(expect, jo->toString());

}

TEST(JSonSuite, Composite) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);

    JsonObject *j_composite = new JsonObject;
    j_composite->set("keyc", jo);
    ASSERT_EQ(jo, j_composite->getValue("keyc"));
    std::string expect ="{\n"\
                            "\"keyc\":{\n"\
                                "\"key1\":\"value1\",\n"\
                                "\"key2\":\"value2\"\n"\
                            "}\n"\
                        "}";
    ASSERT_EQ(expect, j_composite->toString());
}

TEST(JSonSuite, nullIterator){
    Value * v1 = new StringValue("value1");
    JsonIterator * it = v1->createIterator();

    ASSERT_TRUE(it->isDone());

    ASSERT_ANY_THROW(it->currentKey());
    ASSERT_ANY_THROW(it->currentValue());
}

TEST(JSonSuite, jsonObjectIterator){
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);
    JsonObject *j_composite = new JsonObject;
    j_composite->set("keyc", jo);

    JsonIterator * itc = j_composite->createIterator();
    itc->first();
    ASSERT_EQ("keyc", itc->currentKey());

    JsonIterator * it1 = itc->currentValue()->createIterator();
    it1->first();
    ASSERT_EQ("key1", it1->currentKey());
    ASSERT_EQ("\"value1\"", it1->currentValue()->toString());

    it1->next();
    ASSERT_EQ("key2", it1->currentKey());
    ASSERT_EQ("\"value2\"", it1->currentValue()->toString());

    itc->next();
    ASSERT_TRUE(itc->isDone());
}

TEST(JSonSuite, beautifyVisitorStringValue){
    Value * v1 = new StringValue("value1");

    BeautifyVisitor * visitor = new BeautifyVisitor();
    v1->accept(visitor);
    
    std::string s = "\"value1\"";
    ASSERT_EQ(s, visitor->getResult());
}

TEST(JSonSuite, beautifyVisitorJsonObject){
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);
    JsonObject *j_composite = new JsonObject;
    j_composite->set("keyc", jo);

    BeautifyVisitor * visitor = new BeautifyVisitor();
    j_composite->accept(visitor);
    
    std::string s = "{\n    \"keyc\": {\n        \"key1\": \"value1\",\n        \"key2\": \"value2\"\n    }\n}";
    ASSERT_EQ(s, visitor->getResult());
}

TEST(JSonSuite, beautifyVisitorJsonObjectEx2){
    JsonObject *jo1 = new JsonObject;
    Value * v1 = new StringValue("Robert C. Martin");
    jo1->set("author", v1);
    Value * v2 = new StringValue("Clean Code");
    jo1->set("name", v2);

    JsonObject *jo2 = new JsonObject;
    Value * v3 = new StringValue("Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides");
    jo2->set("author", v3);
    Value * v4 = new StringValue("Design Patterns Elements of Reusable Object-Oriented Software");
    jo2->set("name", v4);

    JsonObject *jo3 = new JsonObject;
    jo3->set("clean code", jo1);
    jo3->set("design pattern", jo2);

    JsonObject *j_composite = new JsonObject;
    j_composite->set("books", jo3);

    BeautifyVisitor * visitor = new BeautifyVisitor();
    j_composite->accept(visitor);
    
    // std::cout << visitor->getResult() << std::endl;
    std::string s = "{\n    \"books\": {\n        \"clean code\": {\n            \"author\": \"Robert C. Martin\",\n            \"name\": \"Clean Code\"\n        },\n        \"design pattern\": {\n            \"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides\",\n            \"name\": \"Design Patterns Elements of Reusable Object-Oriented Software\"\n        }\n    }\n}";
    ASSERT_EQ(s, visitor->getResult());
}

TEST(JSonSuite, parser){
    JsonParser * parser = new JsonParser(new JsonScanner(), new JsonBuilder());
    std::string input = "{\n    \"books\": {\n        \"clean code\": {\n            \"author\": \"Robert C. Martin\",\n            \"name\": \"Clean Code\"\n        },\n        \"design pattern\": {\n            \"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides\",\n            \"name\": \"Design Patterns Elements of Reusable Object-Oriented Software\"\n        }\n    }\n}";
    parser->setInput(input);
    // std::cout << "hello" << std::endl;
    parser->parse();
    JsonObject * jo = parser->getJsonObject();
    BeautifyVisitor * visitor = new BeautifyVisitor();
    jo->accept(visitor);
    // std::cout << visitor->getResult() << std::endl;
    ASSERT_EQ(input, visitor->getResult());
}