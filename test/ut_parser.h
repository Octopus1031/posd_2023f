#include "../src/file_system_parser.h" 
#include "../src/file_system_scanner.h"
#include "../src/file_system_builder.h"
// #include "../src/node.h"

// #include <map>
#include <string>
#include <vector>
#include <algorithm>

TEST(ParserTest, Scanner){
    string path = "structure";
    FileSystemScanner * scanner = new FileSystemScanner();
    scanner->setPath(path.c_str());
    
    scanner->nextNode();
    scanner->nextNode();
    scanner->nextNode();
    scanner->nextNode();
    ASSERT_TRUE(scanner->isDone());

    // map<std:string, Node*> * m = scanner->getMap();
    std::vector<string> l = scanner->getVector();
    ASSERT_TRUE( find(l.begin(), l.end(), "home") );
    ASSERT_TRUE( find(l.begin(), l.end(), "vistor") );
    ASSERT_TRUE( find(l.begin(), l.end(), "flie.txt") );
    // ASSERT_FALSE( find(l.begin(), l.end(), "12345" ));
}