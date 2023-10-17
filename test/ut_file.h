#pragma once 

#include "../src/file.h"

TEST(File, normal) {
    File hello("test/home/hello.txt");
    ASSERT_EQ("hello.txt", hello.name());
    ASSERT_EQ("test/home/hello.txt", hello.path());
}

TEST(File, notFileType){
    ASSERT_ANY_THROW(new File ("test/home/Documents"));
}