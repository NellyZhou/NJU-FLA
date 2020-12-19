//
//  my_exception.h
//  turing
//
//  Created by 周心瑜 on 2020/12/20.
//

#ifndef my_exception_h
#define my_exception_h
using namespace std;
#include <string>
#include <iostream>

class MyException{
    string msg;
public:
    MyException(){
        msg = "syntax error";
    }
    
    MyException(string x){
        msg = x;
    }

    void what(){
        cout << msg << endl;
        exit(0);
    }

};

#endif /* my_exception_h */
