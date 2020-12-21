//
//  TM_simulator.cpp
//  turing
//
//  Created by 周心瑜 on 2020/12/20.
//

#include "TM_simulator.hpp"

Simulator::Simulator(Parser* tm_parser, string input){
    my_tm_parser = tm_parser;
    bool flag = input_verification(input);
    try{
        if (!flag)
            throw(MyException("illegal input"));
    }
    catch(MyException err){
        err.what();
    }

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
    
}

bool is_tm_halt(){
    
    return true;
}
