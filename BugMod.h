#ifndef BUGMOD_H
#define BUGMOD_H
#include <string>
#include "Parser.h"
using namespace std;


class BugMod {
public:
    string bug_commit_hash;
    string cur_commit_hash;
    Parser par_bug;
    Parser mod_bug;

    BugMod(string bug_commit_hash1, string cur_commit_hash2);
    int get_new_line_num(LineChange * lc);
    void display();
};

BugMod::BugMod(string bug_commit_hash, string cur_commit_hash) {
    this->bug_commit_hash = bug_commit_hash;
    this->cur_commit_hash = cur_commit_hash;
    this->par_bug = Parser(this->bug_commit_hash);
    this->mod_bug = Parser(this->bug_commit_hash, this->cur_commit_hash);
}

#endif