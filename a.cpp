#include <iostream>
#include <unistd.h>
#include <bits/stdc++.h>
#include <stdio.h>
#include <memory>
#include <stdexcept>
#include <array>

using namespace std;


// string exec(string cmd) {
//     array<char, 128> buffer;
//     string result;
//     char char_arr_cmd[cmd.length() + 1];
//     strcpy(char_arr_cmd, cmd.c_str());
//     unique_ptr<FILE, decltype(&pclose) > pipe(popen(char_arr_cmd, "r"), pclose);
//     if (!pipe) {
//         throw runtime_error("popen() failed");
//     }

//     while (fgets(buffer.data(), buffer.size, pipe.get()) != nullptr) {
//         result += buffer.data();
//     }
//     return result;
// } 


std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}
struct Modification {
    string file_dir;
    string mod_content;
    int line_num;
    Modification * next_line = NULL;
};

class Patch {
private:
    string commit_id;                               // id of commit where bug is modified
    Modification * mod;                             // Linked list of modification lines
    string get_patch_info();
public:
    Patch(string repo_dir, string commit_id);
    ~Patch();
    Modification * mod_list_in_other_commit(string commit_id);
    
};

Patch::Patch(string repo_dir, string commit_id) {
    this -> commit_id = commit_id;
    
}

int main(int argc, char const *argv[]) {
    string rslt = exec("cd ../test && git log -p");
    cout << rslt << endl;
}
