//
//  main.cpp
//  turing
//
//  Created by 周心瑜 on 2020/12/19.
//

#include <iostream>
#include "TM_parser.hpp"
//#include "TM_simulator.hpp"
using namespace std;


int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Hello, World!\n";
    Parser tm1("palindrome_detector_2tapes.tm");
    tm1.show();
    
    return 0;
}
