#ifndef BFINT_HPP
#define BFINT_HPP

#include <vector>

class BFProgram{
    std::string code;
    public:
    void init(std::string code);
    void run(std::vector<int>* input);
};

#endif
