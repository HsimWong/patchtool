#ifndef PATCH_H
#define PATCH_H
#include <string>
#include <iostream>
using namespace std;
struct Modification {
    string file_dir;
    int line_num;
    Modification * next_line;
};

class Patch {
private:
    string commit_id;
    Modification * mod;
public:
    Patch(string file_dir, string commit_id);
    ~Patch();
    void showPatch(){

    }
};

Patch::Patch(string file_dir, string commit_id){
    this -> commit_id = commit_id;

}

Patch::~Patch(){
}



#endif