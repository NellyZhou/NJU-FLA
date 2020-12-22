//
//  TM_simulator.cpp
//  turing
//
//  Created by 周心瑜 on 2020/12/20.
//

#include "TM_simulator.hpp"

Simulator::Simulator(Parser* tm_parser, string input, bool flag){
    is_verbose = flag;
    my_tm_parser = tm_parser;
    tape_num = my_tm_parser->tape_number;
    cur_state = my_tm_parser->initial_state;
    is_halt = false;

    input_verification(input);
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
        tape_zero.push_back(p);
        tape_head.push_back(p);
        tape_most.push_back(p); //left
        tape_most.push_back(p); //right
        return;
    }
    
    string str = content;
    p->symbol = str[0];
    p->p_front = NULL;
    p->p_back = NULL;
    tape_head.push_back(p);
    tape_zero.push_back(p);
    tape_most.push_back(p); //left

    Node* pre_p = p;
    for (int i = 1; i < str.length(); i++){
        p = (Node*)malloc(sizeof(Node));
        p->symbol = str[i];
        p->p_back = NULL;
        pre_p->p_back = p;
        p->p_front = pre_p;
        pre_p = p;
    }
    tape_most.push_back(p); //right
    return;
}

bool Simulator::input_verification(string input){
    string str = input;
    for (int i = 0; i < str.length(); i++){
        if (!my_tm_parser->is_in_input_symbols(str[i])){
            if (!is_verbose){
                MyException err("illegal input");
                err.what();
            } else {
                fprintf(stderr,"Input: %s\n",input.c_str());
                fprintf(stderr,"==================== ERR ====================\n");
                fprintf(stderr,"error: '%c' was not declared in the set of input symbols\n",str[i]);
                fprintf(stderr,"Input: %s\n",input.c_str());
                fprintf(stderr,"       ");
                for(int j = 0; j < i; j++){
                   fprintf(stderr," "); 
                }
                fprintf(stderr,"^\n");
                fprintf(stderr,"==================== END ====================\n");
                exit(1);
            }
        }
    }
    if (is_verbose){
        fprintf(stderr,"Input: %s\n",input.c_str()); 
        fprintf(stderr,"==================== RUN ====================\n");  
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
                tape_most[i << 1 | 1] = tmp_p; //right
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
                tape_most[i << 1] = tmp_p; //left
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
    int steps = 0;
    while (!is_halt){
        show_step_info(steps);
        tm_next_step();
        steps++;
    }
    show_step_info(steps);
}

void Simulator::show_step_info(int steps){
    if (!is_verbose) return;
    printf("Step   : %d\n", steps);
    for (int i = 0; i < tape_num; i++){
        tape_result(i);
    }
    printf("State  : %s\n", cur_state.c_str());
    printf("---------------------------------------------\n");
}

void Simulator::tape_result(int index){
    Node* p_mid = tape_head[index];
    Node* p_begin = tape_most[index << 1]; //left
    Node* p_index = tape_zero[index];
    int head_index = 0;
    while (p_index != p_begin){
        p_index = p_index->p_front;
        head_index--;
    }
    while ((p_begin->p_back != NULL) && (p_begin != p_mid)){
        if (p_begin->symbol == my_tm_parser->blank_symbol){
            p_begin = p_begin->p_back;
            head_index++;
        } else{
            break;
        }
    }

    Node* p_end = tape_most[index << 1 | 1]; //right
    while ((p_end->p_front != NULL) && (p_end != p_mid)){
        if (p_end->symbol == my_tm_parser->blank_symbol){
            p_end = p_end->p_front;
        } else{
            break;
        }
    }
    //======================== Index =========================
    Node* p = p_begin;
    printf("Index%d : ", index);
    while (p != p_end){
        printf("%d ", head_index);
        head_index++;
        p = p->p_back;
    }
    printf("%d\n", head_index);

    //======================== Tape =========================
    p = p_begin;
    printf("Tape%d  : ", index);
    while (p != p_end){
        printf("%c ", p->symbol);
        p = p->p_back;
    }
    printf("%c\n", p->symbol);

    //======================== Head =========================
    p = p_begin;
    printf("Head%d  : ", index);
    while (p != p_mid){
        printf("  ");
        p = p->p_back;
    }
    printf("^\n");
}

void Simulator::show_final_result(){
    int index = 0;
    Node* p_mid = tape_head[index];
    Node* p_begin = tape_most[index << 1]; //left
    Node* p_index = tape_zero[index];
    while (p_index != p_begin){
        p_index = p_index->p_front;
    }
    while (p_begin->p_back != NULL){
        if (p_begin->symbol == my_tm_parser->blank_symbol){
            p_begin = p_begin->p_back;
        } else{
            break;
        }
    }

    Node* p_end = tape_most[index << 1 | 1]; //right
    while ((p_end->p_front != NULL) && (p_end != p_begin)){
        if (p_end->symbol == my_tm_parser->blank_symbol){
            p_end = p_end->p_front;
        } else{
            break;
        }
    }

    Node* p = p_begin;
    while (p != p_end){
        printf("%c", p->symbol);
        p = p->p_back;
    }
    printf("%c\n", p->symbol);
}