#include "basic_structs.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[]) {
    string git_info = exec("git diff bf757b5e131383 836b212f7ec5667fc32bfad1a2cf737296b41973");
    cout << git_info << endl;
}
