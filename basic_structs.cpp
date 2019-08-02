#ifndef BASIC_STRUCTS_CPP
#define BASIC_STRUCTS_CPP

#include <string>
#include <list>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <array>
#include <unistd.h>
#include <bits/stdc++.h>
using namespace std;



string exec_cmd(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose) > pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}



#endif