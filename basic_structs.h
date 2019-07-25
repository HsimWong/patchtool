#ifndef BASIC_STRUCTS_H
#define BASIC_STRUCTS_H

#include <string>
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

struct LineChange {

};

struct FileChange{
    string file_dir;
    list<LineChange *> linechanges;
};

struct Commit {
    string commit_hash;
    list<FileChange *> file_changes;


};
#endif