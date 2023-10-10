#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"

TEST(NodeSuite, Ping){
    ASSERT_TRUE(true);
}

TEST(NodeSuite, FileNameIsDPpdf){
    File * file = new File("/Users/user/books/design-pattern.pdf");
    ASSERT_EQ("design-pattern.pdf", file->name());
}

TEST(NodeSuite, FilePathIsDPpdf){
    File * file = new File("/Users/user/books/design-pattern.pdf");
    ASSERT_EQ("/Users/user/books/design-pattern.pdf", file->path());
}

TEST(NodeSuite, FolderNameIsBooks){
    Folder * folder = new Folder("/Users/user/books");
    ASSERT_EQ("books", folder->name());
}

TEST(NodeSuite, FolderPathIsBooks){
    Folder * folder = new Folder("/Users/user/books");
    ASSERT_EQ("/Users/user/books", folder->path());
}

TEST(NodeSuite, FolderAddChild){
    Folder * folder = new Folder("/Users/user/books");
    folder->add(new File("/Users/user/books/design-pattern.pdf"));
    ASSERT_EQ("design-pattern.pdf", folder->getChildByName("design-pattern.pdf")->name());

    Folder * folder2 = new Folder("/Users/user/NOTbooks");
    folder2->add(new File("/Users/user/books/POSD.pdf"));
    ASSERT_EQ(nullptr, folder->getChildByName("POSD.pdf"));
}

TEST(NodeSuite, RemoveByPath){
    Folder * folder = new Folder("/Users/user/books");
    folder->add(new File("/Users/user/books/design-pattern.pdf"));
    folder->remove("/Users/user/books/design-pattern.pdf");
    ASSERT_EQ(nullptr, folder->getChildByName("design-pattern.pdf"));
}

TEST(NodeSuite, FindByPath){
    Folder * folder = new Folder("/Users/user/books");
    folder->add(new File("/Users/user/books/design-pattern.pdf"));
    ASSERT_EQ(nullptr, folder->find("SOLID-S.pdf"));
}

TEST(NodeSuite, NumberOfFiles){
    Folder * folder = new Folder("/Users/user/books");
    folder->add(new File("/Users/user/books/design-pattern.pdf"));

    Folder * folder2 = new Folder("/Users/user/books/SOLID");
    folder2->add(new File("/Users/user/books/SOLID/SOLID-S.pdf"));
    folder2->add(new File("/Users/user/books/SOLID/SOLID-O.pdf"));
    folder2->add(new File("/Users/user/books/SOLID/SOLID-L.pdf"));
    folder2->add(new File("/Users/user/books/SOLID/SOLID-I.pdf"));
    folder2->add(new File("/Users/user/books/SOLID/SOLID-D.pdf"));

    folder->add(folder2);

    ASSERT_DOUBLE_EQ(6, folder->numberOfFiles());
}

TEST(NodeSuite, FolderIterator){
    Folder * folder = new Folder("/Users/user/books");
    folder->add(new File("/Users/user/books/design-pattern.pdf"));
    Folder * folder2 = new Folder("/Users/user/books/SOLID");
    folder2->add(new File("/Users/user/books/SOLID/SOLID-S.pdf"));
    folder->add(folder2);
    
    FolderIterator * it = folder->createIterator();

    it->first();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("design-pattern.pdf", it->currentItem()->name());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("SOLID", it->currentItem()->name());

    it->next();
    ASSERT_TRUE(it->isDone());
}