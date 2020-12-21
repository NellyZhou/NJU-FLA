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
    vector<Node*> tape_head;
    vector<Node*> tape_leftmost;
    vector<Node*> tape_rightmost;
    
    Simulator();
    Simulator(Parser* tm_parser, string input);
    bool input_verification(string input);
    void tm_next_step();
    bool is_tm_halt();
};


#endif /* TM_simulator_hpp */
