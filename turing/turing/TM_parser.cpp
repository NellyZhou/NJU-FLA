//
//  TM_parser.cpp
//  turing
//
//  Created by 周心瑜 on 2020/12/19.
//

#include "TM_parser.hpp"
#include "parser_help.hpp"
#include <fstream>
#include <regex>
#include <stdlib.h>
#include <string.h>

#define variable_Q state_group
#define variable_S input_symbol_group
#define variable_G tape_symbol_group
#define variable_q0 initial_state
#define variable_B blank_symbol
#define variable_F final_state_group
#define variable_N tape_number

#define proccess_Q(a)\
    (regex_match(a, regex("[a-zA-Z0-9_]+")) == true)? a:throw(MyException())
//    (regex_match(a, regex("[a-zA-Z0-9_]+")) == true)? a:(throw(MyException()))

#define proccess_S(a)\
    ((a.length() == 1) && regex_match(a.substr(0,1), regex("[^,;{}*_]")))? a[0]:throw(MyException())

#define proccess_G(a)\
    ((a.length() == 1) && regex_match(a.substr(0,1), regex("[^,;{}*]")))? a[0]:(throw(MyException()))

#define proccess_q0(a)\
    (regex_match(a, regex("[a-zA-Z0-9_]+")))? a:(throw(MyException()))

#define proccess_B(a)\
    ((a.length() == 1) && (a[0] == '_'))? a[0]:(throw(MyException()))

#define proccess_F(a)\
    (regex_match(a, regex("[a-zA-Z0-9_]+")))? a:(throw(MyException()))

#define proccess_N(a) atoi(&a[0])

Parser::Parser(string prog_name){
    fstream in_file;
    string file_pwd = "/users/zhouxinyu/workspace/fla_project/turing/turing/";
    in_file.open(file_pwd + prog_name);
    cout<<prog_name<<endl;
    while (!in_file.fail()){
        string line_str;
        getline(in_file, line_str);
        if (!line_str.empty() && line_str[0] != ';'){
            parse_certain_line(line_str);
        }
    }
}

void Parser::parse_certain_line(string line){
    try{
        if (line[0] != '#')
            return;
        if (line.length() >= 2){
            switch (line[1]) {
                case 'Q': clean_Q(line); break;
                case 'S': clean_S(line); break;
                case 'G': clean_G(line); break;
                case 'q': clean_q0(line); break;
                case 'B': clean_B(line); break;
                case 'F': clean_F(line); break;
                case 'N': clean_N(line); break;
                default: throw(MyException()); break;
            }
        } else {
            throw(MyException());
        }
    }
    catch(MyException err){
        err.what();
    }
}

void Parser::show(){
    printf("State_group:\n");
    for (int i = 0; i < state_group.size(); i++){
        cout<<'\t'<<state_group[i]<<endl;
    }
}

make_parse_group_func(Q)
make_clean_group_func(Q)

make_parse_group_func(S)
make_clean_group_func(S)

make_parse_symbol_func(B)
make_clean_symbol_func(B)

make_parse_group_func(F)
make_clean_group_func(F)

make_parse_group_func(G)
make_clean_group_func(G)

make_parse_symbol_func(N)
make_clean_symbol_func(N)

make_parse_symbol_func(q0)
make_clean_symbol_func(q0)



