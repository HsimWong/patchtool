#ifndef BASIC_STRUCTS_H
#define BASIC_STRUCTS_H
#include <string>
#include <list>
#include <vector>
using namespace std;

struct LineChange {
    string ori_file_dir;
    string final_dir;
    int inserted_line_num;
    int result_line_num;
    int if_inserted;            // INSERTED: 1, DELETED: -1, UNMODIFIED: 0
    string line_content;
    string commit_hash;
};

struct FileChange{
    string orig_dir;
    string final_dir;
    vector<LineChange *> linechanges;
};

struct Patch {
    string commit_hash;
    vector<FileChange *> file_changes;

};
std::string toString(char * str);
std::string exec_cmd(const char* cmd);
#endif