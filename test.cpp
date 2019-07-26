#include "basic_structs.h"
#include <iostream>
#include <string>
#define INFTY = 65535
using namespace std;

/* Improvement that can be made:
 * 1. Look-back methods are used in parser. This can be 
 * changed to look-forward method
 * 2. Nothing is done until a line of statement is made.
 * This can be improved by directly locate the Enter 
 * character and push it to the dealer after identifier
 * is made.*/

const int identifier_size = 11;

Patch patch;

string identifiers[identifier_size] = {
    "+", "-", "diff --git",
    "+++", "---", "new file mode", 
    " ", "@@", "Binary files",
    "\\No newline at the end of file", "index"
};

void deal_with_one_line(int ident_id, char * st){
    switch (ident_id){
        case 0:
            
            break;
        
        default:
            break;
    }
}

bool hit_identifier(char * op_buffer, int & ident_id) {
    for (int i = 0; i < identifier_size; i++) {
        if (identifiers[i].compare(op_buffer)) {
            ident_id = i;
            return true;
        }
    }
    ident_id = INFTY;
    return false;
}

string parse_patch_git_info(string str) {
    char * op_buffer = new char[32];    // buffer for operator
    int ident_id = INFTY;
    char * st_buffer = new char[128];   // buffer for statement
    int op_buf_size = 0;
    int st_buf_size = 0;
    int ptr = 0
    for(int i = 0; i < str.length(); i++) {
        if (str[i] == '\n') {
            deal_with_one_line(ident_id, st_buffer);
            op_buffer[0] = '\0';
            st_buffer[0] = '\0';
            op_buf_size = 0; 
            st_buf_size = 0;
        } else {
            switch (ptr)
            {
            case 0:
                op_buffer[op_buf_size] = str[i];
                op_buffer[++op_buf_size] = '\0';
                if hit_identifier(op_buffer, ident_id) {
                    ptr = 1;
                }
                break;
            case 1:
                st_buffer[st_buf_size] = str[i];
                st_buffer[++st_buf_size] = '\0';
            default:
                break;
            }
        }
    }
}


int main(int argc, char const *argv[]) {
    string git_info = exec("git diff bf757b5 2d975eda ");
    cout << git_info << endl;
}
