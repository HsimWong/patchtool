#ifndef PARSER_H
#define PARSER_H
#include "Parser.h"
#include "basic_structs.h"
#include <string>
using namespace std;

class Parser {
private:
    Patch patch;
    FileChange * cur_file;
    int cur_ori_num;
    int cur_fin_num;
    string commit_hash;
    void deal_with_one_line(int ident_id, char * st);
    bool hit_identifier(char * op_buffer, int & ident_id);
    void Parse_patch_git_info(string str);
    parse_line_num(int & ori_num, int & fin_num, char * cha)
    void parse_line_num(int & ori_num, int fin_num, char * cha);
public:
    Parser(string commit_hash);
    Parser(string commit_hash1, string commit_hash2);
};

#endif