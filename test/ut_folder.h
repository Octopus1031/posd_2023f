#pragma once 

#include <string>
#include "../src/folder.h"

using namespace std;

TEST(Folder, normal) {
    Folder home("test/home");

    ASSERT_EQ("home", home.name());
    ASSERT_EQ("test/home", home.path());
}

TEST(Folder, add_file) {
    Folder home("test/home");
    File hello("test/home/hello.txt");
    home.add(&hello);

    ASSERT_EQ("hello.txt", home.getChildByName("hello.txt")->name());
}

TEST(Folder, add_incorrect_path_file_to_folder) {
    Folder home("test/home");
    File hello("test/home/Documents/note.txt");
    ASSERT_ANY_THROW(home.add(&hello));
}

TEST(Folder, add_folder) {
    Folder home("test/home");
    Folder document("test/home/Documents");

    home.add(&document);

    ASSERT_EQ("Documents", home.getChildByName("Documents")->name());
}

TEST(Folder, notFolderType){
    ASSERT_ANY_THROW(new Folder ("test/home/Documents/note.txt"));
}