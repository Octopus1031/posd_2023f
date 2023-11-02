#include "../src/json_object.h"
#include "../src/string_value.h"
#include "../src/json_iterator.h"
#include "../src/beautify_visitor.h"

#include <string>

TEST(JSonSuite, OneKeyStringValue) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    ASSERT_EQ(v1, jo->getValue("key1"));
    ASSERT_EQ("{\n\"key1\":\"value1\"\n}", jo->toString());

}

TEST(JSonSuite, TwoKeyStringValue) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);
    ASSERT_EQ("\"value1\"", jo->getValue("key1")->toString());
    ASSERT_EQ("\"value2\"", jo->getValue("key2")->toString());
    ASSERT_EQ("{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}", jo->toString());

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
    ASSERT_EQ("{\n\"keyc\":{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}\n}", j_composite->toString());
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

// TEST(JSonSuite, beautifyVisitorJsonObject){
//     JsonObject *jo = new JsonObject;
//     Value * v1 = new StringValue("value1");
//     jo->set("key1", v1);
//     Value * v2 = new StringValue("value2");
//     jo->set("key2", v2);
//     JsonObject *j_composite = new JsonObject;
//     j_composite->set("keyc", jo);

//     BeautifyVisitor * visitor = new BeautifyVisitor();
//     j_composite->accept(visitor);
    
//     std::string s = "{\n    \"keyc\": {\n        \"key1\": \"value1\",\n        \"key2\": \"value2\"\n    }\n}";
//     ASSERT_EQ(s, visitor->getResult());
// }

// {\n    \"keyc\": {\n        \"key1\": \"value1\",\n        \"key2\": \"value2\"\n    }\n}