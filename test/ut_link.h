#include "../src/link.h"
#include "../src/node.h"

TEST(Link, linkSet){
    std::string path = "structure/home";
    Node* link = new Link(path, new Folder(path));

    ASSERT_EQ("home", link->name());
    ASSERT_EQ("structure/home", link->path());

    
}