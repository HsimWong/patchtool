//
// Created by xwan on 7/31/19.
//

#ifndef PATCHTOOL_PARSER_H
#define PATCHTOOL_PARSER_H

#include <string>
#include "basic_structs.h"
using namespace std;
//string * identifiers;
class Parser {
public:
    Patch patch;
    FileChange * cur_file;
    int cur_ori_num;
    int cur_fin_num;
    string commit_hash;
    void deal_with_one_line(int ident_id, char * st);
    void Parse_patch_git_info(string str);
    void parse_line_num(int & ori_num, int & fin_num, char * cha);
    explicit Parser(string commit_hash);
    Parser(string commit_hash1, string commit_hash2);
};


#endif //PATCHTOOL_PARSER_H
