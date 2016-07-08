#ifndef BFINT_HPP
#define BFINT_HPP

#include <map>
#include <vector>

class BFProgram{
    std::string code;
    public:
    void init(std::string code);
    void run(std::vector<int>* input);
};

class GeneAlgo{
    virtual int fitness(BFProgram bf);
    virtual void breed();
    virtual void mutate();
    std::map<int,BFProgram> programs;

    public:
    virtual void init();

    // run for x generations
    void run_generation(int num);

    int get_fitness();
};

class SumAlgo: public GeneAlgo{
    int fitness(BFProgram bf);
    void breed();
    void mutate();

    public:
    void init();
};

#endif
