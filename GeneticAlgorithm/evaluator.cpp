#include "evaluator.h"


void Evaluator::Estimate(Population& population, const shared_ptr<Map> map){
    for(auto gene : population){
        gene->fitness = map->CalcLength(gene->solution, gene->numberBeginCity);
    }
}
