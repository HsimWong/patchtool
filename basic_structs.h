#ifndef BASIC_STRUCTS_H
#define BASIC_STRUCTS_H
#include <string>
#include "basic_structs.cpp"
struct LineChange;
struct FileChange;
struct Patch;

int line_modified_above(LineChange * l, Patch * cmd);
std::string exec(const char* cmd);
#endif