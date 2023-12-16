#include <string>
#include "../src/folder.h"

using namespace std;

TEST(Folder, normal) {
    Folder home("structure/home");

    ASSERT_EQ("home", home.name());
    ASSERT_EQ("structure/home", home.path());
}

TEST(Folder, invalid_folder) {
    ASSERT_ANY_THROW(Folder("/NOT/EXIST/PATH"));
}

TEST(Folder, invalid_folder_2) {
    ASSERT_ANY_THROW(Folder("structure/home/Documents/hello.txt"));
}

TEST(Folder, add_file) {
    Folder * home = new Folder("structure/home");
    File * hello = new File("structure/home/hello.txt");
    home->add(hello);

    ASSERT_EQ("hello.txt", home->getChildByName("hello.txt")->name());

    delete home;
}

TEST(Folder, add_incorrect_path_file_to_folder) {
    Folder * home = new Folder("structure/home");
    File * hello = new File("structure/home/Documents/hello.txt");
    ASSERT_ANY_THROW(home->add(hello));
    
    delete home;
}

TEST(Folder, add_folder) {
    Folder * home = new Folder("structure/home");
    Folder * document = new Folder("structure/home/Documents");

    home->add(document);

    ASSERT_EQ("Documents", home->getChildByName("Documents")->name());

    delete home;
}

TEST(Folder, renameFolder){
    Folder * home = new Folder("structure/home");
    Folder * document = new Folder("structure/home/Documents");
    Folder * downloads = new Folder("structure/home/Downloads");
    File* hello = new File("structure/home/hello.txt");
    File* funny = new File("structure/home/Downloads/funny.png");
    Folder * favorites = new Folder("structure/home/Documents/favorites");
    File* ca = new File("structure/home/Documents/favorites/clean-architecture.pdf");

    home->add(document);
    home->add(downloads);
    home->add(hello);
    downloads->add(funny);
    document->add(favorites);
    favorites->add(ca);

    home->rename("homeRe");

    ASSERT_EQ("homeRe", home->name());
    ASSERT_EQ("structure/homeRe", home->path());
    
    ASSERT_EQ("structure/homeRe/Documents", document->path());
    ASSERT_EQ("structure/homeRe/Downloads", downloads->path());
    ASSERT_EQ("structure/homeRe/hello.txt", hello->path());
    ASSERT_EQ("structure/homeRe/Downloads/funny.png", funny->path());
    ASSERT_EQ("structure/homeRe/Documents/favorites", favorites->path());
    ASSERT_EQ("structure/homeRe/Documents/favorites/clean-architecture.pdf", ca->path());
}