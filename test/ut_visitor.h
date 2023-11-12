#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/visitor.h"
#include "../src/find_by_name_visitor.h"
#include "../src/stream_out_visitor.h"
#include "../src/tree_visitor.h"

class VisitorTest: public ::testing::Test {
protected:
    virtual void SetUp() {
        home = new Folder("structure/home");

        profile = new File("structure/home/my_profile");
        home->add(profile);

        hello1 = new File("structure/home/hello.txt");
        home->add(hello1);

        document = new Folder("structure/home/Documents");
        home->add(document);

        favorite = new Folder("structure/home/Documents/favorites");
        document->add(favorite);
        ddd = new File("structure/home/Documents/favorites/domain-driven-design.pdf");
        favorite->add(ddd);
        ca = new File("structure/home/Documents/favorites/clean-architecture.pdf");
        favorite->add(ca);
        cqrs = new File("structure/home/Documents/favorites/cqrs.pdf");
        favorite->add(cqrs);

        note = new File("structure/home/Documents/note.txt");
        document->add(note);

        hello2 = new File("structure/home/hello.txt");
        home->add(hello2);

        download = new Folder("structure/home/Downloads");
        home->add(download);

        funny = new File("structure/home/Downloads/funny.png");
        download->add(funny);

        visitor_folder = new Folder("structure/visitor");
        file1 = new File("structure/visitor/file1.txt");
        visitor_folder->add(file1);
        file2 = new File("structure/visitor/file2.txt");
        visitor_folder->add(file2);
        nested = new Folder("structure/visitor/nested");
        visitor_folder->add(nested);
        file3 = new File("structure/visitor/nested/file3.txt");
        nested->add(file3);
        file4 = new File("structure/visitor/nested/file4.txt");
        nested->add(file4);

        //add
        f1 = new File("test/testUseFolder/testFolder5/f1");
        f2 = new File("test/testUseFolder/testFolder5/f2");
        f3 = new File("test/testUseFolder/testFolder5/f3");
        f4 = new File("test/testUseFolder/testFolder5/f1.txt");
        f5 = new File("test/testUseFolder/testFolder5/f2.txt");

        fo1 = new Folder("test/testUseFolder/testFolder5/fo1");
        f11 = new File("test/testUseFolder/testFolder5/fo1/f11");
        fo11 = new Folder("test/testUseFolder/testFolder5/fo1/fo11");
        f111 = new File("test/testUseFolder/testFolder5/fo1/fo11/f111");
        f112 = new File("test/testUseFolder/testFolder5/fo1/fo11/f112");

        fo2 = new Folder("test/testUseFolder/testFolder5/fo2");
        f21 = new File("test/testUseFolder/testFolder5/fo2/f21");


        root = new Folder("test/testUseFolder/testFolder5");
        fo11->add(f111);
        fo11->add(f112);
        fo1->add(f11);
        fo1->add(fo11);

        fo2->add(f21);

        root->add(fo1);
        root->add(fo2);
        root->add(f1);
        root->add(f2);
        root->add(f3);
        root->add(f4);
        root->add(f5);
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
        delete funny;
        delete hello1;
        delete hello2;
        delete visitor_folder;
        delete file1;
        delete file2;
        delete nested;
        delete file3;
        delete file4;

        delete fo1;
        delete fo2;
        delete f1;
        delete f2;
        delete f3;
        delete f4;
        delete f5;
        delete f11;
        delete f21;
        delete fo11;
        delete f111;
        delete f112;
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
    Node * funny;
    Node * hello1;
    Node * hello2;

    Node * visitor_folder;
    Node * file1;
    Node * file2;
    Node * nested;
    Node * file3;
    Node * file4;

    Node * root;
    Node * fo1;
    Node * fo2;
    Node * f1;
    Node * f2;
    Node * f3;
    Node * f4;
    Node * f5;
    Node * f11;
    Node * f21;
    Node * fo11;
    Node * f111;
    Node * f112;
};

TEST_F(VisitorTest, findNormal) {
    FindByNameVisitor * visitor = new FindByNameVisitor("clean-architecture.pdf");

    home->accept(visitor);

    ASSERT_EQ(1, visitor->getPaths().size());
    ASSERT_EQ(ca->path(), visitor->getPaths().begin().operator*());
}

TEST_F(VisitorTest, findMany) {
    FindByNameVisitor * visitor = new FindByNameVisitor("hello.txt");

    home->accept(visitor);

    ASSERT_EQ(2, visitor->getPaths().size());
}

TEST_F(VisitorTest, findNothing) {
    FindByNameVisitor * visitor = new FindByNameVisitor("nothing-to_find");

    home->accept(visitor);

    ASSERT_EQ(0, visitor->getPaths().size());
}

TEST_F(VisitorTest, streamOutFile) {
    StreamOutVisitor * visitor = new StreamOutVisitor();

    profile->accept(visitor);

    string expected;
    expected += "_____________________________________________\n";
    expected += "structure/home/my_profile\n";
    expected += "---------------------------------------------\n";
    expected += "Profile\n";
    expected += "Name: name\n";
    expected += "_____________________________________________\n";

    ASSERT_EQ(expected, visitor->getResult());
}

TEST_F(VisitorTest, streamOutFolder) {
    StreamOutVisitor * visitor = new StreamOutVisitor();

    nested->accept(visitor);

    string expected;
    expected += "_____________________________________________\n";
    expected += "structure/visitor/nested/file3.txt\n";
    expected += "---------------------------------------------\n";
    expected += "I am file 3\n";
    expected += "_____________________________________________\n";
    expected += "\n";
    expected += "_____________________________________________\n";
    expected += "structure/visitor/nested/file4.txt\n";
    expected += "---------------------------------------------\n";
    expected += "I am file 4\n";
    expected += "_____________________________________________\n";
    expected += "\n";

    ASSERT_EQ(expected, visitor->getResult());
}

TEST_F(VisitorTest, streamOutNestedFolder) {
    StreamOutVisitor * visitor = new StreamOutVisitor();

    visitor_folder->accept(visitor);

    string expected;
    expected += "_____________________________________________\n";
    expected += "structure/visitor/file1.txt\n";
    expected += "---------------------------------------------\n";
    expected += "I am file 1\n";
    expected += "_____________________________________________\n";
    expected += "\n";
    expected += "_____________________________________________\n";
    expected += "structure/visitor/file2.txt\n";
    expected += "---------------------------------------------\n";
    expected += "I am file 2\n";
    expected += "_____________________________________________\n";
    expected += "\n";
    expected += "_____________________________________________\n";
    expected += "structure/visitor/nested/file3.txt\n";
    expected += "---------------------------------------------\n";
    expected += "I am file 3\n";
    expected += "_____________________________________________\n";
    expected += "\n";
    expected += "_____________________________________________\n";
    expected += "structure/visitor/nested/file4.txt\n";
    expected += "---------------------------------------------\n";
    expected += "I am file 4\n";
    expected += "_____________________________________________\n";
    expected += "\n";

    ASSERT_EQ(expected, visitor->getResult());
}

TEST_F(VisitorTest, treeVisitorNestedFolderByName) {
    TreeVisitor * visitor = new TreeVisitor(OrderBy::Name);
    visitor_folder->accept(visitor);

    string expected;
    expected+=".\n";
    expected+="├── file1.txt\n";
    expected+="├── file2.txt\n";
    expected+="└── nested\n";
    expected+="    ├── file3.txt\n";
    expected+="    └── file4.txt\n";

    ASSERT_EQ(expected, visitor->getTree());

} // ├:a ─:b │:c └:d

TEST_F(VisitorTest, treeVisitorNestedFolderByNameWithFolderFirst) {
    TreeVisitor * visitor = new TreeVisitor(OrderBy::NameWithFolderFirst);
    visitor_folder->accept(visitor);

    string expected;
    expected+=".\n";
    expected+="├── nested\n";
    expected+="│   ├── file3.txt\n";
    expected+="│   └── file4.txt\n";
    expected+="├── file1.txt\n";
    expected+="└── file2.txt\n";

    ASSERT_EQ(expected, visitor->getTree());
}

TEST_F(VisitorTest, treeVisitorNestedFolderByKindWithFolderfirst) {
    TreeVisitor * visitor = new TreeVisitor(OrderBy::Kind);
    visitor_folder->accept(visitor);

    string expected;
    expected+=".\n";
    expected+="├── nested\n";
    expected+="│   ├── file3.txt\n";
    expected+="│   └── file4.txt\n";
    expected+="├── file1.txt\n";
    expected+="└── file2.txt\n";

    ASSERT_EQ(expected, visitor->getTree());
}

TEST_F(VisitorTest, treeVisitorTestFolderByName) {
    TreeVisitor * visitor = new TreeVisitor(OrderBy::Name);
    root->accept(visitor);

    string expected;
    expected+=".\n";
    expected+="├── f1\n";
    expected+="├── f1.txt\n";
    expected+="├── f2\n";
    expected+="├── f2.txt\n";
    expected+="├── f3\n";
    expected+="├── fo1\n";
    expected+="│   ├── f11\n";
    expected+="│   └── fo11\n";
    expected+="│       ├── f111\n";
    expected+="│       └── f112\n";
    expected+="└── fo2\n";
    expected+="    └── f21\n";

    ASSERT_EQ(expected, visitor->getTree());
}

TEST_F(VisitorTest, treeVisitorTestFolderByNameWithFolderFirst) {
    TreeVisitor * visitor = new TreeVisitor(OrderBy::NameWithFolderFirst);
    root->accept(visitor);

    string expected;
    expected+=".\n";
    expected+="├── fo1\n";
    expected+="│   ├── fo11\n";
    expected+="│   │   ├── f111\n";
    expected+="│   │   └── f112\n";
    expected+="│   └── f11\n";
    expected+="├── fo2\n";
    expected+="│   └── f21\n";
    expected+="├── f1\n";
    expected+="├── f1.txt\n";
    expected+="├── f2\n";
    expected+="├── f2.txt\n";
    expected+="└── f3\n";

    ASSERT_EQ(expected, visitor->getTree());
}

TEST_F(VisitorTest, treeVisitorTestFolderByKind) {
    TreeVisitor * visitor = new TreeVisitor(OrderBy::Kind);
    root->accept(visitor);

    string expected;
    expected+=".\n";
    expected+="├── f1\n";
    expected+="├── f2\n";
    expected+="├── f3\n";
    expected+="├── fo1\n";
    expected+="│   ├── f11\n";
    expected+="│   └── fo11\n";
    expected+="│       ├── f111\n";
    expected+="│       └── f112\n";
    expected+="├── fo2\n";
    expected+="│   └── f21\n";
    expected+="├── f1.txt\n";
    expected+="└── f2.txt\n";

    ASSERT_EQ(expected, visitor->getTree());
}