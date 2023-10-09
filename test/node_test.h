#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"


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

TEST(NodeSuite, FolderAddChild){
    Folder folder("/Users/user/books");
    folder.add(new File("/Users/user/books/design-pattern.pdf"));
    ASSERT_EQ("design-pattern.pdf", folder.getChildByName("design-pattern.pdf")->name());

    Folder folder2("/Users/user/NOTbooks");
    folder2.add(new File("/Users/user/books/POSD.pdf"));
    ASSERT_EQ(nullptr, folder.getChildByName("POSD.pdf"));
}

TEST(NodeSuite, RemoveByPath){
    Folder folder("/Users/user/books");
    folder.add(new File("/Users/user/books/design-pattern.pdf"));
    folder.remove("/Users/user/books/design-pattern.pdf");
    ASSERT_EQ(nullptr, folder.getChildByName("design-pattern.pdf"));
}

TEST(NodeSuite, FindByPath){
    Folder folder("/Users/user/books");
    folder.add(new File("/Users/user/books/design-pattern.pdf"));
    ASSERT_EQ(nullptr, folder.find("SOLID-S.pdf"));
}

// TEST(NodeSuite, FolderIterator){
//     Folder folder("/Users/user/books");
//     folder.add(new File("/Users/user/books/design-pattern.pdf"));
//     folder.add(new File("/Users/user/books/SOLID-S.pdf"));
//     // folder.add(new File("/Users/user/books/SOLID-O.pdf"));
//     // folder.add(new File("/Users/user/books/SOLID-L.pdf"));
//     // folder.add(new File("/Users/user/books/SOLID-S.pdf"));
//     // folder.add(new File("/Users/user/books/SOLID-S.pdf"));

//     FolderIterator * it = folder.createIterator();

//     // it->first();
//     // ASSERT_FALSE(it->isDone());
//     // ASSERT_EQ("design-pattern.pdf", it->currentItem()->getChildByName("design-pattern.pdf")->name());

//     // it->next();
//     // ASSERT_FALSE(it->isDone());
//     // ASSERT_EQ("SOLID-S.pdf", it->currentItem()->getChildByName("SOLID-S.pdf")->name());

//     // it->next();
//     // ASSERT_TRUE(it->isDone());
// }