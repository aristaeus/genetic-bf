#ifndef BFINT_HPP
#define BFINT_HPP

#include <map>
#include <random>
#include <vector>

#define NUM_PROGRAMS 1000

class BFProgram{
    public:
    std::string code;
    int fitness;
    void init(std::string code);
    std::vector<int>run(std::vector<int>* input);
};

class GeneAlgo{
    protected:
    virtual void fitness(BFProgram* bf);
    virtual void breed();
    virtual void mutate();
    std::array<BFProgram,NUM_PROGRAMS> programs;
    std::mt19937 rand;
    char bf_char();

    public:
    virtual void init();

    // run for x generations
    void run_generation(int num);

    int get_fitness();
};

class SumAlgo: public GeneAlgo{
    void fitness(BFProgram* bf);

    public:
    void init();
};

#endif
