#include <list>

#include "../src/link.h"
#include "../src/node.h"

class LinkTest: public ::testing::Test{
protected:
    virtual void SetUp(){
        path = "structure/home";
        home = new Folder(path);
        documents = new Folder(path + "/Documents");
        downloads = new Folder(path + "/Downloads");
        hello = new File(path + "/hello.txt");
        profile = new File(path + "/my_profile");
    }

    void TearDown(){
        delete home;
        home = nullptr;
        documents = nullptr;
        downloads = nullptr;
        hello = nullptr;
        profile = nullptr;
    }

    std::string path = "structure/home";
    Node* home;
    Node* documents;
    Node* downloads;
    Node* hello;
    Node* profile;
};

TEST_F(LinkTest, LinkSetting){
    Node* link = new Link(path, new Folder(path));

    ASSERT_EQ("home", link->name());
    ASSERT_EQ(path , link->path());    
}

TEST_F(LinkTest, LinkAddAndNumberOfFiles){
    Node* linkHome = new Link(path, home);
    Node* linkHello = new Link(path + "/hello.txt", hello);

    linkHome->add(documents);
    linkHome->add(downloads);
    linkHome->add(hello);
    linkHome->add(profile);

    ASSERT_EQ(1, linkHello->numberOfFiles());
    ASSERT_EQ(2, linkHome->numberOfFiles()); 
}

TEST_F(LinkTest, LinkFind){
    Node* linkHome = new Link(path, home);
    Node* linkHello = new Link(path + "/hello.txt", hello);

    linkHome->add(documents);
    linkHome->add(downloads);
    linkHome->add(hello);
    linkHome->add(profile);

    ASSERT_EQ(hello, linkHello->find(linkHello->path()));
    ASSERT_EQ(hello, linkHome->find(linkHello->path()));
    ASSERT_EQ(home, linkHome->find(linkHome->path()));
    ASSERT_EQ(nullptr, linkHome->find("structure/Nothing"));
}

TEST_F(LinkTest, LinkFuncs){
    Link* linkHome = new Link("structure/home/linkHome", home);
    Link* linkHello = new Link("structure/home/linkHello", hello);

    linkHome->add(documents);
    linkHome->add(downloads);
    linkHome->add(profile);

    ASSERT_EQ(hello->path(), linkHello->getTarget()->path());
    ASSERT_EQ(home->path(), linkHome->getTarget()->path());
    ASSERT_EQ(0, linkHome->findByName("linkHome").size());
    ASSERT_EQ(0, linkHome->findByName("linkHello").size());
}