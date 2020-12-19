//
//  parser_help.hpp
//  turing
//
//  Created by 周心瑜 on 2020/12/19.
//

#ifndef parser_help_hpp
#define parser_help_hpp

#include "my_exception.h"
#include <stdio.h>
#include <string>
#include <sstream>
#define concat2(a,b) a ## b
using namespace std;

typedef void (*func_name)(string input);

//macro for line clean
#define make_func(name)                             \
    void name(string input)

#define make_clean_symbol_func(name)                \
    make_func(concat2(Parser::clean_,name))         \
    {                                               \
    try{                                            \
        if (input.length() < 6){                    \
            throw(MyException());                   \
        }                                           \
        input.erase(0, 5);                          \
        if (input[0] == ' ')                        \
            input.erase(0,1);                       \
        if (!input.empty()){                        \
            concat2(parse_,name)(input);            \
        }                                           \
    }                                               \
    catch(MyException err){                         \
        err.what();                                 \
    }                                               \
    }

#define make_clean_group_func(name)                 \
    make_func(concat2(Parser::clean_,name))         \
    {                                               \
    try{                                            \
        if (input.length() < 6){                    \
            throw(MyException());                   \
        }                                           \
        input.erase(0, 6);                          \
        input.pop_back();                           \
        for (int i = 0; i < input.length(); i++){   \
            if (input[i] == ',')                    \
                input[i] = ' ';                     \
        }                                           \
        if (!input.empty()){                        \
            concat2(parse_,name)(input);            \
        }                                           \
    }                                               \
    catch(MyException err){                         \
        err.what();                                 \
    }                                               \
    }

#define make_parse_symbol_func(name)                                \
    make_func(concat2(Parser::parse_, name))                        \
    {                                                               \
    try{                                                            \
        concat2(variable_, name) = concat2(proccess_, name)(input); \
    }                                                               \
    catch(MyException err){                                         \
        err.what();                                                 \
    }                                                               \
    }

#define make_parse_group_func(name)                                         \
    make_func(concat2(Parser::parse_, name))                                \
    {                                                                       \
    try{                                                                    \
        istringstream istr(input);                                          \
        string s;                                                           \
        while (istr >> s){                                                  \
            concat2(variable_, name).push_back(concat2(proccess_, name)(s));\
        }                                                                   \
    }                                                                       \
    catch(MyException err){                                                 \
        err.what();                                                         \
    }                                                                       \
    }

#endif /* parser_help_hpp */
