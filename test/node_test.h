#include "../src/node.h"
#include "../src/file.h"

TEST(NodeSuite, Ping){
    ASSERT_TRUE(true);
}

TEST(NodeSuite, NameIsDPpdf){
    File f("/Users/user/books/design-pattern.pdf");
    ASSERT_EQ("design-pattern.pdf", f.name());
}

TEST(NodeSuite, PathIsDPpdf){
    File f("/Users/user/books/design-pattern.pdf");
    ASSERT_EQ("/Users/user/books/design-pattern.pdf", f.path());
}