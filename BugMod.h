#ifndef BUGMOD_H
#define BUGMOD_H
#include <string>

class BugMod {
private:
    string bug_commit_hash;
    string cur_commit_hash;
public:
    BugMod(std::string bug_commit_hash, std::string cur_commit_hash);
    ~BugMod();
};

#endif