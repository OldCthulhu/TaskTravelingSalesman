#ifndef _GENETIC_ALGORITHM_H_
#define _GENETIC_ALGORITHM_H_
#include "Map/map.h"
#include "includes.h"
#include "evaluator.h"
#include "reproductor.h"
#include "mutator.h"
#include "gene.h"
#include "const.h"


class GeneticAlgorithm{
public:
    GeneticAlgorithm(const int numberBeginCity,
                     const shared_ptr<Map> map,
                     const int countGenes,
                     const int countPopulation,
                     const int changeMutation);

    void Start();

    void NextPopulation(){

        //Selection
        //Reprodaction
        Population newPopulation = Crossower::Reproduction(_population);


        //std::copy(newPopulation.begin(), newPopulation.end(), std::back_inserter(_population));
        _population = newPopulation;

        Mutator::Mutation(newPopulation, _changeMutation);

        //Evaluator::Estimate(_population, _map);

        /*std::sort(_population.begin(), _population.end(), [](shared_ptr<Gene> gene1, shared_ptr<Gene> gene2){
           return gene1->fitness < gene2->fitness;
        });*/

        //_population.resize(_countGenes);
        //Mutation

        Evaluator::Estimate(_population, _map);

        shared_ptr<Gene> bestGene = _population[0];
        for(auto gene : _population){
            if(bestGene->fitness > gene->fitness){
                bestGene = gene;
            }
        }
        _bestGene = bestGene;

        ++_numberCurrentPopulation;
    }

    int GetCurrentPopulation() const{
       return _numberCurrentPopulation;
    }

    bool IsNext();

    Gene GetBestGene() const;
private:
    int _countGenes;
    int _maxPopulation;
    int _numberCurrentPopulation;
    int _numberBeginCity;
    int _changeMutation;

    //Best gen will be on the top postion
    weak_ptr<Gene> _bestGene;
    Population _population;
    shared_ptr<Map> _map;
};

#endif
