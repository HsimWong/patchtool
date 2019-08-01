//
// Created by xwan on 8/1/19.
//
#include <iostream>
#include <string>
#include <cstdio>
#define INFINITY 65535
using namespace std;

const int identifier_size = 11;
string identifiers[identifier_size] = {
         "+++", "---","+", "-",
        " ", "@@", "new file mode",
         "Binary files","diff --git",
        "\\No newline at the end of file", "*index"
};

void char_star_assign(string input, char * str) {
    for (int i = 0; i < input.length(); i++ ) {
        str[i] = input[i];
    }
    str[input.length()] = '\0';
}



/* Duplicated part can be modulized to a function
 * Do it later. 15:21, 1, Aug, 2019*/
int parse_ident(string str, char * op, char * st, int *index) {
    int ret_val = INFINITY;
    int st_length = INFINITY;
//    printf("%d\n", index);
    // // *index++;
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
            st_length = str.substr(i).find('\n')-i-2;
            char_star_assign(str.substr(i + 2, st_length), st);
            *index += (st_length + 3);
            return 5;
        case ' ':
            char_star_assign(" ", op);
            st_length = str.substr(i).find('\n')-i-1;
            char_star_assign(str.substr(i + 2, st_length), st);
            *index += (st_length + 3);
            return 4;
        default:
            st_length = str.substr(i).find('\n')-i;
            char_star_assign(str.substr(i,st_length), st);
            *index += (st_length);
            return INFINITY;
        }
    }
    return INFINITY;
}


int main(int argc, char const *argv[]) {
    string str= "+1234567879\n@@ 123456\n 12345\n--- 123456\n";
    char op[32];
    char st[512];
    int index = 12;
//    cout << str[11] << endl;
//    *index = 0;
//    printf("%d\n", index);
//    printf("%d\n", &index);
    int ret = parse_ident(str, op, st, &index);
    printf("ret:%d, \nop:%s, \nst:%s, \n*index:%d", ret, op, st, index);

    return 0;
}

