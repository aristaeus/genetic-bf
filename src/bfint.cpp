#include <iostream>
#include <map>

#include "bfint.hpp"

void bf(int* code, int* input, int* output, int* instr, int* inp_ctr, int* out_ctr, int** ptr, int size);

void run_bf(int* code, int* input, int* output, int size){
    int instr = 0;
    int inp_ctr = 0;
    int out_ctr = 0;
    int stack[1000] = {0};
    int* ptr = stack;

    bf(code, input, output, &instr, &inp_ctr, &out_ctr, &ptr, size);
}

int get_size(int* instr){
    int opening = 0;
    int i = 0;
    while(opening >= 0){
        if(instr[i] == '['){
            std::cout<<"count up"<<std::endl;
            opening++;
        }
        if(instr[i] == ']'){
            opening--;
            std::cout<<"count down"<<std::endl;
        }
        i++;
    }
    return i;
}

void bf(int* code, int* input, int* output, int* instr, int* inp_ctr, int* out_ctr, int** ptr, int size){
    int start_instr = *instr;
    std::map<int,int> braces;
    // build braces
    for(int i = 0; i < size; i++){
        if(code[i] == '['){
            int opening = 0;
            int j = 0;
            for(j = i+1; opening >= 0; j++){
                if(code[j] == '[') opening++;
                if(code[j] == ']') opening--;
            }
            braces[i] = j-1;
            braces[j-1] = i;
        }
    }
    while(*instr < size + start_instr){
        if(code[*instr] == '>')
            (*ptr)++;
        if(code[*instr] == '<')
            (*ptr)--;
        if(code[*instr] == '+')
            (**ptr)++;
        if(code[*instr] == '-')
            (**ptr)--;
        if(code[*instr] == '.')
            output[(*out_ctr)++] = **ptr;
        if(code[*instr] == ',')
            **ptr = input[(*inp_ctr)++];
        if(code[*instr] == '['){
            if(!**ptr)
                *instr = braces[*instr];
        }
        if(code[*instr] == ']'){
            if(**ptr)
                *instr = braces[*instr];
        }
        (*instr)++;
    }
}
