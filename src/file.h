#if !defined(FILE_H)
#define FILE_H

class File: public Node {
public:
    File(string path):_path(path) {
        
    }
    string name() const override{
        std::vector<string> v = split(path(), "/");
        return v.back();
    };

    string path() const override{
        return _path;
    }

    int numberOfFiles() const override{
        return 1;
    }

    //new add
    string getFolder() const override{
        std::vector<string> v = split(_path, "/");
        v.pop_back();
        return v.back();
    }

private: 
    string _path;
};

#endif // FILE_H
