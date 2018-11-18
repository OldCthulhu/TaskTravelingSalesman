#include "reproductor.h"
#include <QDebug>

Population Crossower::Reproduction(const Population& population){
    int countChild = population.size();

    Population newPopulation;

    for(int i = 0; i < countChild; ++i){
        auto parentOwn = SelectParent(population);
        auto parentTwo = SelectParent(population);

        //auto parentOwn = population[i % population.size()];
        //auto parentTwo = population[(i + 1) % population.size()];

        if(parentOwn == nullptr || parentTwo == nullptr){
            return newPopulation;
        }

        int middleBorder = parentOwn->solution.size() / 2;

        shared_ptr<Gene> newGene = std::make_shared<Gene>();
        newGene->numberBeginCity = parentOwn->numberBeginCity;


        //std::unordered_set<int> genes;
        if(parentOwn->fitness > parentTwo->fitness){
            /*for(int i = 0; i < parentOwn->solution.size(); ++i){
                const bool is_in = genes.find(parentOwn->solution[i]) != genes.end();
                if(is_in){
                    genes.insert(parentTwo->solution[i]);
                }else{
                    genes.insert(parentOwn->solution[i]);
                }
            }*/
            newGene->solution = parentTwo->solution;
        }else{
            /*for(int i = middleBorder; i < parentOwn->solution.size(); ++i){
                const bool is_in = genes.find(parentTwo->solution[i]) != genes.end();
                if(is_in){
                    genes.insert(parentOwn->solution[i]);
                }else{
                    genes.insert(parentTwo->solution[i]);
                }
            }*/
            newGene->solution = parentOwn->solution;
        }
        //
        /*
        for(int i = 0; i < parentOwn->solution.size(); ++i){
            genes.insert(parentOwn->solution[i]);
            genes.insert(parentTwo->solution[i]);
        }


        */
        //newGene->solution.assign(genes.begin(), genes.end());
        newPopulation.push_back(newGene);
    }

    return newPopulation;
}

shared_ptr<Gene> Crossower::SelectParent(const Population& population){

    float sumFitness = 0;

    for(auto gene : population){
        if(gene->fitness != 0){
            float k = 1 / (float)gene->fitness;
            sumFitness += k;
        }
    }

    if(sumFitness == 0){
        return shared_ptr<Gene>();
    }

    auto gene = population[(rand() + 1) % population.size()];
    while(true){
        auto gene = population[(rand() + 1) % population.size()];
        if(gene->fitness == 0){
            break;
        }

        float propobility = (1 / (float)gene->fitness) / (float)sumFitness * 100;

        if((rand() + 1) % 101 <= propobility){
            return gene;
        }
    }

    qDebug() << "пуст";
    return gene;
}
