//
// Created by xwan on 7/31/19.
//

#ifndef PATCHTOOL_PARSER_H
#define PATCHTOOL_PARSER_H


//#include <bits/basic_string.h>
#include <string>
#include "basic_structs.h"
using namespace std;

class Parser {
private:
//    Parser(std::__cxx11::basic_string<char> commit_hash);

    Patch patch{};
    FileChange * cur_file{};
    int cur_ori_num{};
    int cur_fin_num{};
    string commit_hash{};
    void deal_with_one_line(int ident_id, char * st);
    bool hit_identifier(char * op_buffer, int & ident_id);
    void Parse_patch_git_info(string str);
    void parse_line_num(int & ori_num, int & fin_num, char * cha);
    void parse_line_num(int & ori_num, int fin_num, char * cha);
public:
    Parser(string commit_hash);
    Parser(string commit_hash1, string commit_hash2);
};


#endif //PATCHTOOL_PARSER_H
