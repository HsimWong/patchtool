#include "basic_structs.h"
#include "Parser.h"
#include <iostream>
#include <string>
#define INFTY = 65535
#define ELMIMINATED = -1
using namespace std;

/* Improvement that can be made:
 * 1. Look-back methods are used in Parserr. This can be 
 * changed to look-forward method
 * 2. Nothing is done until a line of statement is made.
 * This can be improved by directly locate the Enter 
 * character and push it to the dealer after identifier
 * is made.*/

const int identifier_size = 11;

string identifiers[identifier_size] = {
    "+", "-", "diff --git",
    "+++", "---", "new file mode", 
    " ", "@@", "Binary files",
    "\\No newline at the end of file", "index"
};





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
}

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
        } else {
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
        }
    }  
}

void Parser::deal_with_one_line(int ident_id, char * st){
    switch (ident_id){
        LineChange * l;
        case 0:         // +

            (*l) = {this->cur_file->orig_dir, this->cur_file->final_dir, 
                        cur_ori_num, cur_fin_num, true, (string)st, this->commit_hash};
            (*(patch.file_changes.end())).linechanges.push_back((*l);
            this->cur_fin_num += 1;
            break;

        case 1:         // -  

            (*l) = {this->cur_file->orig_dir, this->cur_file->final_dir, 
                        cur_ori_num, cur_fin_num, false, (string)st, this->commit_hash};
            (*(patch.file_changes.end())).linechanges.push_back((*l);
            /* Cur_ori_line_num & cur_fin_lin_num stay originally */
            this->cur_ori_num += 1;
            break;

        case 3:         // +++
            this->cur_file->final_dir = ((string)st).substr(2);
            break;

        case 4:         // ---
            FileChange new_file;
            new_file.final_dir = ((string)st).substr(2);
            this->patch.file_changes.push_back(new_file);
            this->cur_file = &new_file;
            break;

        case 6:         // normal lines, no addition and no deletion
            this->cur_ori_num += 1;
            break;

        case 7:         // @@
            this->parse_line_num(this->cur_ori_num, this->cur_fin_num, st);
            break;

        default:
            break;
    }
}

bool Parser::hit_identifier(char * op_buffer, int & ident_id) {
    for (int i = 0; i < identifier_size; i++) {
        if (identifiers[i].compare(op_buffer)) {
            ident_id = i;
            return true;
        }
    }
    ident_id = INFTY;
    return false;
}

int fetch_int(char * cha, int & i) {
    string start_num = "";
    for (int j = i + 1; cha[i] != 0; j++) {
        if (cha[j] == ',') {
            return stoi(start_num);
            i = j;
        } else {
            start_num += cha[j];
        }
        i = j;
    }
}

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
}

int main(int argc, char const *argv[]) {
    string git_info = exec("git diff bf757b5 2d975eda ");
    cout << git_info << endl;
}
