//
// Created by xwan on 8/1/19.
//
#include <iostream>
#include <string>
#define INFINITY 65535
using namespace std;

const int identifier_size = 11;
string identifiers[identifier_size] = {
         "+++", "---","+", "-",
        " ", "@@", "new file mode",
         "Binary files","diff --git",
        "\\No newline at the end of file", "index"
};


void char_star_assign(string input, char * str) {
    for (int i = 0; i < input.length(); i++ ) {
        str[i] = input[i];
        str[i + 1] = '\0';
    }
}

// int parse_ident(string str, char * op, char * st, int index) {
//     int ret_val = INFINITY;
//     for (int i = index; i < str.length(); i++) {
//         if (str[i] == '+') {
//             if (str.substr(i, i + 3).compare("+++") == 0) {
//                 ret_val = 0;
//                 char_star_assign("+++", op);
//                 char_star_assign(str.substr(), st);
//             }


//             ret_val = (str.substr(i, i + 2).compare("+++") == 0) ? 0 : 2;
            
//             st = str.substr(i + 4, str.find('\n'))
//         } else if (str[i] == '-') {
//             ret_val = (str.substr(i, i + 2).compare("---") == 0) ? 1 : 3;
//         }
//     }
// }


int main(int argc, char const *argv[]) {
    string a = "we are the world";
    string b = a.substr(5,7);
    char c[5];
    char_star_assign("qqq", c);

    cout << b << endl;
    cout << c << endl;

    return 0;
}

