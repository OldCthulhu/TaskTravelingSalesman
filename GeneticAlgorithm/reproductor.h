#ifndef _REPRODUCTOR_H_
#define _REPRODUCTOR_H_
#include "gene.h"
#include "includes.h"

class Crossower{
public:
    static Population Reproduction(const Population& population);
    static shared_ptr<Gene> SelectParent(const Population& population);
};

#endif
