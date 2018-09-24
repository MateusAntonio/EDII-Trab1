#ifndef FILE_READER_H
#define FILE_READER_H   
#include "city.h"

typedef struct tsp TSP;

//inicializa a struct TSP
TSP* init_tsp(char* name, char* comment, char* type, int dimension, char* edge_weight_type);

char* get_tsp_name(TSP* tsp);

char* get_tsp_type(TSP* tsp);

int get_tsp_dimension(TSP* tsp);

City* get_tsp_coord_section(TSP* tsp);

void print_tsp(TSP* tsp);

void free_tsp(TSP* tsp);

TSP* read_tsp_file(char* filename);

#endif //FILE_READER_H