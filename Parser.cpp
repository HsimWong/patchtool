//
// Created by xwan on 7/31/19.
//

#include "Parser.h"
#define INFTY 65535

 * 1. Look-back methods are used in Parser. This can be
 * This can be improved by directly locate the Enter
        "+", "-", "diff --git",
        "+++", "---", "new file mode",
        " ", "@@", "Binary files",
        "\\No newline at the end of file", "index"
Parser::Parser(string commit_hash) {
    this -> cur_ori_num = 1;
    this -> cur_fin_num = 1;
    this -> commit_hash = commit_hash;
    this->patch.commit_hash = commit_hash;
    string cmd = "git diff " + commit_hash;
    this->Parse_patch_git_info(exec((cmd).c_str()));
}
Parser::Parser(string commit_hash1, string commit_hash2) {
    this -> cur_ori_num = 1;
    this -> cur_fin_num = 1;
    this -> commit_hash = commit_hash;
    this->patch.commit_hash = commit_hash;
    string cmd = "git diff " + commit_hash1 + " " + commit_hash2;
    this->Parse_patch_git_info(exec(cmd.c_str()));
void Parser::Parse_patch_git_info(string str) {
    char * op_buffer = new char[32];    // buffer for operator
    int ident_id = INFTY;
    char * st_buffer = new char[512];   // buffer for statement
    int op_buf_size = 0;
    int st_buf_size = 0;
    int ptr = 0;
    for(int i = 0; i < str.length(); i++) {
        if (str[i] == '\n') {
            deal_with_one_line(ident_id, st_buffer);       // Process this line when it's over
            op_buffer[0] = '\0';                           // Clear the buffers
            st_buffer[0] = '\0';
            op_buf_size = 0;
            st_buf_size = 0;
            switch (ptr)
            {
                case 0:
                    op_buffer[op_buf_size] = str[i];
                    op_buffer[++op_buf_size] = '\0';
                    if (hit_identifier(op_buffer, ident_id)) {
                        ptr = 1;
                    }
                    break;
                case 1:
                    st_buffer[st_buf_size] = str[i];
                    st_buffer[++st_buf_size] = '\0';
                    // if ((str[i] == '\n') || (str[i] == '\0')) {
                    //     this->deal_with_one_line(ident_id, st_buffer);
                    // }
                default:
                    break;
            }
    LineChange * l;
    switch (ident_id) {

            (*l) = {this->cur_file->orig_dir, this->cur_file->final_dir,
                    cur_ori_num, cur_fin_num, true, (string)st, this->commit_hash};
        case 1:         // -

            (*l) = {this->cur_file->orig_dir, this->cur_file->final_dir,
                    cur_ori_num, cur_fin_num, false, (string)st, this->commit_hash};

        case 3:         // +++
            this->cur_file->final_dir = ((string)st).substr(2);
            break;

            this->patch.file_changes.push_back(new_file);
int fetch_int(char * cha, int & i) {
    string start_num = "";
    for (int j = i + 1; cha[i] != 0; j++) {
        if (cha[j] == ',') {
            return stoi(start_num);
            i = j;
            start_num += cha[j];
        i = j;
void Parser::parse_line_num(int & ori_num, int & fin_num, char * cha) {
    for (int i = 0; cha[i] != '\0'; i++) {
        if (cha[i] == '+') {
            ori_num = fetch_int(cha, i);
        } else if (cha[i] == '-') {
            fin_num = fetch_int(cha, i);
            break;
        } else {
            continue;
        }
    }
