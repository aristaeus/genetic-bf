#include <fstream>
#include <iostream>
#include <string>
#include "bfint.hpp"

int main(){
    SumAlgo algo;
    algo.init();
    for(int i = 0; i < 10; i++){
        algo.run_generation(100);
        std::cout<<"generation: "<<i*100<<", fitness: "<<algo.get_fitness()<<std::endl;
    }
    return 0;
}
