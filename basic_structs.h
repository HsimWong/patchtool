#ifndef BASIC_STRUCTS_H
#define BASIC_STRUCTS_H
#include <string>
#include <list>
using namespace std;

struct LineChange {
    string ori_file_dir;
    string final_dir;
    int inserted_line_num;
    int result_line_num;
    bool if_inserted;
    string line_content;
    string commit_hash;
};

struct FileChange{
    string orig_dir;
    string final_dir;
    list<LineChange> linechanges;
};

struct Patch {
    string commit_hash;
    list<FileChange> file_changes;

};



int line_modified_above(LineChange * l, Patch * cmd);
std::string exec_cmd(const char* cmd);
#endif