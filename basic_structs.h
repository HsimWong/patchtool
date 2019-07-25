#ifndef BASIC_STRUCTS_H
#define BASIC_STRUCTS_H

#include <string>
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

struct LineChange {
    string file_dir;
    int line_num;
    string line_content;
    string commit_hash;
};

struct FileChange{
    string file_dir;
    list<LineChange *> linechanges;
};

struct Commit {
    string commit_hash;
    list<FileChange *> file_changes;
    string author;
    string email;
};

int line_modified_above(LineChange * l, Commit * cmt) {
    int mod_num = 0;
    FileChange * new_version_file;
    for (auto const & i : (cmt->file_changes)) {
        if(i->file_dir == (l->file_dir)) {
            new_version_file = i;
            break;
        } else {
            continue;
        }
    }
    if (!(new_version_file == nullptr)) {
        for(auto const & i : (new_version_file->linechanges)) {
            if (i->line_num > ())
        }
    } else {
        return 0;
    }
}

#endif