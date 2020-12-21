//
//  TM_parser.cpp
//  turing
//
//  Created by 周心瑜 on 2020/12/19.
//

#include "TM_parser.hpp"
using namespace std;

#define variable_Q state_group
#define variable_S input_symbol_group
#define variable_G tape_symbol_group
#define variable_q0 initial_state
#define variable_B blank_symbol
#define variable_F final_state_group
#define variable_N tape_number

#define proccess_Q(a)\
    (regex_match(a, regex("[a-zA-Z0-9_]+")) == true)? a:throw(MyException())

#define proccess_S(a)\
    ((a.length() == 1) && regex_match(a.substr(0,1), regex("[^,;{}*_]")))? a[0]:throw(MyException())

#define proccess_G(a)\
    ((a.length() == 1) && regex_match(a.substr(0,1), regex("[^,;{}*]")))? a[0]:(throw(MyException()))

#define proccess_q0(a)\
    (regex_match(a, regex("[a-zA-Z0-9_]+")))? a:(throw(MyException()))

#define proccess_B(a)\
    ((a.length() == 1) && (a[0] == '_'))? a[0]:(throw(MyException()))

#define proccess_F(a)\
    (regex_match(a, regex("[a-zA-Z0-9_]+")))? a:(throw(MyException()))

#define proccess_N(a) atoi(&a[0])

Parser::Parser(string prog_name){
    fstream in_file;
    string file_pwd = "./";
    in_file.open(file_pwd + prog_name);
    
    strcpy(delta_function_file,"/tmp/temp_file.XXXXXX");
    delta_function_fd = mkstemp(delta_function_file);
    unlink(delta_function_file);
    
    while (!in_file.fail()){
        string line_str;
        getline(in_file, line_str);
        if (!line_str.empty() && line_str[0] != ';'){
            parse_certain_line(line_str);
        }
    }
}

void Parser::parse_certain_line(string line){
    try{
        if (line[0] != '#')
            return;
        if (line.length() >= 2){
            switch (line[1]) {
                case 'Q': clean_Q(line); break;
                case 'S': clean_S(line); break;
                case 'G': clean_G(line); break;
                case 'q': clean_q0(line); break;
                case 'B': clean_B(line); break;
                case 'F': clean_F(line); break;
                case 'N': clean_N(line); break;
                default: throw(MyException()); break;
            }
        } else {
            throw(MyException());
        }
    }
    catch(MyException err){
        err.what();
    }
}


void Parser::write_temp_file(char* buffer, int length) {
    int fd = delta_function_fd;
    lseek(fd, 0, SEEK_END);
    int line_len = length;
    write(fd, &line_len, sizeof(line_len));
    write(fd, buffer, line_len);
    
    lseek(fd, 0, SEEK_SET);
    int tmp_len;
    read(fd, &tmp_len, sizeof(tmp_len));
    
    lseek(fd, 0, SEEK_SET);
    int len = tmp_len + 1;
    write(fd, &len, sizeof(len));
}

char* Parser::read_rule_line(int* length, int index){
    int fd = delta_function_fd;
    int n = 0;
    lseek(fd, 0, SEEK_SET);
    read(fd, &n, sizeof(n));
    try{
        if (index >= n)
            throw(MyException("index out of range!"));
    }
    catch(MyException err){
        err.what();
    }

    for (int i = 0; i < index; i++){
        int tmp_len;
        read(fd, &tmp_len, sizeof(tmp_len));
        lseek(fd, tmp_len, SEEK_CUR);
    }
    
    int ans_len;
    read(fd, &ans_len, sizeof(ans_len));
    char* buffer = (char*)malloc(ans_len);
    read(fd, buffer, ans_len);
    return buffer;
}

int Parser::transition_number(){
    int fd = delta_function_fd;
    int n = 0;
    lseek(fd, 0, SEEK_SET);
    read(fd, &n, sizeof(n));
    return n;
}

vector<string> Parser::transition_function(string old_state, string old_symbols){
    vector<string> ans_set;
    int n = transition_number();
    for (int i = 0; i < n; i++){
        int line_len = 0;
        char* transition_line = read_rule_line(&line_len, i);
        char* tokenPtr = strtok(transition_line," ");
        while (tokenPtr != NULL){
            string str = tokenPtr;
            ans_set.push_back(str);
            tokenPtr = strtok(NULL," ");
        }
        if (old_state != ans_set.front()){
            ans_set.clear();
            continue;;
        }
        ans_set.erase(ans_set.begin());
        if (old_symbols != ans_set.front()){
            ans_set.clear();
            continue;;
        }
        ans_set.erase(ans_set.begin());
        return ans_set;
    }
    return ans_set;
}


void Parser::show(){
    printf("State_group:\n");
    for (int i = 0; i < state_group.size(); i++){
        cout<<'\t'<<state_group[i]<<endl;
    }

    printf("Input_symbols_group:\n");
    for (int i = 0; i < input_symbol_group.size(); i++){
        cout<<'\t'<<input_symbol_group[i]<<endl;
    }

    printf("Tape_symbols:\n");
    for (int i = 0; i < tape_symbol_group.size(); i++){
        cout<<'\t'<<tape_symbol_group[i]<<endl;
    }

    printf("Final_states:\n");
    for (int i = 0; i < final_state_group.size(); i++){
        cout<<'\t'<<final_state_group[i]<<endl;
    }
}

bool Parser::is_in_input_symbols(char ch){
    for (int i = 0; i < input_symbol_group.size(); i++){
        if (input_symbol_group[i] == ch)
            return true;
    }
    return false;
}

Parser::~Parser(){
    close(delta_function_fd);
    state_group.clear();
    input_symbol_group.clear();
    tape_symbol_group.clear();
    final_state_group.clear();
}

make_parse_group_func(Q)
make_clean_group_func(Q)

make_parse_group_func(S)
make_clean_group_func(S)

make_parse_symbol_func(B)
make_clean_symbol_func(B)

make_parse_group_func(F)
make_clean_group_func(F)

make_parse_group_func(G)
make_clean_group_func(G)

make_parse_symbol_func(N)
make_clean_symbol_func(N)

make_parse_symbol_func(q0)
make_clean_symbol_func(q0)



