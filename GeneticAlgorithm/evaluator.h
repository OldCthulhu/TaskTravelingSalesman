#ifndef _EVALUATOR_H_
#define _EVALUATOR_H_
#include "includes.h"
#include "gene.h"
#include "Map/map.h"


class Evaluator{
public:
    static void Estimate(Population& population, const shared_ptr<Map> map);
};

#endif
