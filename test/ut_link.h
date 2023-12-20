#include "../src/link.h"
#include "../src/node.h"

TEST(Link, linkSetting){
    std::string path = "structure/home";
    Node* link = new Link(path, new Folder(path));

    ASSERT_EQ("home", link->name());
    ASSERT_EQ(path , link->path());    
}

TEST(Link, linkAddAndNumberOfFiles){
    std::string path = "structure/home";
    Node* home = new Folder(path);
    Node* linkHome = new Link(path, home);

    Node* document = new Folder(path + "/Documents");
    Node* download = new Folder(path + "/Downloads");
    Node* hello = new File(path + "/hello.txt");
    Node* linkHello = new Link(path + "/hello.txt", hello);

    Node* profile = new File(path + "/my_profile");

    linkHome->add(document);
    linkHome->add(download);
    linkHome->add(hello);
    linkHome->add(profile);

    ASSERT_EQ(1, linkHello->numberOfFiles());
    ASSERT_EQ(2, linkHome->numberOfFiles()); 
}