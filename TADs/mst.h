#ifndef MST_H
#define MST_H
#include "fileReader.h"

typedef struct mst MST;

int calc_arc_array_size(int dimension);

MST* generate_mst(TSP* tsp);

void print_mst(MST* mst);

#endif //MST_H