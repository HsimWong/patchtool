#include <iostream>
#include "Parser.h"
#include "basic_structs.h"
#include <string>
#include <cstdio>
using namespace std;

class BugMod {
private:
    string bug_commit_hash;
    string cur_commit_hash;
    Parser par_bug;
    Parser mod_bug;
public:
    int get_new_line_num(LineChange * lc);
    BugMod(string bug_commit_hash, string cur_commit_hash);
    ~BugMod();
    void display();
};

BugMod::BugMod(string bug_commit_hash, string cur_commit_hash) {
    this->bug_commit_hash = bug_commit_hash;
    this->cur_commit_hash = cur_commit_hash;
    this->par_bug = *(new Parser(bug_commit_hash));
    this->mod_bug = *(new Parser(bug_commit_hash, cur_commit_hash));
}

int BugMod::get_new_line_num(LineChange * lc) {
    // std::list<FileChange *>::iterator it;
    int disp_num = lc->result_line_num;
    for (auto const & i : (this->mod_bug.patch.file_changes)) {
        if (i->orig_dir.substr(1).compare(lc->final_dir.substr(1)) == 0) {
            for (auto const & l : i->linechanges) {
                if ((l->inserted_line_num) < (lc->result_line_num)) {
                    disp_num += l->if_inserted;
                }
            }
        }
    }
    return (lc->result_line_num + disp_num);
}

void BugMod::display() {
    cout << " \tbefore debugged\tAfter debugged\tnow\t content" << endl;
    for (auto const & file: (this->par_bug.patch.file_changes)){
        printf("File dir when un-debugged:\t%s\n",file->orig_dir);
        printf("File dir after debugged:\t%s\n",file->final_dir);
        bool ifModAfterDebugged = false;
        for (auto const & new_file: (this->mod_bug.patch.file_changes)) {
            if( (new_file->orig_dir.substr(2)
                        .compare(file->final_dir.substr(2)) == 0) ) {
                printf("File dir right now:\t\t%s", new_file->final_dir);
                ifModAfterDebugged = true;                
                break;
            } 
        }
        printf(ifModAfterDebugged ? "" : "File dir right now:\t%s\n",file->final_dir);
        for (auto const & line : (file->linechanges)) {
            print("%d\t%d\t%d\t%s", 
                (line->if_inserted) == 1 ? "" : line->inserted_line_num,
                line->result_line_num,
                (line->if_inserted) == -1 ? "" : get_new_line_num(line),
                line->line_content
            );
        }
    }
}



int main(int argc, char const *argv[]) {
    int a = 5;
    cout << "Hello, world" << endl;

    BugMod * bm = new BugMod("0f2bb18a0b", "4f4891263");
    bm->display();
    return 0;
}


