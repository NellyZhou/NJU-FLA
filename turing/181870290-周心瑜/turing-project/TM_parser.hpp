//
//  TM_parser.hpp
//  turing
//
//  Created by 周心瑜 on 2020/12/19.
//

#ifndef TM_parser_hpp
#define TM_parser_hpp

#include "parser_help.hpp"
#include <vector>
#include <fstream>
#include <unistd.h>
#include <regex>
#include <stdlib.h>

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
    int delta_function_fd;
    char delta_function_file[];
    
    Parser();
    Parser(string prog_filename);
    void parse_certain_line(string line);

    func_about_variable(clean_)
    func_about_variable(parse_)
    
    
    vector<string> transition_function(string old_state, string old_symbols);
    // new symbols ## direction ## state
    void write_temp_file(char* buffer, int length);
    char* read_rule_line(int* length, int index);
    int transition_number();
    void initial_transition_file();
    void show_transition_rule();
    void show();
    bool is_in_input_symbols(char ch);
    bool is_in_tape_symbols(string str);
    bool is_in_state_group(string cur_state);
    bool is_in_final_state_group(string cur_state);
    bool is_in_form_of_five_tuple(string line);
    
    ~Parser();
};

#endif /* TM_parser_hpp */
