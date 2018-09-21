#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADs/fileReader.h"
#include "TADs/city.h"
#include "TADs/graph.h"



int main(int argc, char* argv[]){
    // printf("%d\n", calc_arc_array_size(18512)); //MANO ISSO VAI DAR BOSTAAAAAAAAAA
    TSP* tsp = read_tsp_file(argv[argc-1]);
    print_tsp(tsp);
    Graph* g = generate_graph(tsp);
    printf("\n************ NOT SORTED ************\n");
    print_graph(g);
    printf("\n************ SORTED ************\n");
    sort_graph(g);
    print_graph(g);
    free_graph(g);
    free_tsp(tsp); //TODO checar liberação de memoria ***********IMPORTANTE***********
    
    return 0;
}