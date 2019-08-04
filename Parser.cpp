//
// Created by xwan on 7/31/19.
//

#include "Parser.h"
#include <string>
#include <iostream>
#include <vector>

#define INFTY 65535
using namespace std;


/* Improvement that can be made:
 * 1. Look-back methods are used in Parser. This can be
 * changed to look-forward method
 * 2. Nothing is done until a line of statement is made.
 * This can be improved by directly locate the Enter
 * character and push it to the dealer after identifier
 * is made.*/

const int identifier_size = 11;

string identifiers[identifier_size] = {
         "+++", "---","+", "-",
        " ", "@@", "new file mode",
         "Binary files","diff --git",
        "\\No newline at the end of file", "index"
};


Parser::Parser(string commit_hash) {
    this->cur_ori_num = 1;
    this->cur_fin_num = 1;
    this->commit_hash = commit_hash;
    this->patch = *(new Patch);
    this->patch.file_changes = *(new vector<FileChange *>);
    this->patch.commit_hash = commit_hash;
    string cmd = "git diff " + commit_hash;
    string git_info = exec_cmd((cmd.c_str()));
    this->Parse_patch_git_info(git_info);
}

Parser::Parser(string commit_hash1, string commit_hash2) {
    this->cur_ori_num = 1;
    this->cur_fin_num = 1;
    this->patch = *(new Patch);
    this->patch.file_changes = *(new vector<FileChange *>);
    this->commit_hash = commit_hash;
    this->patch.commit_hash = commit_hash;
    string cmd = "git diff " + commit_hash1 + " " + commit_hash2;
    this->Parse_patch_git_info(exec_cmd(cmd.c_str()));
}

void char_star_assign(string input, char * str) {
    for (int i = 0; i < input.length(); i++ ) {
        str[i] = input[i];
    }
    str[input.length()] = '\0';
}

int parse_ident(string str, char * op, char * st, int *index) {
    int ret_val = INFTY;
    int st_length = INFTY;
    for (int i = *index; i < str.length(); i++) {
        switch (str[i]) {
        case '+':
            if (str.substr(i, 3).compare("+++") == 0) {
                char_star_assign("+++", op);
                st_length = str.substr(i).find('\n') + 1;
                char_star_assign(str.substr(i + 4, st_length-5), st);
                *index = *index + (st_length);
                return 0;
            } else {
                cout << "index" << *index << endl;
                char_star_assign("+", op);
                st_length = str.substr(i).find('\n');
                cout << "stlength" << st_length << endl;
                char_star_assign(str.substr(i + 1, st_length-1), st);
                *index += (st_length + 1);
                return 2;
            }
            break;
        case '-':
            if (str.substr(i, 3).compare("---") == 0) {
                char_star_assign("---", op);
                st_length = str.substr(i).find('\n') + 1;
                char_star_assign(str.substr(i + 4, st_length-5), st);
                *index = *index + (st_length);
                return 1;
            } else {
                cout << "index" << *index << endl;
                char_star_assign("-", op);
                st_length = str.substr(i).find('\n');
                cout << "stlength" << st_length << endl;
                char_star_assign(str.substr(i + 1, st_length-1), st);
                *index += (st_length + 1);
                return 3;
            }
            break;
        case '@':
            char_star_assign("@@", op);
            st_length = str.substr(i).find('\n');
            cout << st_length << endl;

            char_star_assign(str.substr(i + 3, st_length - 3), st);
            *index += (st_length + 1);
            return 5;
        case ' ':
            cout << "index" << *index << endl;
            char_star_assign(" ", op);
            st_length = str.substr(i).find('\n');
            cout << "stlength" << st_length << endl;
            char_star_assign(str.substr(i + 1, st_length-1), st);
            *index += (st_length + 1);
            return 4;
        default:
            st_length = str.substr(i).find('\n');
            char_star_assign(str.substr(i,st_length), st);
            *index += (st_length+1);
            return INFTY;
        }
    }
    return INFTY;
}

void Parser::Parse_patch_git_info(string str) {
//    char * op = new char[8];
//    char * st = new char[128];
    int op_code = INFTY;
    int start_ind = 0;
    while (start_ind != (str.length())) {
        char * op = new char[8];
        char * st = new char[128];
        if (this->patch.file_changes.size() != 0) {
            cout << this->patch.file_changes[this->patch.file_changes.size() - 1]->orig_dir << endl;

        }
        op_code = parse_ident(str, op, st, &start_ind);
        if (this->patch.file_changes.size() != 0) {
            cout << this->patch.file_changes[this->patch.file_changes.size() - 1]->orig_dir << endl;

//            cout << (*(this->patch.file_changes.rbegin()))->orig_dir << endl;
        }
        this->deal_with_one_line(op_code, st);
        if (this->patch.file_changes.size() != 0) {
            cout << this->patch.file_changes[this->patch.file_changes.size() - 1]->orig_dir << endl;
//            cout << (*(this->patch.file_changes.rbegin()))->orig_dir << endl;
        }
    }
}

/* Function here uses if-else rather than switch
 * for switch only allows one declaration */
void Parser::deal_with_one_line(int ident_id, char * st){

    if (ident_id == 1) {        // ---
        FileChange fc = {};
        fc.linechanges = *(new vector<LineChange *>);
        vector<char *> lst = *(new vector<char *>);
        lst.push_back("hello, world");
        this->patch.file_changes.push_back(&fc);
        string tmp(st);
        fc.orig_dir = tmp;
//        this->patch.file_changes.push_back(&fc);
        cout << "((this->patch.file_changes.size()))" << ((this->patch.file_changes.size())) << endl;
        cout << (*(this->patch.file_changes.rbegin()))->orig_dir << endl;
        fc.final_dir = "";
        return;
    } else if (ident_id == 0) { // +++
        cout << (*(this->patch.file_changes.end())-1)->orig_dir << endl;
        cout << (*(this->patch.file_changes.rbegin()))->final_dir << endl;
        string tmp(st);
        (*(this->patch.file_changes.rbegin()))->final_dir = tmp;
        return;
    } else if (ident_id == 2) { // +
        LineChange lc = *(new LineChange);
        lc = {(*(this->patch.file_changes.rbegin()))->orig_dir,
              (*(this->patch.file_changes.rbegin()))->final_dir,
              this->cur_ori_num,
              this->cur_fin_num,
              1,
              st,
              this->commit_hash};
        this->cur_fin_num += 1;
        (*(this->patch.file_changes.rbegin()))->linechanges.push_back(&lc);
        return;
    } else if (ident_id == 3) { // '-'
        LineChange lc = *(new LineChange);
        lc = {(*(this->patch.file_changes.rbegin()))->orig_dir,
              (*(this->patch.file_changes.rbegin()))->final_dir,
              this->cur_ori_num,
              this->cur_fin_num,
              -1,
              st,
              this->commit_hash};
        this->cur_ori_num += 1;
        (*(this->patch.file_changes.rbegin()))->linechanges.push_back(&lc);
        return;
    } else if (ident_id == 4) {  // ' '
        LineChange lc = *(new LineChange);
        lc.ori_file_dir = (*(this->patch.file_changes.rbegin()))->orig_dir;
        lc.final_dir = (*(this->patch.file_changes.rbegin()))->final_dir;
        lc.inserted_line_num = this->cur_ori_num;
        lc.result_line_num = cur_fin_num;
        lc.if_inserted = 0;
        lc.line_content = st;
        lc.commit_hash = this->commit_hash;

        this->cur_ori_num += 1;
        this->cur_fin_num += 1;
        (*(this->patch.file_changes.rbegin()))->linechanges.push_back(&lc);
        return;
    } else {
        if (ident_id == 5) { // @@
            FileChange fc = *(new FileChange);
            fc.linechanges = *(new vector<LineChange *>);
            fc.orig_dir = (*(this->patch.file_changes.rbegin()))->orig_dir;
            this->parse_line_num(this->cur_ori_num, this->cur_fin_num, st);
        }
    }
}

int fetch_int(char * cha, int & i) {
    string start_num = "";
    for (int j = i + 1; cha[i] != 0; j++) {
        if (cha[j] == ',') {
            return stoi(start_num);
        } else {
            start_num += cha[j];
        }
        i = j;
    }
}

void Parser::parse_line_num(int & ori_num, int & fin_num, char * cha) {
    for (int i = 0; cha[i] != '\0'; i++) {
        if (cha[i] == '-') {
            ori_num = fetch_int(cha, i);
        } else if (cha[i] == '+') {
            fin_num = fetch_int(cha, i);
            break;
        } else {
            continue;
        }
    }
}

