#include "../src/file_system_parser.h" 
#include "../src/file_system_scanner.h"
#include "../src/file_system_builder.h"

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
        // size_t find = 
        if( scanner->currentNodeName().find(".")!=string::npos){
            ASSERT_TRUE(scanner->isFile());
        }
        else{
            ASSERT_TRUE(scanner->isFolder());
        }
    }
}

TEST(ParserTest, parser){
    
}