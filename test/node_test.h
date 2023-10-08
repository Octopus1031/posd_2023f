#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"

TEST(NodeSuite, Ping){
    ASSERT_TRUE(true);
}

TEST(NodeSuite, FileNameIsDPpdf){
    File file("/Users/user/books/design-pattern.pdf");
    ASSERT_EQ("design-pattern.pdf", file.name());
}

TEST(NodeSuite, FilePathIsDPpdf){
    File file("/Users/user/books/design-pattern.pdf");
    ASSERT_EQ("/Users/user/books/design-pattern.pdf", file.path());
}

TEST(NodeSuite, FolderNameIsBooks){
    Folder folder("/Users/user/books");
    ASSERT_EQ("books", folder.name());
}

TEST(NodeSuite, FolderPathIsBooks){
    Folder folder("/Users/user/books");
    ASSERT_EQ("/Users/user/books", folder.path());
}