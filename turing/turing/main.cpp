//
//  main.cpp
//  turing
//
//  Created by 周心瑜 on 2020/12/19.
//

#include "TM_parser.hpp"
#include "TM_simulator.hpp"
#include <string>
#include <iostream>
using namespace std;


int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Hello, World!\n";
    string filename = argv[1];
    Parser my_parser(filename);
    my_parser.show();
    string input = argv[2];
    Simulator my_simulator(&my_parser, input);
    
    return 0;
}
