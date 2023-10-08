#if !defined(FOLDER)
#define FOLDER

#include <string>

using namespace std;

class Folder: public Node {
public:
    Folder(string path):_path(path) {
        
    }
    string name() const override{
        vector<string> v = split(path(), "/");
        return v.back();
    };

    string path() const override{
        return _path;
    }

private: 
    string _path;
};


#endif // FOLDER
