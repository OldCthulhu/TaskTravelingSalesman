#include "geneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(const int numberBeginCity,
                                   const shared_ptr<Map> map,
                                   const int countGenes,
                                   const int countPopulation,
                                   const int changeMutation){

    _map = map;
    _countGenes = countGenes;
    _maxPopulation= countPopulation;
    _numberBeginCity = numberBeginCity;
    _changeMutation = changeMutation;
}

void GeneticAlgorithm::Start(){
    _numberCurrentPopulation = 0;

    //Genes
    for(int i = 0; i < _countGenes; ++i){
        shared_ptr<Gene> newGene = std::make_shared<Gene>();

        int countCities = _map->GetSize();

        //cities
        for(int j = 0; j < countCities; ++j){
            if(j != _numberBeginCity){
                newGene->solution.push_back(j);
            }
        }
        //
        //Перемешать
        std::random_shuffle(newGene->solution.begin(), newGene->solution.end());

        newGene->numberBeginCity = _numberBeginCity;
        _population.push_back(newGene);
    }

    Evaluator::Estimate(_population, _map);
}

Gene GeneticAlgorithm::GetBestGene() const{
    if(_numberCurrentPopulation == 0){
        return Gene();
    }else{
        return *_bestGene.lock();
    }
}

bool GeneticAlgorithm::IsNext(){
    if(_numberCurrentPopulation >= _maxPopulation){
        return false;
    }

    return true;
}
