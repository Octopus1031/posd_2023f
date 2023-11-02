#include "../src/file_system_parser.h" 
#include "../src/file_system_scanner.h"
#include "../src/file_system_builder.h"
#include "../src/file.h"
#include "../src/folder.h"

#include <string>
#include <vector>
#include <algorithm>

TEST(ParserTest, scannerScan){
    string path = "structure";
    FileSystemScanner * scanner = new FileSystemScanner();
    scanner->setPath(path.c_str());
    
    scanner->nextNode();
    scanner->nextNode();
    scanner->nextNode();
    scanner->nextNode();
    scanner->nextNode();
    ASSERT_TRUE(scanner->isDone());

    std::vector<string> v = scanner->getVector();
    ASSERT_TRUE( find(v.begin(), v.end(), "home")!=v.end() );
    ASSERT_TRUE( find(v.begin(), v.end(), "visitor")!=v.end() );
    ASSERT_TRUE( find(v.begin(), v.end(), "file.txt")!=v.end() );
}

TEST(ParserTest, scannerScanType){
    string path = "structure";
    FileSystemScanner * scanner = new FileSystemScanner();
    scanner->setPath(path.c_str());

    // mac OS 多一個.DS_store檔案
    for(int i=0; i<4; i++){
        scanner->nextNode();
        // TODO 遇到"沒.的檔案"會有問題 再看怎麼改
        if( scanner->currentNodeName().find(".")!=string::npos){
            ASSERT_TRUE(scanner->isFile());
        }
        else{
            ASSERT_TRUE(scanner->isFolder());
        }
    }
}

TEST(ParserTest, parserWithOneFile){
    string path = "test/testUseFolder/testFolder";
    FileSystemParser* parser = new FileSystemParser( new FileSystemBuilder() );
    parser->setPath(path.c_str());
    parser->parse();
    
    Folder * root = parser->getRoot();
    ASSERT_TRUE( root->getChildByName("testFile1")!=NULL );
}

TEST(ParserTest, parserWithFiles){
    string path = "test/testUseFolder/testFolder4";
    // string path = "test/testUseFolder/testFolder2/testFolder3";
    FileSystemParser* parser = new FileSystemParser( new FileSystemBuilder() );
    parser->setPath(path.c_str());
    parser->parse();
    
    Folder * root = parser->getRoot();
    ASSERT_TRUE( root->getChildByName("testFile1")!=NULL );
    ASSERT_TRUE( root->getChildByName("testFile2")!=NULL );
    ASSERT_TRUE( root->getChildByName("testFile3")!=NULL );
}

TEST(ParserTest, folderWithNothing){
    string path = "test/testUseFolder/testFolder2/testFolder3";
    FileSystemParser* parser = new FileSystemParser( new FileSystemBuilder() );
    parser->setPath(path.c_str());
    parser->parse();
    
    ASSERT_EQ( 0, parser->getVector().size() );
}

TEST(ParserTest, parserWithOneFolder){
    string path = "test/testUseFolder/testFolder2";
    FileSystemParser* parser = new FileSystemParser( new FileSystemBuilder() );
    parser->setPath(path.c_str());
    parser->parse();
    
    Folder * root = parser->getRoot();
    ASSERT_EQ("testFolder2", root->name());
    ASSERT_TRUE( root->getChildByName("testFolder3")!=NULL );
}

// TEST(ParserTest, parserWithFolderNested){
//     string path = "structure/visitor/nested";
//     FileSystemParser* parser = new FileSystemParser( new FileSystemBuilder() );
//     parser->setPath(path.c_str());
//     parser->parse();
    
//     Folder * root = parser->getRoot();
//     ASSERT_EQ("nested", root->name());
//     ASSERT_TRUE( root->getChildByName("file3.txt")!=NULL );
//     ASSERT_TRUE( root->getChildByName("file4.txt")!=NULL );
// }

TEST(ParserTest, parserWithFolderVisitor){
    string path = "structure/visitor";
    FileSystemParser* parser = new FileSystemParser( new FileSystemBuilder() );
    parser->setPath(path.c_str());
    parser->parse();
    
    Folder * root = parser->getRoot();
    ASSERT_EQ("visitor", root->name());
    // ASSERT_EQ("nested", parser->test);
    ASSERT_TRUE( root->getChildByName("nested")!=NULL );
    ASSERT_TRUE( root->getChildByName("file1.txt")!=NULL );
    ASSERT_TRUE( root->getChildByName("file2.txt")!=NULL );
    ASSERT_TRUE( root->getChildByName("nested")->getChildByName("file3.txt")!=NULL );
    ASSERT_TRUE( root->getChildByName("nested")->getChildByName("file4.txt")!=NULL );
}
