#include <iostream>
#include <map>

#include <stdio.h>

#include "bfint.hpp"

void
BFProgram::init(std::string code){
    this->code = code;
}

void
BFProgram::run(std::vector<int>* input){
    int instr = 0;
    int total_instr = 0;
    const int max_instr = 10000000;
    int inp_ctr = 0;
    int stack[10000] = {0};
    int ptr = 0;
    std::vector<int> output;

    std::map<int,int> braces;
    // build braces
    for(int i = 0; i < code.size(); i++){
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

    while(instr < code.size()){
        if(code[instr] == '>')
            ptr++;
        if(code[instr] == '<')
            ptr--;
        if(code[instr] == '+')
            stack[ptr]++;
        if(code[instr] == '-')
            stack[ptr]--;
        if(code[instr] == '.')
            output.push_back(stack[ptr]);
        if(code[instr] == ',')
            if(inp_ctr < input->size())
                stack[ptr] = (*input)[inp_ctr++];
        if(code[instr] == '['){
            if(!stack[ptr])
                instr = braces[instr];
        }
        if(code[instr] == ']'){
            if(stack[ptr])
                instr = braces[instr];
        }
        instr++;
        total_instr++;
        if(total_instr < max_instr)
            std::cout<<"error: infinite loop?"<<std::endl;
    }

    for(int i = 0; i < output.size(); i++){
        std::cout<<(char)output[i];
    }
}

void
GeneAlgo::run_generation(int num){
    for(int i = 0; i < num; i++){
        
    }
}

int
GeneAlgo::get_fitness(){
    auto it = programs.end();
    return it->first;
}

int
SumAlgo::fitness(BFProgram bf){
    std::vector<int> input {2, 5};
    bf.run(&input);

}

void
SumAlgo::breed(){
}

void
SumAlgo::mutate(){
}
