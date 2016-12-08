//
// Created by dialight on 04.11.16.
//

#ifndef OPENCVCLIENT_MACROENUMSTRING_HPP
#define OPENCVCLIENT_MACROENUMSTRING_HPP

#include <string>
#include <map>

using namespace std;

#define BEGIN_ENUM(HEAD) \
    enum HEAD {
#define ENUM_ITEM(ENUM, NAME) \
    ENUM,
#define END_ENUM };

#define BEGIN_MAP(HEAD) \
    static map<int, string> HEAD = {
#define MAP_ITEM(ENUM, NAME) \
    {ENUM, NAME},
#define END_MAP };

#define ENUM_STRING(MACRO, ENUM, METHOD) \
    BEGIN_ENUM(ENUM) \
        MACRO(ENUM_ITEM) \
    END_ENUM \
    BEGIN_MAP(METHOD) \
        MACRO(MAP_ITEM) \
    END_MAP

////Example usage
//#define MethodsMacro(m) \
//    m(FACE_DETECT, "Face detect") \
//    m(LINES, "Lines")
//ENUM_STRING(MethodsMacro, Methods, MethodsMap)
//
////it will create next structure:
//enum Methods {
//    FACE_DETECT,
//    LINES
//};
//vector<string> MethodsMap = {
//        "Face detect",
//        "Lines",
//};

//void __() {
//    map<int, string> MethodsMap = {
//            {BorderTypes::BORDER_DEFAULT, "hello"}
//    };
//}

#endif //OPENCVCLIENT_MACROENUMSTRING_HPP
