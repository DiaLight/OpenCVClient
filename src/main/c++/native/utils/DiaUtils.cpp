//
// Created by dialight on 16.01.17.
//

#include "utils/DiaUtils.hpp"

using namespace std;

void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector<string> strSplit(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

PairStr strCut(const string &s, char delim) {
    vector<string> elems;
    size_t colonPos = s.find(delim);

    if (colonPos != string::npos) {
        return PairStr(s.substr(0, colonPos), s.substr(colonPos + 1));
    }
    return PairStr(s, "");
}
