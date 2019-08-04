#include <iostream>
#include "Parser.h"
#include "basic_structs.h"
#include "BugMod.h"
#include <string>
#include <cstdio>
using namespace std;


int BugMod::get_new_line_num(LineChange * lc, Parser & mod_bug) {
    // std::list<FileChange *>::iterator it;
    int disp_num = lc->result_line_num;
    for (auto const & i : (mod_bug.patch.file_changes)) {
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

void BugMod::display(Parser & par_bug, Parser & mod_bug) {
    cout << " \tbefore debugged\tAfter debugged\tnow\t content" << endl;
    for (auto const & file: (par_bug.patch.file_changes)){
        printf("File dir when un-debugged:\t%s\n",(file->orig_dir.c_str()));
        printf("File dir after debugged:\t%s\n",file->final_dir.c_str());
        bool ifModAfterDebugged = false;
        for (auto const & new_file: (mod_bug.patch.file_changes)) {
            if( (new_file->orig_dir.substr(2)
                        .compare(file->final_dir.substr(2)) == 0) ) {
                printf("File dir right now:\t\t%s", new_file->final_dir.c_str());
                ifModAfterDebugged = true;                
                break;
            } 
        }
        printf(ifModAfterDebugged ? "" : "File dir right now:\t%s\n",file->final_dir.c_str());
        for (auto const & line : (file->linechanges)) {
            printf("%d\t%d\t%d\t%s",
                    line->inserted_line_num,
                    line->result_line_num,
                    this->get_new_line_num(line, mod_bug),
                    line->line_content.c_str());
        }
    }
}



int main(int argc, char const *argv[]) {
    int a = 5;
    cout << "Hello, world" << endl;
    string bug_par_hash = "ec2b076e8832c";
    string now_par_hash = "714ab525d5ada";
    Parser bug_par = Parser(std::string (bug_par_hash));
    Parser now_par = Parser(std::string (bug_par_hash), std::string (now_par_hash));
    BugMod bm = BugMod(bug_par_hash, now_par_hash);
    bm.display(bug_par, now_par);
}


