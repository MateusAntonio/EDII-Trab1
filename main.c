#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADs/fileReader.h"
#include "TADs/city.h"
#include "TADs/graph.h"



int main(int argc, char* argv[]){
    TSP* tsp = read_tsp_file(argv[argc-1]);
    // print_tsp(tsp);
    Graph* g = generate_graph(tsp);
    print_graph(g);
    sort_graph(g);
    // printf("\n************ SORTED ************\n\n");
    // print_graph(g);
    free_tsp(tsp); //TODO checar liberação de memoria ***********IMPORTANTE***********
    
    return 0;
}