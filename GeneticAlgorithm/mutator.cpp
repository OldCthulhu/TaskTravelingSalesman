#include "mutator.h"

void Mutator::Mutation(const Population& population, const int changeMutation){
    auto gene = population[rand() % population.size()];
    for(auto& gene : population){
        float randInt = rand() % 101;
        if(randInt < changeMutation){
            vector<int> solution = gene->solution;
            int sizeSolution = solution.size();
            std::swap(solution[rand() % sizeSolution], solution[rand() % sizeSolution]);

            gene->solution = solution;
        }
    }
}
