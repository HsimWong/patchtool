#include <iostream>
#include <unistd.h>
#include <bits/stdc++.h>
using namespace std;

struct Modification {
    string file_dir;
    int line_num;
    Modification * next_line;
};

class Patch {
private:
    string commit_id;                               // id of commit where bug is modified
    Modification * mod;                             // Linked list of modification lines
public:
    Patch(string repo_dir, string commit_id);
    ~Patch();
};




int main(int argc, char const *argv[]) {
    system("git");
}
