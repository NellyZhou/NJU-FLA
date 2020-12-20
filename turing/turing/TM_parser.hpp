//
//  TM_parser.hpp
//  turing
//
//  Created by 周心瑜 on 2020/12/19.
//

#ifndef TM_parser_hpp
#define TM_parser_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "parser_help.hpp"
using namespace std;

#define func_about_variable(name) \
    make_func(concat2(name,Q));  \
    make_func(concat2(name,S));  \
    make_func(concat2(name,G));  \
    make_func(concat2(name,q0));  \
    make_func(concat2(name,B));  \
    make_func(concat2(name,F));  \
    make_func(concat2(name,N));

class Parser{
public:
    vector<string> state_group;
    vector<char> input_symbol_group;
    vector<char> tape_symbol_group;
    string initial_state;
    char blank_symbol;
    vector<string> final_state_group;
    int tape_number;
    char delta_function_file[];
    
    Parser();
    Parser(string prog_filename);
    void parse_certain_line(string line);

    func_about_variable(clean_)
    func_about_variable(parse_)
    
    vector<string> transition_function(string old_state, string old_symbols);
    void show();
};

#endif /* TM_parser_hpp */
