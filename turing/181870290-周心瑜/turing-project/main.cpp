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
    //cout << "Hello, World!\n";
    int index = 1;
    bool flag = false;
    if ((strcmp(argv[index], "-v") == 0) || (strcmp(argv[index], "--verbose") == 0)){
        flag = true;
        index++;
    }

    if ((strcmp(argv[index], "-h") == 0) || (strcmp(argv[index], "--help") == 0)){
        printf("usage: turing [-v|--verbose] [-h|--help] <tm> <input>\n");
        exit(0);
    }

    string filename = argv[index];
    Parser my_parser(filename);
    //cout<<"finished parsing"<<endl;
    //my_parser.show();
    string input = argv[index + 1];
    Simulator my_simulator(&my_parser, input, flag);

    my_simulator.tm_start();
    my_simulator.show_final_result();
    
    exit(0);
}
