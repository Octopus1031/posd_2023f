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
    scanner->nextNode();
    ASSERT_TRUE(scanner->isDone());

    std::vector<string> v = scanner->getVector();
    ASSERT_TRUE( find(v.begin(), v.end(), "home")!=v.end() );
    ASSERT_TRUE( find(v.begin(), v.end(), "visitor")!=v.end() );
    ASSERT_TRUE( find(v.begin(), v.end(), "file.txt")!=v.end() );
}