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
    vector<Node*> tape_leftmost;
    vector<Node*> tape_rightmost;
    bool is_halt;
    
    Simulator();
    Simulator(Parser* tm_parser, string input);
    void build_tape(int index, string content);
    bool input_verification(string input);
    void tm_next_step();
    void tm_start();
    string get_symbols();
    void tape_result(int index);
};


#endif /* TM_simulator_hpp */
