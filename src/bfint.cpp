#include <algorithm>
#include <iostream>
#include <map>

#include <stdio.h>

#include "bfint.hpp"

void
BFProgram::init(std::string code){
    this->code = code;
    fitness = 0;
}

std::vector<int>
BFProgram::run(std::vector<int>* input){
    int instr = 0;
    int total_instr = 0;
    const int max_instr = 100000;
    const int max_ptr = 10000;
    int inp_ctr = 0;
    int stack[max_ptr] = {0};
    int ptr = 0;
    std::vector<int> output;

    std::map<int,int> braces;

    // build braces
    for(int i = 0; i < code.size(); i++){
        if(code[i] == '['){
            int opening = 0;
            int j = 0;
            for(j = i+1; opening >= 0 && j < code.size(); j++){
                if(code[j] == '[') opening++;
                if(code[j] == ']') opening--;
            }
            braces[i] = j-1;
            braces[j-1] = i;
        }
    }

    while(instr < code.size() && total_instr < max_instr && ptr > 0 && ptr < max_ptr){
        if(code[instr] == '>'){
            std::cout<<"ptr: "<<ptr<<"instr: "<<instr<<std::endl;
            ptr++;
        }
        if(code[instr] == '<'){
            std::cout<<"ptr: "<<ptr<<"instr: "<<instr<<std::endl;
            ptr--;
        }
        if(code[instr] == '+'){
            std::cout<<"ptr: "<<ptr<<"instr: "<<instr<<std::endl;
            stack[ptr]++;
        }
        if(code[instr] == '-'){
            std::cout<<"ptr: "<<ptr<<"instr: "<<instr<<std::endl;
            stack[ptr]--;
        }
        if(code[instr] == '.')
            output.push_back(stack[ptr]);
        if(code[instr] == ','){
            if(inp_ctr < input->size()){
                std::cout<<"ptr: "<<ptr<<"instr: "<<instr<<std::endl;
                stack[ptr] = (*input)[inp_ctr++];
            }
        }
        if(code[instr] == '['){
            if(!stack[ptr])
                instr = braces[instr];
        }
        if(code[instr] == ']'){
            if(stack[ptr]){
                if(braces.find(instr) != braces.end())
                    instr = braces[instr];
            }
        }
        instr++;
        total_instr++;
        if(total_instr > max_instr)
            std::cout<<"error: infinite loop?"<<std::endl;
        if(ptr >= max_ptr || ptr < 0)
            std::cout<<"error: stack overflow"<<std::endl;
    }

    return output;
}

void
GeneAlgo::init(){

}

void
GeneAlgo::fitness(BFProgram* bf){

}

void
GeneAlgo::breed(){
    auto win = programs.begin();
    // std::advance(win, 0.9*NUM_PROGRAMS);
    std::uniform_int_distribution<int> parent_dist(0.9*NUM_PROGRAMS, NUM_PROGRAMS);
    for(auto it = programs.begin(); it != win; it++){
        std::string code;

        int a = parent_dist(rand);
        int b = parent_dist(rand);
        int off1 = win[a].code.size();
        int off2 = win[b].code.size();
        std::uniform_int_distribution<int> code_dist1(0,0.75*off1);;
        code += win[a].code.substr(0,code_dist1(rand));
        std::uniform_int_distribution<int> code_dist2(0,0.75*off2);;
        code += win[b].code.substr(0,code_dist2(rand));

        it->init(code);
    }
}

void
GeneAlgo::mutate(){
    std::uniform_int_distribution<int> dist(0,NUM_PROGRAMS-1);
    for(int i = 0; i < 5000; i++){
        int j = dist(rand);
        std::uniform_int_distribution<int> code(0,programs[j].code.size()-1);
        programs[j].code[code(rand)] = bf_char();
    }
}

void
GeneAlgo::run_generation(int num){
    for(int i = 0; i < num; i++){
        for(auto it = programs.begin(); it != programs.end(); it++){
            fitness(&(*it));
            if(it->fitness)
                std::cout<<it->fitness<<"!!!\n";
        }

        std::sort(programs.begin(), programs.end(),
            [](BFProgram& a, BFProgram& b){
                return a.fitness < b.fitness; });

        breed();
        mutate();
    }
}

int
GeneAlgo::get_fitness(){
    auto it = programs.end() - 1;
    return it->fitness;
}

char 
GeneAlgo::bf_char(){
    char chars [] = {',','.','[',']','<','>','+','-'};
    std::uniform_int_distribution<int> dist(0,7);
    return chars[dist(rand)];
}

void
SumAlgo::init(){
    rand.seed(4);
    for(auto it = programs.begin(); it != programs.end(); it++){
        std::string code = ",>,<";
        std::uniform_int_distribution<int> dist(10,40);
        int size = dist(rand);
        for(int i = 0; i < size; i++){
            code += bf_char();
        }
        int braces = 0;
        for(int i = 0; i < code.size(); i++){
            if(code[i] == '[') braces++;
            if(code[i] == ']'){
                if(braces > 0) braces--;
                else code.erase(i,1);
            }
        }
        for(int i = 0; i < braces; i++) code+=']';
        it->init(code);
    }
}

void
SumAlgo::fitness(BFProgram* bf){
    std::vector<int> input {2, 5};
    std::vector<int> expected_output {7};
    std::vector<int> output = bf->run(&input);
    if(output.size() > 0){
        for(int i = 0; i < output.size(); i++){
            if(output[i] == expected_output[i]) bf->fitness++;
        }
        output.clear();
    }

    input[0] = 4;
    input[1] = 3;
    expected_output[0] = 7;
    output = bf->run(&input);
    if(output.size() > 0){
        for(int i = 0; i < output.size(); i++){
            if(output[i] == expected_output[i]) bf->fitness++;
        }
        output.clear();
    }

    input[0] = 8;
    input[1] = 2;
    expected_output[0] = 10;
    output = bf->run(&input);
    if(output.size() > 0){
        for(int i = 0; i < output.size(); i++){
            if(output[0] == expected_output[0]) bf->fitness++;
        }
    }
    output.clear();

    input[0] = 2;
    input[1] = 2;
    expected_output[0] = 4;
    output = bf->run(&input);
    if(output.size() > 0){
        for(int i = 0; i < output.size(); i++){
            if(output[0] == expected_output[0]) bf->fitness++;
        }
    }
    output.clear();

    input[0] = 6;
    input[1] = 3;
    expected_output[0] = 9;
    output = bf->run(&input);
    if(output.size() > 0){
        for(int i = 0; i < output.size(); i++){
            if(output[0] == expected_output[0]) bf->fitness++;
        }
    }
    output.clear();

    if(bf->fitness > 3){
        std::uniform_int_distribution<int> dist(0,20);
        for(int i = 0; i < 95; i++){
            input[0] = dist(rand);
            input[1] = dist(rand);
            expected_output[0] = input[0] + input[1];
            output = bf->run(&input);
            if(output.size() > 0){
                if(output[0] == expected_output[0]) bf->fitness++;
            }
            output.clear();
        }
    }
}
