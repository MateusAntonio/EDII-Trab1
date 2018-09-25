#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph Graph;

int calc_arc_array_size(int dimension);

Graph* generate_graph(void* array, int dimension);

void print_graph(Graph* graph);

void free_graph(Graph* graph);

void sort_graph(Graph* graph);

int arc_compare(const void* arc1, const void* arc2);

Graph* generate_mst(Graph* graph, int mst_dimension);

void write_mst(char* name, char* type, int dimension, Graph* mst);

void write_tour(char* name, int dimension);

void teste();

int* generate_tour(Graph* mst);

#endif //GRAPH_H