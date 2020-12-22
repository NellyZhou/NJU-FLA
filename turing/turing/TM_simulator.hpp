//
//  TM_simulator.hpp
//  turing
//
//  Created by 周心瑜 on 2020/12/20.
//

#ifndef TM_simulator_hpp
#define TM_simulator_hpp

#include "TM_parser.hpp"
#include <stdio.h>
#include <vector>
#include <string>

struct Node{
    Node* p_front;
    Node* p_back;
    char symbol;
};

class Simulator{
public:
    Parser* my_tm_parser;
    int tape_num;
    string cur_state;
    vector<Node*> tape_head;
    vector<Node*> tape_most;
    //vector<Node*> tape_rightmost;
    vector<Node*> tape_zero;
    bool is_halt;
    bool is_verbose;
    
    Simulator();
    Simulator(Parser* tm_parser, string input, bool flag);
    void build_tape(int index, string content);
    bool input_verification(string input);
    void tm_next_step();
    void tm_start();
    string get_symbols();
    void tape_result(int index);
    void show_step_info(int steps);
    void show_final_result();
};


#endif /* TM_simulator_hpp */
