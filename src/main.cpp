#include <fstream>
#include <iostream>
#include <string>
#include "bfint.hpp"

int main(){
    std::string code;
    std::string line;
    std::ifstream file("file");
    while(getline(file,line))
        code += line;

    std::vector<int> input;
    input.push_back('a');
    input.push_back('b');
    input.push_back('o');
    input.push_back('n');

    BFProgram bf;
    bf.init(code);
    bf.run(&input);

    return 0;
}
