#ifndef GENE_H_
#define GENE_H_
#include "includes.h"

struct Gene{
   vector<int> solution;
   float fitness = 0;
   int numberBeginCity;
};

typedef vector<shared_ptr<Gene>> Population;

#endif
