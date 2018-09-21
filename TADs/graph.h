#ifndef GRAPH_H
#define GRAPH_H
#include "fileReader.h"

typedef struct graph Graph;

int calc_arc_array_size(int dimension);

Graph* generate_graph(TSP* tsp);

void print_graph(Graph* graph);

void free_graph(Graph* graph);

void sort_graph(Graph* graph);

int arc_compare(const void* arc1, const void* arc2);

void teste(Graph* g);

#endif //GRAPH_H