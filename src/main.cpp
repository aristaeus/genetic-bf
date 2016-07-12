#include <fstream>
#include <iostream>
#include <string>
#include "bfint.hpp"

#define NUM_GEN 1000

int main(){
    SumAlgo algo;
    algo.init();
    for(int i = 0; i < 100; i++){
        algo.run_generation(NUM_GEN);
        std::cout<<"generation: "<<i*NUM_GEN<<", fitness: "<<algo.get_fitness()<<std::endl;
    }
    return 0;
}
