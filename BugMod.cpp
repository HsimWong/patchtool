#include <iostream>
#include "Parser.h"
#include "basic_structs.h"
#include <string>
using namespace std;

class BugMod {
private:
    string bug_commit_hash;
    string cur_commit_hash;
public:
    BugMod(string bug_commit_hash, string cur_commit_hash);
    ~BugMod();
};

BugMod::BugMod(string bug_commit_hash, string cur_commit_hash) {
    this->bug_commit_hash = bug_commit_hash;
    this->cur_commit_hash = cur_commit_hash;
    Parser * par_bug = new Parser(bug_commit_hash);
    Parser * mod_bug = new Parser(bug_commit_hash, cur_commit_hash);
}

BugMod::~BugMod() {
}

int main(int argc, char const *argv[]) {
    int a = 5;
    cout << "Hello, world" << endl;
    BugMod * bm = new BugMod("0f2bb18a0b", "4f4891263");
    return 0;
}


