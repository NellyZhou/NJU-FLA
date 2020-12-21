//
//  TM_simulator.cpp
//  turing
//
//  Created by 周心瑜 on 2020/12/20.
//

#include "TM_simulator.hpp"

Simulator::Simulator(Parser* tm_parser, string input){
    my_tm_parser = tm_parser;
    tape_num = my_tm_parser->tape_number;
    cur_state = my_tm_parser->initial_state;
    is_halt = false;

    bool flag = input_verification(input);
    try{
        if (!flag)
            throw(MyException("illegal input"));
    }
    catch(MyException err){
        err.what();
    }

    build_tape(0, input);
    for (int i = 1; i < tape_num; i++){
        string str = "";
        build_tape(i, str);
    }
}

void Simulator::build_tape(int index, string content){
    Node* p = (Node*)malloc(sizeof(Node));

    if (content == ""){
        p->symbol = my_tm_parser->blank_symbol;
        p->p_front = NULL;
        p->p_back = NULL;
        tape_head.push_back(p);
        tape_leftmost.push_back(p);
        tape_rightmost.push_back(p);
        return;
    }
    
    string str = content;
    p->symbol = str[0];
    p->p_front = NULL;
    p->p_back = NULL;
    tape_head.push_back(p);
    tape_leftmost.push_back(p);

    Node* pre_p = p;
    for (int i = 1; i < str.length(); i++){
        p = (Node*)malloc(sizeof(Node));
        p->symbol = str[i];
        p->p_back = NULL;
        pre_p->p_back = p;
        p->p_front = pre_p;
        pre_p = p;
    }
    tape_rightmost.push_back(p);
    return;
}

bool Simulator::input_verification(string input){
    string str = input;
    for (int i = 0; i < str.length(); i++){
        if (!my_tm_parser->is_in_input_symbols(str[i]))
            return false;
    }
    return true;
}

void Simulator::tm_next_step(){
    string cur_symbols = get_symbols();
    //printf("Current state is {%s}, symbols are {%s}\n", cur_state.c_str(), cur_symbols.c_str());
    vector<string> ans_set = my_tm_parser->transition_function(cur_state, cur_symbols);
    if (ans_set.empty()){
        is_halt = true;
        return;
    }
    string new_symbols = ans_set[0];
    string new_direction = ans_set[1];
    string new_state = ans_set[2];

    cur_state = new_state;
    for (int i = 0; i < tape_num; i++){
        tape_head[i]->symbol = new_symbols[i];
        if (new_direction[i] == 'r'){
            if (tape_head[i]->p_back == NULL){
                Node* p = tape_head[i];
                Node* tmp_p = (Node*)malloc(sizeof(Node));
                p->p_back = tmp_p;
                tmp_p->symbol = my_tm_parser->blank_symbol;
                tmp_p->p_front = p;
                tmp_p->p_back = NULL;
                tape_head[i] = tmp_p;
                tape_rightmost[i] = tmp_p;
            } else{
                tape_head[i] = tape_head[i]->p_back;
            }
        } if (new_direction[i] == 'l'){
            if (tape_head[i]->p_front == NULL){
                Node* p = tape_head[i];
                Node* tmp_p = (Node*)malloc(sizeof(Node));
                p->p_front = tmp_p;
                tmp_p->symbol = my_tm_parser->blank_symbol;
                tmp_p->p_back = p;
                tmp_p->p_front = NULL;
                tape_head[i] = tmp_p;
                tape_leftmost[i] = tmp_p;
            } else{
                tape_head[i] = tape_head[i]->p_front;
            }
        }
    }
}

string Simulator::get_symbols(){
    string str = "";
    for (int i = 0; i < tape_num; i++){
        str = str + tape_head[i]->symbol;
    }
    return str;
}

void Simulator::tm_start(){
    while (!is_halt){
/*
        printf("\n---moveing---\n");
        for (int i = 0; i < tape_num; i++){
            tape_result(i);
        }
  */
        tm_next_step();
    }
    //printf("TM FINISHED!\n");
}

void Simulator::tape_result(int index){
    Node* p = tape_leftmost[index];
    while (p->p_back != NULL){
        if (p->symbol == my_tm_parser->blank_symbol){
            p = p->p_back;
        } else{
            break;
        }
    }
    Node* p_end = tape_rightmost[index];
    while ((p_end->p_front != NULL) && (p_end != p)){
        if (p_end->symbol == my_tm_parser->blank_symbol){
            p_end = p_end->p_front;
        } else{
            break;
        }
    }
    while (p != p_end){
        printf("%c", p->symbol);
        p = p->p_back;
    }
    printf("%c\n", p->symbol);
}