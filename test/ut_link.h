#include "../src/link.h"
#include "../src/node.h"

TEST(Link, linkSet){
    Node* n = new Folder("structure/home");
    Node* link = new Link(n);

    ASSERT_EQ("home", link->name());
    ASSERT_EQ("structure/home", link->path());

    
}