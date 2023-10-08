#if !defined(FILE_H)
#define FILE_H

class File: public Node {
public:
    File(string path):_path(path) {
        
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

#endif // FILE_H
