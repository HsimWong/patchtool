#ifndef BASIC_STRUCTS_CPP
#define BASIC_STRUCTS_CPP

#include <string>
#include <list>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <array>
#include <unistd.h>
#include <bits/stdc++.h>
using namespace std;

struct LineChange {
    string file_dir;
    int inserted_line_num;
    int result_line_num;
    string line_content;
    string commit_hash;
};

struct FileChange{
    string orig_dir;
    string final_dir;
    list<LineChange *> linechanges;
};

struct Patch {
    string commit_hash;
    list<FileChange *> file_changes;

};

int line_modified_above(LineChange * l, Patch * cmt) {
    int mod_num = 0;
    FileChange * new_version_file;
    /* Find out interfered files */
    for (auto const & i : (cmt->file_changes)) {
        if(i->final_dir == (l->file_dir)) {
            new_version_file = i;
            break;
        } else {
            continue;
        }
    }
    /* Dealing with front-inserted 
     * lines when interfered file is not empty. */
    int influenced_offset_num = 0;
    if (new_version_file != nullptr) {
        for(auto const & i : (new_version_file->linechanges)) {
            if ((i->inserted_line_num) <= (l->result_line_num)) {
                influenced_offset_num += 
                    (l->line_content.substr(0, 1).compare("+") == 0) ? 1 : -1;
            } else {
                continue;
            }
        }
    } 
    return influenced_offset_num;
}

// string get_one_string(string &string) {

// }

// Patch new_patch(string git_diff_info) {

// }

string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose) > pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}



#endif