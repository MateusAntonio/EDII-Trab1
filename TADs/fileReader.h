#ifndef FILE_READER_H
#define FILE_READER_H   

typedef struct tsp TSP;

//inicializa a struct TSP
TSP* init_tsp(char* name, char* comment, char* type, int dimension, char* edge_weight_type/*, City** node_coord_section*/);

void print_tsp(TSP* tsp);

void free_tsp(TSP* tsp);

TSP* read_tsp_file(char* filename);

#endif //FILE_READER_H