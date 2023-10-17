#pragma once 

#include "../src/find_by_name_visitor.h"
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"

class VisitorTest: public ::testing::Test {
protected:
    void SetUp() {
        home = new Folder("test/home");

        profile = new File("test/home/my_profile");
        home->add(profile);

        download = new Folder("test/home/Downloads");
        home->add(download);

        document = new Folder("test/home/Documents");
        home->add(document);

        note = new File("test/home/Documents/note.txt");
        document->add(note);

        favorite = new Folder("test/home/Documents/favorites");
        document->add(favorite);
        ddd = new File("test/home/Documents/favorites/domain-driven-design.pdf");
        favorite->add(ddd);
        ca = new File("test/home/Documents/favorites/clean-architecture.pdf");
        favorite->add(ca);
        cqrs = new File("test/home/Documents/favorites/cqrs.pdf");
        favorite->add(cqrs);
    }

    void TearDown() {
        delete home;
        delete profile;
        delete download;
        delete document;
        delete note;
        delete favorite;
        delete ddd;
        delete ca;
        delete cqrs;
    }
    
    Node * home;
    Node * profile;
    Node * download;
    Node * document;
    Node * note;
    Node * favorite;
    Node * ddd;
    Node * ca;
    Node * cqrs;
};

TEST_F(VisitorTest, find_file){
    FindByNameVisitor v("note.txt");
    Node* result = v.findByName(document);

    ASSERT_EQ(note, result);

    // Node * result = home->find("test/home/Documents/favorites/cqrs.pdf");
    // ASSERT_EQ(nullptr, result);
}

TEST_F(VisitorTest, test){
    FindByNameVisitor v("my_profile");
    Node* result = home->getChildByName("my_profile");
    ASSERT_EQ(profile, result);
}