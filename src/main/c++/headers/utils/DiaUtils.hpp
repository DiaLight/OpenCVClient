//
// Created by dialight on 16.01.17.
//

#ifndef OPENCVCLIENT_DIAUTILS_HPP
#define OPENCVCLIENT_DIAUTILS_HPP

#include <string>
#include <sstream>
#include <vector>


struct pair_str_t {
    std::string first;
    std::string second;
    pair_str_t(std::string first, std::string second) : first(first), second(second) {}
};
typedef struct pair_str_t PairStr;


void split(const std::string &s, char delim, std::vector<std::string> &elems);


std::vector<std::string> strSplit(const std::string &s, char delim);
PairStr strCut(const std::string &s, char delim);


#endif //OPENCVCLIENT_DIAUTILS_HPP
