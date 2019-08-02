#include <iostream>
#include <algorithm>
#include <list>
#include "basic_structs.h"
using namespace std;

int fetch_int(char * cha, int & i) {
    string start_num = "";
    for (int j = i + 1; cha[i] != 0; j++) {
        if (cha[j] == ',') {
            return stoi(start_num);
            i = j;
        } else {
            start_num += cha[j];
        }
        i = j;
    }
}

void parse_line_num(int & ori_num, int & fin_num, char * cha) {
    for (int i = 0; cha[i] != '\0'; i++) {
        if (cha[i] == '+') {
            ori_num = fetch_int(cha, i);
        } else if (cha[i] == '-') {
            fin_num = fetch_int(cha, i);
            break;
        } else {
            continue;
        }
    }
}

int main(int argc, char const *argv[]) {
    char * info = "@@ +245, 13 -175,35 @@";
    int start_num = 0;
    int final_num = 0;
    parse_line_num(start_num, final_num, info);
    cout << start_num << endl;
    cout << final_num << endl;
    cout << info << endl;
    
    // Patch patch = *(new Patch);
    // patch.commit_hash = "commit_hash";
    // cout << patch.commit_hash << endl;
    // patch.file_changes = *(new list<FileChange *>);
    // FileChange fc = *(new FileChange);
    // fc.final_dir = "final+dir";
    // cout << fc.final_dir << endl;
    // patch.file_changes.push_back(&fc);
    // printf("%d\n", &fc);
    // printf("%d\n", *(patch.file_changes.rbegin()));
    // // cout << patch.file_changes.begin() << endl;


    return 0;
}

