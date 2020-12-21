//
//  my_exception.h
//  turing
//
//  Created by 周心瑜 on 2020/12/20.
//

#ifndef my_exception_h
#define my_exception_h

#include <string>
#include <iostream>

using namespace std;

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
        exit(1);
    }

};

#endif /* my_exception_h */
