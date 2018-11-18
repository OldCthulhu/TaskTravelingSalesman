#ifndef MUTATOR_H_
#define MUTATOR_H_
#include "gene.h"
#include "includes.h"
#include "const.h"

class Mutator{
public:
    static void Mutation(const Population& population, const int changeMutation);

};

#endif
