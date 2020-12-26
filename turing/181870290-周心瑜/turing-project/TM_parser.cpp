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
    in_file.open(prog_name);
    if (in_file.fail()){
        MyException err("FILE not exits.");
        err.what();
    }
    
    strcpy(delta_function_file,"/tmp/temp_file.XXXXXX");
    delta_function_fd = mkstemp(delta_function_file);
    unlink(delta_function_file);
    initial_transition_file();
    
    while (!in_file.fail()){
        string line_str;
        getline(in_file, line_str);
        //cout<<line_str<<endl;
        if (line_str.find(';') != string::npos){
            line_str = line_str.substr(0, line_str.find(';'));
        }
        if (!line_str.empty() && line_str[0] != ';'){
            parse_certain_line(line_str);
        }
    }
}

void Parser::parse_certain_line(string line){
    try{
        if (line[0] != '#'){
            if (!is_in_form_of_five_tuple(line)){
                MyException err;
                err.what();
            }
            char* tmp_str = (char*)malloc(sizeof(char) * (line.length() + 1));
            strcpy(tmp_str, line.c_str());
            write_temp_file(tmp_str, line.length());
            free(tmp_str);
            return;
        }
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
    //printf("Write rule: %d\n",tmp_len);
    
    lseek(fd, 0, SEEK_SET);
    int len = tmp_len + 1;
    write(fd, &len, sizeof(len));
}

void Parser::initial_transition_file(){
    int fd = delta_function_fd;
    lseek(fd, 0, SEEK_SET);
    int len = 0;
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
    
    read(fd, length, sizeof(int));
    char* buffer = (char*)malloc(*length + 1);
    read(fd, buffer, *length);
    buffer[*length] = '\0';
    return buffer;
}

int Parser::transition_number(){
    int fd = delta_function_fd;
    int n = 0;
    lseek(fd, 0, SEEK_SET);
    read(fd, &n, sizeof(n));
    //printf("N: %d\n",n);
    return n;
}

vector<string> Parser::transition_function(string old_state, string old_symbols){
    vector<string> ans_set;
    int n = transition_number();
    for (int i = 0; i < n; i++){
        int line_len = 0;
        char* transition_line = read_rule_line(&line_len, i);
        string str = transition_line;
        istringstream in(str);
        ans_set.clear();
        while (in >> str){
            ans_set.push_back(str);
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

void Parser::show_transition_rule(){
    vector<string> ans_set;
    int n = transition_number();
    for (int i = 0; i < n; i++){
        int line_len = 0;
        char* transition_line = read_rule_line(&line_len, i);
        printf("\nRule:%s        %d\n",transition_line, line_len);
        string str = transition_line;
        istringstream in(str);
        ans_set.clear();
        while (in >> str){
            ans_set.push_back(str);
        }
        printf("After:\n");
        for (int j = 0; j < ans_set.size();j++){
            printf("%s  ",ans_set[j].c_str());
        }
        printf("\n");
    } 
}

bool Parser::is_in_input_symbols(char ch){
    for (int i = 0; i < input_symbol_group.size(); i++){
        if (input_symbol_group[i] == ch)
            return true;
    }
    return false;
}

bool Parser::is_in_tape_symbols(string str){
    if (str.length() != tape_number)
        return false;
    for (int index = 0; index < str.length(); index++){
        char ch = str[index];
        bool flag = false;
        for (int i = 0; i < tape_symbol_group.size(); i++){
            if (tape_symbol_group[i] == ch){
                flag = true;
                break;
            }
        }
        if (!flag)
            return false;
    }
    return true;
}

bool Parser::is_in_state_group(string cur_state){
    for (int i = 0; i < state_group.size(); i++){
        if (state_group[i] == cur_state)
            return true;
    }
    return false;
}

bool Parser::is_in_final_state_group(string cur_state){
    for (int i = 0; i < final_state_group.size(); i++){
        if (final_state_group[i] == cur_state)
            return true;
    }
    return false;
}

bool Parser::is_in_form_of_five_tuple(string line){
    istringstream in(line);
    vector<string> tuple;
    string str;
    while (in >> str){
        tuple.push_back(str);
    }
    if (tuple.size() != 5)
        return false;
    if (!is_in_state_group(tuple[0]))
        return false;
    if (!is_in_tape_symbols(tuple[1]))
        return false;
    if (!is_in_tape_symbols(tuple[2]))
        return false;
    if (!(regex_match(tuple[3], regex("[l/r*]+")) && (tuple[3].length() == tape_number)))
        return false;
    if (!is_in_state_group(tuple[4]))
        return false;
    return true;
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



